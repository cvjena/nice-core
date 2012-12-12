/** 
* @file ILSConjugateGradientsLanczos.cpp
* @brief Iteratively solving linear equation systems with the conjugate gradients method using Lanczos process
* @author Paul Bodesheim
* @date 20/01/2012 (dd/mm/yyyy)

*/
#include <iostream>

#include "ILSConjugateGradientsLanczos.h"

using namespace NICE;
using namespace std;


ILSConjugateGradientsLanczos::ILSConjugateGradientsLanczos( bool verbose, uint maxIterations, double minDelta) //, bool useFlexibleVersion )
{
  this->minDelta = minDelta;
  this->maxIterations = maxIterations;
  this->verbose = verbose;
//   this->useFlexibleVersion = useFlexibleVersion;
}

ILSConjugateGradientsLanczos::~ILSConjugateGradientsLanczos()
{
}

// void ILSConjugateGradientsLanczos::setJacobiPreconditionerLanczos ( const Vector & jacobiPreconditioner )
// {
//   this->jacobiPreconditioner = jacobiPreconditioner;
// }
    
int ILSConjugateGradientsLanczos::solveLin ( const GenericMatrix & gm, const Vector & b, Vector & x )
{
  if ( b.size() != gm.rows() ) {
    fthrow(Exception, "Size of vector b (" << b.size() << ") mismatches with the size of the given GenericMatrix (" << gm.rows() << ").");
  }

  if ( x.size() != gm.cols() )
  {
    x.resize(gm.cols());
    x.set(0.0); // bad initial solution, but whatever
  }

//   if ( verbose ) cerr << "initial solution: " << x << endl;

  // CG-Method based on Lanczos vectors: implementation based on the following:
  //
  // C.C. Paige and M.A. Saunders: "Solution of sparse indefinite systems of linear equations". SIAM Journal on Numerical Analysis, p. 617--629, vol. 12, no. 4, 1975
  // 
  // http://www.netlib.org/templates/templates.pdf
  //

  // init some helping vectors
  Vector Av(b.size(),0.0); // Av = A * v_j
  Vector Ac(b.size(),0.0); // Ac = A * c_j
  Vector r(b.size(),0.0); // current residual
  Vector *v_new = new Vector(x.size(),0.0); // new Lanczos vector v_j
  Vector *v_old = new Vector(x.size(),0.0); // Lanczos vector v_{j-1} of the iteration before 
  Vector *v_older = 0; // Lanczos vector v_{j-2} of the iteration before 
  Vector *c_new = new Vector(x.size(),0.0); // current update vector c_j for the solution x
  Vector *c_old = 0; // update vector of iteration before

  // declare some helpers
  double d_new = 0; // current element of diagonal matrix D normally obtained from Cholesky factorization of tridiagonal matrix T, where T consists alpha and beta as below
  double d_old = 0; // corresponding element of the iteration before
  double l_new = 0; // current element of lower unit bidiagonal matrix L normally obtained from Cholesky factorization of tridiagonal matrix T
  double p_new = 0; // current element of vector p, where p is the solution of the modified linear system
  double p_old = 0; // corresponding element of the iteration before
  double alpha = 0; // alpha_j = v_j^T * A * v_j for new Lanczos vector v_j
  double beta = b.normL2(); // beta_1 = norm(b), in general beta_j = norm(v_j) for new Lanczos vector v_j
  
  // first iteration + initialization, where b will be used as the first Lanczos vector
  *v_new = (1/beta)*b; // init v_1, v_1 = b / norm(b)
  gm.multiply(Av,*v_new); // Av = A * v_1
  alpha = v_new->scalarProduct(Av); // alpha_1 = v_1^T * A * v_1
  d_new=alpha; // d_1 = alpha_1, d_1 is the first element of diagonal matrix D
  p_new = beta/d_new; // p_1 = beta_1 / d_1
  
  *c_new = *v_new; // c_1 = v_1
  Ac = Av; // A*c_1 = A*v_1
  
  // store current solution
  Vector current_x = (p_new*(*c_new)); // first approx. of x: x_1 = p_1 * c_1

  // calculate current residual
  r = b - (p_new*Ac);
  double res = r.scalarProduct(r);
  
  // store minimal residual
  double res_min = res;
  
  // store optimal solution in output variable x
  x = current_x;
  
  double delta_x = fabs(p_new) * c_new->normL2();
  if ( verbose ) {
    cerr << "ILSConjugateGradientsLanczos: iteration 1 / " << maxIterations << endl;
    if ( current_x.size() <= 20 )
      cerr << "ILSConjugateGradientsLanczos: current solution " << current_x << endl;
    cerr << "ILSConjugateGradientsLanczos: delta_x = " << delta_x << endl;
    cerr << "ILSConjugateGradientsLanczos: residual = " << r.scalarProduct(r) << endl;
  }  
  
  // start with second iteration
  uint j = 2;
  while (j <= maxIterations )
  {
    // prepare d and p for next iteration
    d_old = d_new;
    p_old = p_new;
    
    // prepare vectors v_older, v_old, v_new for next iteration
    if ( v_older == 0) v_older = v_old;
    else {
      
      delete v_older;
      v_older = v_old;
    }
    v_old = v_new;
    v_new = new Vector(v_old->size(),0.0);
    
    // prepare vectors c_old, c_new for next iteration
    if ( c_old == 0 ) c_old = c_new;
    else {
      
      delete c_old;
      c_old = c_new;
    }
    c_new = new Vector(c_old->size(),0.0);
    
    //start next iteration:
    // calulate new Lanczos vector v_j based on older ones
    *v_new = Av - (alpha*(*v_old)) - (beta*(*v_older)); // unnormalized v_j = ( A * v_{j-1} ) - ( alpha_{j-1} * v_{j-1} ) - ( beta_{j-1} * v_{j-2} )

    // calculate new weight beta_j and normalize v_j
    beta = v_new->normL2(); // beta_j = norm(v_j) 
    v_new->normalizeL2(); // normalize v_j 

    // calculate new weight alpha_j
    gm.multiply(Av,*v_new); // Av = A * v_j
    alpha = v_new->scalarProduct(Av); // alpha_j =  v_j^T * A * v_j

    // calculate l_j and d_j as the elements of the Cholesky Factorization of current tridiagonal matrix T, where T = L * D * L^T  with diagonal matrix D and
    // lower bidiagonal matrix L; l_j and d_j are necessary for computing the new update vector c_j for the solution x and the corresponding weight
    l_new = beta/sqrt(d_old); // unnormalized l_j = beta_j / sqrt(d_{j-1})
    d_new = alpha-(l_new*l_new); // d_j = alpha_j - l_j^2

    l_new/=sqrt(d_old); // normalize l_j by sqrt(d_{j-1})

    // calculate the new weight p_j of the new update vector c_j for the solution x
    p_new = -p_old*l_new*d_old/d_new; 

    // calculate the new update vector c_j for the solution x
    *c_new = *v_new - (l_new*(*c_old));

    // calculate new residual vector
    Ac = Av - (l_new*Ac);
    r-=p_new*Ac;
    res = r.scalarProduct(r);
    
    // update solution x
    current_x+=(p_new*(*c_new)); 
    
    if ( verbose ) {
      cerr << "ILSConjugateGradientsLanczos: iteration " << j << " / " << maxIterations << endl;
      if ( current_x.size() <= 20 )
        cerr << "ILSConjugateGradientsLanczos: current solution " << current_x << endl;
    }
    
    // store optimal x that produces smallest residual
    if (res < res_min) {
      
      x = current_x;
      res_min = res;
    }     

    // check convergence
    delta_x = fabs(p_new) * c_new->normL2();
    if ( verbose ) {
      cerr << "ILSConjugateGradientsLanczos: delta_x = " << delta_x << endl;
      cerr << "ILSConjugateGradientsLanczos: residual = " << r.scalarProduct(r) << endl;
    }  

    if ( delta_x < minDelta ) {
      if ( verbose )
        cerr << "ILSConjugateGradientsLanczos: small delta_x" << endl;
      break;
    } 
    
    j++;
  }
  
//   if ( verbose ) {
    cerr << "ILSConjugateGradientsLanczos: iterations needed: " << std::min<uint>(j,maxIterations) << endl;
    cerr << "ILSConjugateGradientsLanczos: minimal residual achieved: " << res_min << endl;
    if ( x.size() <= 20 )
      cerr << "ILSConjugateGradientsLanczos: optimal solution: " << x << endl;
//   }  
   
  delete v_new;
  delete v_old;
  delete v_older;
  delete c_new;
  delete c_old;

  return 0;
}

