/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - liboptimization - An optimization/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/
#ifndef _OPTIMIZATIONPROBLEMSECOND_OPTIMIZATION_H
#define _OPTIMIZATIONPROBLEMSECOND_OPTIMIZATION_H

#include <iostream>

#include <core/vector/MatrixT.h>
#include <core/optimization/gradientBased/OptimizationProblemFirst.h>

namespace NICE {

/**
 * Base class for nonlinear minimization problems providing
 * 1st and 2nd order derivatives.
 *
 * The documentation of this class has three parts. The first part is of
 * general importance. The second part is for users of the library.
 * The third part describes details which are important
 * when implementing new optimization algorithms. These details can also
 * be important to users of the library.
 *
 * <b>1. General Information</b>
 *
 * The interface provides the value of the objective function, the gradient,
 * the Hessian and some further data.
 *
 * <b>2. Using the Library</b>
 *
 * If you want to use the library to solve an optimization problem,
 * you have to implement a subclass of \c OptimizationProblemSecond
 * or at least of \c OptimizationProblemFirst. The later is simpler,
 * as it does not require a function to compute the Hessian matrix.
 * However, it cannot be solved using the (generally) more efficient
 * second order optimization algorithms.
 *
 * Quite obviously, you need (at least) to implement all abstract
 * (i.e. pure virtual) methods:
 * - \c computeObjective() has to compute the value of the objective function
 *   at the current position in parameter space.
 * - If you implement a subclass of \c OptimizationProblemFirst, you need
 *   to implement \c computeGradient(), which has to compute the gradient
 *   of the objective function at the current position in parameter space.
 * - If you implement a subclass of \c OptimizationProblemSecond, you need
 *   to implement <b>either</b> \c computeGradientAndHessian() <b>or</b>
 *   \c computeGradient() and \c computeHessian() (and a simple
 *   \c computeGradientAndHessian() which calls the other two).
 *
 * You also need to take care of how the current position in parameter space
 * is represented. There are two possibilities:
 * - \c OptimizationProblemFirst provides the method \c position() which
 *   gives public read access to the current position, and the protected method
 *   \c parameters() which gives write access. You can simply store the
 *   current position in parameter space in the vector returned by
 *   \c parameters(). This is the suggested technique.
 * - If you want to have a different representation, you need to reimplement
 *   \c computePosition(), \c doApplyStep() and \c doUnapplyStep().
 *   Use this alternative technique only if there is a good reason
 *   (e.g. if you already have existing code which uses its own
 *   representation).
 *
 * Note: If you want to renormalize the position in parameter space
 *       (e.g. to ensure that unit quaternions have unit length),
 *       you can do so in \c doApplyStep(). Further information is provided
 *       there.
 *
 * For an example, refer to the CppUnit test cases of the library.
 *
 * <b>3. Implementing Optimization Algorithms</b>
 *
 * There is an important difference in the way derivatives
 * and non-derivative information is handled. All non-derivate information is
 * automatically computed at the current position in parameter space
 * when the access method is called.
 * Derivatives are only computed by an explicit call to \c computeGradient()
 * (or \c computeGradientAndHessian() in the second order subclass)
 * and also by calling \c gradientCurrent(), \c gradientNormCurrent()
 * (or \c hessianCurrent() in the second order subclass).
 * This strategy allows keeping old derivatives without copying when applying
 * a test step. See \c FirstOrderTrustRegion for a quite simple example.
 *
 * \ingroup optimization_problems
 */
class OptimizationProblemSecond : public OptimizationProblemFirst {
public:
  //! Default constructor
  inline OptimizationProblemSecond(unsigned int dimension)
      : OptimizationProblemFirst(dimension), m_hessianCached(false) {}

  virtual ~OptimizationProblemSecond();

  inline void computeGradientAndHessian() {
    m_gradientNormCached = false;
    m_hessianCache.resize(dimension(), dimension());
    computeGradientAndHessian(m_gradientCache, m_hessianCache);
    m_gradientCached = true;
    m_hessianCached = true;
  }

  /**
   * Get the Hessian of the objective function
   * as computed by the last call to \c computeGradientAndHessian().
   */
  inline const Matrix& hessianCached() {
    return m_hessianCache;
  }

  /**
   * Get the Hessian of the objective function at the current position
   * in parameter space.
   * The Hessian will be computed if the Hessian cache is out of date.
   */
  inline const Matrix& hessianCurrent() {
    if (!m_hessianCached) {
      computeGradientAndHessian();
    }
    return m_hessianCache;
  }

  /**
   * See base class. Note: you probably don't want to override this
   * method in a subclass.
   */
  virtual void invalidateCaches() {
    OptimizationProblemFirst::invalidateCaches();
    m_hessianCached = false;
  }

protected:
  /**
   * Compute the gradient and the Hessian of the objective function
   * at the current position.
   * @param newGradient Output parameter for the gradient of the objective
   *        function. Be careful: \c newGradient is the <b>same</b> object
   *        as \c gradientCached(). If you need to access (the old)
   *        \c gradientCached()
   *        during the computation, first make a copy.
   * @param newHessian Output parameter for the Hessian of the objective
   *        function. Be careful: \c newHessian is the <b>same</b> object
   *        as \c hessianCached(). If you need to access (the old)
   *        \c hessianCached()
   *        during the computation, first make a copy.
   */
  virtual void computeGradientAndHessian(Vector& newGradient,
                                         Matrix& newHessian) = 0;

  /**
   * See baseclass for documentation.
   * @note
   * There is a default implementation for this method, which uses
   * \c computeGradientAndHessian(). This works, but is not efficient for
   * 1st order optimization algorithms. To improve this, provide an efficient
   * implementation of \c computeGradient(). Depending on your situation,
   * it may or may not be a good idea to have a method computeHessian() and
   * call computeHessian() and computeGradient()
   * in computeGradientAndHessian().
   */
  virtual void computeGradient(Vector& newGradient);

private:
  bool m_hessianCached;
  Matrix m_hessianCache;
};

}; // namespace NICE

#endif /* _OPTIMIZATIONPROBLEMSECOND_OPTIMIZATION_H */
