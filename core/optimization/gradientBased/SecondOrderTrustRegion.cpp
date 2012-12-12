/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - liboptimization - An optimization/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/
#include "core/optimization/gradientBased/SecondOrderTrustRegion.h"

#ifdef NICE_USELIB_LINAL
  #include <LinAl/linal.h>
  #include <LinAl/algorithms.h>
#endif

#include <core/basics/Exception.h>
#include <core/basics/Log.h>

namespace NICE {

SecondOrderTrustRegion::~SecondOrderTrustRegion() {
}

#ifdef NICE_USELIB_LINAL
typedef LinAl::VectorCC<double> LinAlVector;
typedef LinAl::MatrixCF<double> LinAlMatrix;

/**
 * assume input and output to be quadratic and of same size.
 * also assume them to be symmetric
 * (only upper (?) triangular matrix will be used).
 * Exception, if not positive (semi?) definite
 */
void choleskyDecompose(const LinAlMatrix& input, LinAlMatrix& output) {
// FIXME checks missing (quadratic, same size)
  const int size = input.rows();
  int i,j,k;
  double sum;
  for (i=0;i<size;i++) {
    bool divide=true;
    for (j=0;j<i;j++) output(j,i)=0.0;
    for (;j<size;j++) {
      sum=input(i,j);
      for (k=i-1;k>=0;k--) sum -= output(i,k)*output(j,k);
      if (i == j) {
        // The following applies if A, with rounding errors, is not positive definite
        if (isZero(sum, 1e-16)) {
          output(i,i)=0.0;
          divide=false;
        } else if (sum<0.0) {
          // input is (numerically) not positive definite.
          fthrow(Exception, "Choloskey decomposition failed." << sum);
        }
        output(i,i)=sqrt(sum);
      } else {
        if (!divide) output(j,i)=0.0;
        else output(j,i)=sum/output(i,i);
      }
    }
  }
}




/**
 * Compute the inner product of \c v1 and \c v2.
 * @param v1 First parameter vector
 * @param v2 Second parameter vector
 * @return The inner product of \c v1 and \c v2
 */
inline double dotProduct(const LinAlVector& v1,
                         const LinAlVector& v2) {
  double result = 0.0;
  for (int i = 0; i < v1.rows(); i++) {
    result += v1(i) * v2(i);
  }
  return result;
}

/**
 * Compute the squared Euclidian norm of vector \c v.
 * @param v Parameter vector
 * @return The squared Euclidian norm of \c v
 */
inline double normSquared(const LinAlVector& v) {
  double result = 0.0;
  for (int i = 0; i < v.rows(); i++) {
    const double entry = v(i);
    result += entry * entry;
  }
  return result;
}

/**
 * Compute the Euclidian norm of vector \c v.
 * @copydoc normSquared()
 */
inline double norm(const LinAlVector& v) {
  return sqrt(normSquared(v));
}

/**
 * Compute \f$\mathrm{v1}^T \cdot \mathrm{ma} \cdot \mathrm{v2}\f$.
 * @param v1 First vector
 * @param ma Matrix
 * @param v2 Second vector
 * @return \f$\mathrm{v1}^T \cdot \mathrm{ma} \cdot \mathrm{v2}\f$
 */
inline double productVMV(const LinAlVector& v1, 
                         const LinAlMatrix& ma, 
                         const LinAlVector& v2) {
  double result = 0.0;
  for (int i = 0; i < ma.rows(); i++) {
    double productEntry = 0.0;
    for (int j = 0; j < ma.cols(); j++) {
      productEntry += ma(i, j) * v2(j);
    }
    result += v1(i) * productEntry;
  }
  return result;
}

/**
 * Compute \f$\mathrm{v1}^T \cdot \mathrm{ma} \cdot \mathrm{v2}\f$.
 * @param v1 First vector
 * @param ma Matrix
 * @param v2 Second vector
 * @return \f$\mathrm{v1}^T \cdot \mathrm{ma} \cdot \mathrm{v2}\f$
 */
inline double productVMV(const Vector& v1, 
                         const Matrix& ma, 
                         const Vector& v2) {
  double result = 0.0;
  for (unsigned int i = 0; i < ma.rows(); i++) {
    double productEntry = 0.0;
    for (unsigned int j = 0; j < ma.cols(); j++) {
      productEntry += ma(i, j) * v2[j];
    }
    result += v1[i] * productEntry;
  }
  return result;
}
#endif

void SecondOrderTrustRegion::doOptimize(OptimizationProblemSecond& problem) {
#ifdef NICE_USELIB_LINAL
  bool previousStepSuccessful = true;
  double previousError = problem.objective();
  problem.computeGradientAndHessian();
  double delta = computeInitialDelta(problem.gradientCached(), problem.hessianCached());
  double normOldPosition = 0.0;
  
  // iterate
  for (int iteration = 0; iteration < maxIterations; iteration++) {
//     Log::debug() << "iteration, objective: " << iteration << ", "
//                   << problem.objective() << std::endl;
    
    if (previousStepSuccessful && iteration > 0) {
      problem.computeGradientAndHessian();
    }
  
    // gradient-norm stopping condition
    if (problem.gradientNormCached() < epsilonG) {
      Log::debug() << "SecondOrderTrustRegion stopped: gradientNorm "
                   << iteration << std::endl;
      break;
    }
    
    LinAlVector gradient(problem.gradientCached().linalCol());
    LinAlVector negativeGradient(gradient);
    negativeGradient.multiply(-1.0);

    double lambda;
    int lambdaMinIndex = -1;
    // FIXME will this copy the matrix? no copy needed here!
    LinAlMatrix hessian(problem.hessianCached().linal());
    LinAlMatrix l(hessian);
    try {
      //l.CHdecompose(); // FIXME
      choleskyDecompose(hessian, l);
      
      lambda = 0.0;
    } catch (...) { //(LinAl::BLException& e) { // FIXME
      const LinAlVector& eigenValuesHessian = LinAl::eigensym(hessian);

      // find smallest eigenvalue
      lambda = std::numeric_limits<double>::infinity();
      for (unsigned int i = 0; i < problem.dimension(); i++) {
        const double eigenValue = eigenValuesHessian(i);
        if (eigenValue < lambda) {
          lambda = eigenValue;
          lambdaMinIndex = i;
        }
      }
      const double originalLambda = lambda;
      lambda = -lambda * (1.0 + epsilonLambda);
      
      l = hessian;
      for (unsigned int i = 0; i < problem.dimension(); i++) {
        l(i, i) += lambda;
      }
      try {
        //l.CHdecompose(); // FIXME
        LinAlMatrix temp(l);
        choleskyDecompose(temp, l);
      } catch (...) { // LinAl::BLException& e) { // FIXME
        /*
         * Cholesky factorization failed, which should theortically not be
         * possible (can still happen due to numeric problems,
         * also note that there seems to be a bug in CHdecompose()).
         * Try a really great lambda as last attempt.
         */        
//         lambda = -originalLambda * (1.0 + epsilonLambda * 100.0)
//                  + 2.0 * epsilonM;
        lambda = fabs(originalLambda) * (1.0 + epsilonLambda * 1E5)
                 + 1E3 * epsilonM;
//        lambda = fabs(originalLambda);// * 15.0;
        l = hessian;
        for (unsigned int i = 0; i < problem.dimension(); i++) {
          l(i, i) += lambda;
        }
        try {
          //l.CHdecompose(); // FIXME
          LinAlMatrix temp(l);
          choleskyDecompose(temp, l);
        } catch (...) { // (LinAl::BLException& e) { // FIXME
          // Cholesky factorization failed again, give up.
          l = hessian;
          for (unsigned int i = 0; i < problem.dimension(); i++) {
            l(i, i) += lambda;
          }

          const LinAlVector& eigenValuesL = LinAl::eigensym(l);
                    
          Log::detail()
               << "l.CHdecompose: exception" << std::endl
              //<< e.what() << std::endl // FIXME
               << "lambda=" << lambda << std::endl
               << "l" << std::endl << l
               << "hessian" << std::endl << hessian
               << "gradient" << std::endl << gradient
               << "eigenvalues hessian" << std::endl << eigenValuesHessian
               << "eigenvalues l" << std::endl << eigenValuesL
               << std::endl;
          return;
        }
      }
    }

    // FIXME will the copy the vector? copy is needed here
    LinAlVector step(negativeGradient);
    l.CHsubstitute(step);
    double normStepSquared = normSquared(step);
    double normStep = sqrt(normStepSquared);
    // exact: if normStep <= delta
    if (normStep - delta <= tolerance) {
      // exact: if lambda == 0 || normStep == delta
      if (std::fabs(lambda) < tolerance
          || std::fabs(normStep - delta) < tolerance) {
        // done
      } else {
        LinAlMatrix eigenVectors(problem.dimension(), problem.dimension());
        eigensym(hessian, eigenVectors);
        double a = 0.0;
        double b = 0.0;
        double c = 0.0;
        for (unsigned int i = 0; i < problem.dimension(); i++) {
          const double ui = eigenVectors(i, lambdaMinIndex);
          const double si = step(i);
          a += ui * ui;
          b += si * ui;
          c += si * si;
        }
        b *= 2.0;
        c -= delta * delta;
        const double sq = sqrt(b * b - 4.0 * a * c);
        const double root1 = 0.5 * (-b + sq) / a;
        const double root2 = 0.5 * (-b - sq) / a;
        LinAlVector step1(step);
        LinAlVector step2(step);
        for (unsigned int i = 0; i < problem.dimension(); i++) {
          step1(i) += root1 * eigenVectors(i, lambdaMinIndex);
          step2(i) += root2 * eigenVectors(i, lambdaMinIndex);
        }
        const double psi1
          = dotProduct(gradient, step1)
            + 0.5 * productVMV(step1, hessian, step1);
        const double psi2
          = dotProduct(gradient, step2)
            + 0.5 * productVMV(step2, hessian, step2);
        if (psi1 < psi2) {
          step = step1;
        } else {
          step = step2;
        }
      }
    } else {
      for (unsigned int subIteration = 0; 
           subIteration < maxSubIterations; 
           subIteration++) {
        if (std::fabs(normStep - delta) <= kappa * delta) {
          break;
        }

        // NOTE specialized algorithm may be more effifient than solvelineq
        //      (l is lower triangle!)
        // Only lower triangle values of l are valid (other implicitly = 0.0),
        // but solvelineq doesn't know that -> explicitly set to 0.0
        for (int i = 0; i < l.rows(); i++) {
          for (int j = i + 1; j < l.cols(); j++) {
            l(i, j) = 0.0;
          }
        }
        LinAlVector y(step.size());
        try {
          y = solvelineq(l, step);
        } catch (LinAl::Exception& e) {
          // FIXME if we end up here, something is pretty wrong!
          // give up the whole thing
          Log::debug() << "SecondOrderTrustRegion stopped: solvelineq failed "
                       << iteration << std::endl;
          return;
        }
        
        lambda += (normStep - delta) / delta
                  * normStepSquared / normSquared(y);
        l = hessian;
        for (unsigned int i = 0; i < problem.dimension(); i++) {
          l(i, i) += lambda;
        }
        try {
          //l.CHdecompose(); // FIXME
          LinAlMatrix temp(l);
          choleskyDecompose(temp, l);
        } catch (...) { // (LinAl::BLException& e) { // FIXME
          Log::detail()
               << "l.CHdecompose: exception" << std::endl
               // << e.what() << std::endl // FIXME
               << "lambda=" << lambda << std::endl
               << "l" << std::endl << l
               << std::endl;
          return;
        }
        step = negativeGradient;
        l.CHsubstitute(step);
        normStepSquared = normSquared(step);
        normStep = sqrt(normStepSquared);
      }
    }
    
    // computation of step is complete, convert to NICE::Vector
    Vector stepLimun(step);
    
    // minimal change stopping condition
    if (changeIsMinimal(stepLimun, problem.position())) {
      Log::debug() << "SecondOrderTrustRegion stopped: change is minimal "
                   << iteration << std::endl;
      break;
    }
  
    if (previousStepSuccessful) {
      normOldPosition = problem.position().normL2();
    }

    // set new region parameters (to be verified later)
    problem.applyStep(stepLimun);
    
    // compute reduction rate
    const double newError = problem.objective();
//Log::debug() << "newError: " << newError << std::endl;
    const double errorReduction = newError - previousError;
    const double psi = problem.gradientCached().scalarProduct(stepLimun)
                       + 0.5 * productVMV(step, hessian, step);
    double rho;
    if (std::fabs(psi) <= epsilonRho
        && std::fabs(errorReduction) <= epsilonRho) {
      rho = 1.0;
    } else {
      rho = errorReduction / psi;
    }

    // NOTE psi and errorReduction checks added to the algorithm 
    //      described in Ferid Bajramovic's Diplomarbeit
    if (rho < eta1 || psi >= 0.0 || errorReduction > 0.0) {
      previousStepSuccessful = false;
      problem.unapplyStep(stepLimun);
      delta = alpha2 * normStep;
    } else {
      previousStepSuccessful = true;
      previousError = newError;
      if (rho >= eta2) {
        const double newDelta = alpha1 * normStep;
        if (newDelta > delta) {
          delta = newDelta;
        }
      } // else: don't change delta
    }
    
    // delta stopping condition
    if (delta < epsilonDelta * normOldPosition) {
      Log::debug() << "SecondOrderTrustRegion stopped: delta too small "
                   << iteration << std::endl;
      break;
    }
  }
#else // no linal
  fthrow(Exception,
         "SecondOrderTrustRegion needs LinAl. Please recompile with LinAl");
#endif
}


/*
void SecondOrderTrustRegion::doOptimizeFirst(OptimizationProblemFirst& problem) {
  bool previousStepSuccessful = true;
  double previousError = problem.objective();
  problem.computeGradient();
  double delta = computeInitialDelta(problem.gradientNorm());
  double normOldPosition = 0.0;
  
  // iterate
  for (int iteration = 0; iteration < maxIterations; iteration++) {
    if (iteration > 0) {
      problem.computeGradient();
    }
    
    // gradient-norm stopping condition
    if (problem.gradientNorm() < epsilonG) {
      break;
    }

    // compute step
    Vector step(problem.gradient());
    step /= (-delta / problem.gradientNorm());
    
    // minimal change stopping condition
    if (changeIsMinimal(step, problem)) {
      break;
    }
    
    if (previousStepSuccessful) {
      normOldPosition = problem.position().normL2();
    }

    // set new region parameters (to be verified later)
    problem.applyStep(step);
    
    // compute reduction rate
    const double newError = problem.objective();
//Log::debug() << "newError: " << newError << std::endl;
    const double errorReduction = newError - previousError;
    const double psi = problem.gradient().scalarProduct(step);
    double rho;
    if (std::fabs(psi) <= epsilonRho
        && std::fabs(errorReduction) <= epsilonRho) {
      rho = 1.0;
    } else {
      rho = errorReduction / psi;
    }
      
    // NOTE psi check should not really be needed
    if (rho < eta1 || psi >= 0.0) {
      previousStepSuccessful = false;
      problem.unapplyStep(step);
      delta = alpha2 * step.normL2();
    } else {
      previousStepSuccessful = true;
      previousError = newError;
      if (rho >= eta2) {
        const double newDelta = alpha1 * step.normL2();
        if (newDelta > delta) {
          delta = newDelta;
        }
      } // else: don't change delta
    }
    
    // delta stopping condition
    if (delta < epsilonDelta * normOldPosition) {
      break;
    }
  }
}
*/

double SecondOrderTrustRegion::computeInitialDelta(
                                 const Vector& gradient,
                                 const Matrix& hessian) {
#ifdef NICE_USELIB_LINAL
  const double norm = gradient.normL2();
  const double gHg = productVMV(gradient, hessian, gradient);
  double result;
  if (isZero(norm)) {
    result = 1.0;
  } else if (isZero(gHg) || gHg < 0) {
    result = norm / 10.0;
  } else {
    result = norm * norm / gHg;
  }
  if (result < deltaMin) {
    result = deltaMin;
  }
  return result;
#else
  fthrow(Exception,
         "SecondOrderTrustRegion needs LinAl. Please recompile with LinAl");
#endif
}

}; // namespace NICE 
