/** 
* @file ILSMinResLanczos.cpp
* @brief Iteratively solving linear equation systems with the minimum residual (MINRES) method using Lanczos process
* @author Paul Bodesheim
* @date 20/01/2012 (dd/mm/yyyy)

*/
#include <iostream>

#include "ILSMinResLanczos.h"

using namespace NICE;
using namespace std;


ILSMinResLanczos::ILSMinResLanczos( bool verbose, uint maxIterations, double minDelta) //, bool useFlexibleVersion )
{
  this->minDelta = minDelta;
  this->maxIterations = maxIterations;
  this->verbose = verbose;
//   this->useFlexibleVersion = useFlexibleVersion;
}

ILSMinResLanczos::~ILSMinResLanczos()
{
}

// void ILSMinResLanczos::setJacobiPreconditionerLanczos ( const Vector & jacobiPreconditioner )
// {
//   this->jacobiPreconditioner = jacobiPreconditioner;
// }
    
int ILSMinResLanczos::solveLin ( const GenericMatrix & gm, const Vector & b, Vector & x )
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

  // MINRES-Method based on Lanczos vectors: implementation based on the following:
  //
  // C.C. Paige and M.A. Saunders: "Solution of sparse indefinite systems of linear equations". SIAM Journal on Numerical Analysis, p. 617--629, vol. 12, no. 4, 1975
  // 
  // http://www.netlib.org/templates/templates.pdf
  //
  
  // declare some helpers
  double gamma = 0.0;
  double gamma_bar = 0.0;
  double alpha = 0.0; // alpha_j = v_j^T * A * v_j for new Lanczos vector v_j
  double beta = b.normL2(); // beta_1 = norm(b), in general beta_j = norm(v_j) for new Lanczos vector v_j
  double beta_next = 0.0; // beta_{j+1}
  double c_new = 0.0;
  double c_old = -1.0;
  double s_new = 0.0;
  double s_old = 0.0;
  double delta_new = 0.0;
  double epsilon_next = 0.0;
  double t_new = 0.0;

  // init some helping vectors
  Vector Av(b.size(),0.0); // Av = A * v_j
  Vector Ac(b.size(),0.0); // Ac = A * c_j
  Vector *v_new = new Vector(b.size(),0.0); // new Lanczos vector v_j
  Vector *v_old = 0; // Lanczos vector of the iteration before: v_{j-1}
  Vector *v_next = new Vector(b.size(),0.0); // Lanczos vector of the next iteration: v_{j+1}
  Vector *m_new = new Vector(x.size(),0.0); // current update vector m_j for the solution x
  Vector *m_old = new Vector(x.size(),0.0); // update vector m_{j-1} of iteration before
  Vector *m_older = 0; // update vector m_{j-2} of iteration before
  
  // first iteration + initialization, where b will be used as the first Lanczos vector
  *v_new = (1/beta)*b; // init v_1, v_1 = b / norm(b)
  gm.multiply(Av,*v_new); // Av = A * v_1
  alpha = v_new->scalarProduct(Av); // alpha_1 = v_1^T * A * v_1  
  gamma_bar = alpha; // (gamma_bar_1 is equal to alpha_1 in ILSConjugateGradientsLanczos)
  *v_next = Av - (alpha*(*v_new));
  beta_next = v_next->normL2();
  v_next->normalizeL2();
  
  // calculate helpers (equation 5.6 in the paper mentioned above)
  gamma = sqrt( (gamma_bar*gamma_bar) + (beta_next*beta_next) );
  c_new = gamma_bar/gamma;
  s_new = beta_next/gamma;

  t_new = beta*c_new; // t_1 = beta_1 * c_1
  *m_new = (1/gamma)*(*v_new); // m_1 = ( 1 / gamma_1 ) * v_1
  
  x = t_new*(*m_new); // first approximation of x
  
  // calculate current residual of x
  double res = (beta*beta)*(s_new*s_new);
  
  // calculate delta of x_L
  double delta_x = fabs(t_new) * m_new->normL2();
  if ( verbose ) {
    cerr << "ILSMinResLanczos: iteration 1 / " << maxIterations << endl;
    if ( x.size() <= 20 )
      cerr << "ILSMinResLanczos: current solution x: " << x << endl;
    cerr << "ILSMinResLanczos: delta_x = " << delta_x << endl;
  }
  
  // start with second iteration
  uint j = 2;
  while (j <= maxIterations )
  {
  
    // prepare next iteration
    if ( v_old == 0 ) v_old = v_new;
    else {
      
      delete v_old;
      v_old = v_new;
    }
    v_new = v_next;
    v_next = new Vector(b.size(),0.0);

    if ( m_older == 0 ) m_older = m_old;
    else {
      
      delete m_older;
      m_older = m_old;
    }     
    m_old = m_new;
    m_new = new Vector(x.size(),0.0);

    beta = beta_next;
    s_old = s_new;
    t_new /= c_new;
    
    // start next iteration:
    // calculate next Lanczos vector v_ {j+1} based on older ones
    gm.multiply(Av,*v_new);
    alpha = v_new->scalarProduct(Av);
    *v_next = Av - (alpha*(*v_new)) - (beta*(*v_old)); // calculate v_{j+1} 
    beta_next = v_next->normL2(); // calculate beta_{j+1} 
    v_next->normalizeL2(); // normalize v_{j+1}  
    
    // calculate elements of matrix L_bar_{j}
    gamma_bar = -c_old*s_new*beta - c_new*alpha; // calculate gamma_bar_{j} 
    delta_new = -c_old*c_new*beta + s_new*alpha; // calculate delta_{j} 
    
    //NOTE updating c_old after using it to calculate gamma_bar and delta_new is important!!
    c_old = c_new;
    
    // calculate helpers (equation 5.6 in the paper mentioned above)
    gamma = sqrt( (gamma_bar*gamma_bar) + (beta_next*beta_next) ); // calculate gamma_{j}
    c_new = gamma_bar/gamma; // calculate c_{j-1}
    s_new = beta_next/gamma; // calculate s_{j-1}
    
    // calculate t_{j} according to equation 6.7 of the paper mentioned above
    t_new *= s_old*c_new;
    
    // calculate m_{j}
    *m_new = (1/gamma)*(*v_new - (delta_new*(*m_old)) - (epsilon_next*(*m_older)) );
       
    epsilon_next = s_old*beta_next; // calculate epsilon_{j+1} of matrix L_bar_{j+1}
      
    x += t_new*(*m_new); // update x

    // calculate residual of current solution x 
    res *= (s_new*s_new);
    
    if ( verbose ) {
      cerr << "ILSMinResLanczos: iteration " << j << " / " << maxIterations << endl;
      if ( x.size() <= 20 )
      {
        cerr << "ILSMinResLanczos: current solution x: " << x << endl;
      }
    }

    // check convergence
    delta_x = fabs(t_new) * m_new->normL2();
    if ( verbose ) {
      cerr << "ILSMinResLanczos: delta_x = " << delta_x << endl;
      cerr << "ILSMinResLanczos: residual = " << res << endl;
    }  

    if ( delta_x < minDelta ) {
      if ( verbose )
        cerr << "ILSMinResLanczos: small delta_x" << endl;
      break;
    } 
    
    j++;
  }

  // Normally, we do not need this, because the last iteration produces the optimal solution with minimal residual. 
  // However, we will have this outputs equally to the other ILS methods.
//   if ( verbose ) {
    cerr << "ILSMinResLanczos: iterations needed: " << std::min<uint>(j,maxIterations) << endl;
    cerr << "ILSMinResLanczos: minimal residual achieved: " << res << endl;
    if ( x.size() <= 20 )
      cerr << "ILSMinResLanczos: optimal solution: " << x << endl;
//   }
  
  delete v_new;
  delete v_old;
  delete v_next;
  delete m_new;
  delete m_old;
  delete m_older;
  
  return 0;
}

