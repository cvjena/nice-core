/** 
* @file ILSSymmLqLanczos.cpp
* @brief Iteratively solving linear equation systems with the symmetric LQ (SYMMLQ) method using Lanczos process
* @author Paul Bodesheim
* @date 20/01/2012 (dd/mm/yyyy)

*/
#include <iostream>

#include "ILSSymmLqLanczos.h"

using namespace NICE;
using namespace std;


ILSSymmLqLanczos::ILSSymmLqLanczos( bool verbose, uint maxIterations, double minDelta) //, bool useFlexibleVersion )
{
  this->minDelta = minDelta;
  this->maxIterations = maxIterations;
  this->verbose = verbose;
//   this->useFlexibleVersion = useFlexibleVersion;
}

ILSSymmLqLanczos::~ILSSymmLqLanczos()
{
}

// void ILSSymmLqLanczos::setJacobiPreconditionerLanczos ( const Vector & jacobiPreconditioner )
// {
//   this->jacobiPreconditioner = jacobiPreconditioner;
// }
    
int ILSSymmLqLanczos::solveLin ( const GenericMatrix & gm, const Vector & b, Vector & x )
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

  // SYMMLQ-Method based on Lanczos vectors: implementation based on the following:
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
  double z_new = 0.0;
  double z_old = 0.0;
  double z_older = 0.0;
  double delta_new = 0.0;
  double epsilon_next = 0.0;

  // init some helping vectors
  Vector Av(b.size(),0.0); // Av = A * v_j
  Vector Ac(b.size(),0.0); // Ac = A * c_j
  Vector *v_new = new Vector(b.size(),0.0); // new Lanczos vector v_j
  Vector *v_old = 0; // Lanczos vector of the iteration before: v_{j-1}
  Vector *v_next = new Vector(b.size(),0.0); // Lanczos vector of the next iteration: v_{j+1}
  Vector *w_new = new Vector(b.size(),0.0); 
  Vector *w_bar = new Vector(b.size(),0.0); 
  Vector x_L (b.size(),0.0); 
//   Vector x_C (b.size(),0.0); // x_C is a much better approximation than x_L (according to the paper mentioned above)
// NOTE we store x_C in output variable x and only update this solution if the residual decreases (we are able to calculate the residual of x_C without calculating x_C)
  
  // first iteration + initialization, where b will be used as the first Lanczos vector
  *v_new = (1/beta)*b; // init v_1, v_1 = b / norm(b)
  gm.multiply(Av,*v_new); // Av = A * v_1
  alpha = v_new->scalarProduct(Av); // alpha_1 = v_1^T * A * v_1  
  gamma_bar = alpha; // (gamma_bar_1 is equal to alpha_1 in ILSConjugateGradientsLanczos)
  *v_next = Av - (alpha*(*v_new));
  beta_next = v_next->normL2();
  v_next->normalizeL2();
  
  gamma = sqrt( (gamma_bar*gamma_bar) + (beta_next*beta_next) );
  c_new = gamma_bar/gamma;
  s_new = beta_next/gamma;
  
  z_new = beta/gamma;
  
  *w_bar = *v_new;
  
  *w_new = c_new*(*w_bar) + s_new*(*v_next);
  *w_bar = s_new*(*w_bar) - c_new*(*v_next);
  
  x_L = z_new*(*w_new); // first approximation of x
  
  // calculate current residual of x_C
  double res_x_C = (beta*beta)*(s_new*s_new)/(c_new*c_new);
  
  // store minimal residual
  double res_x_C_min = res_x_C;
  
  // store optimal solution x_C in output variable x instead of additional variable x_C
  x = x_L + (z_new/c_new)*(*w_bar); // x_C = x_L + (z_new/c_new)*(*w_bar); 
  
  // calculate delta of x_L
  double delta_x_L = fabs(z_new) * w_new->normL2();
  if ( verbose ) {
    cerr << "ILSSymmLqLanczos: iteration 1 / " << maxIterations << endl;
    if ( x.size() <= 20 )
      cerr << "ILSSymmLqLanczos: current solution x_L: " << x_L << endl;
    cerr << "ILSSymmLqLanczos: delta_x_L = " << delta_x_L << endl;
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
    beta = beta_next;
    z_older = z_old;
    z_old = z_new;
    s_old = s_new;
    res_x_C *= (c_new*c_new);
    
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
    
    // calculate next component z_{j} of vector z
    z_new = - (delta_new*z_old + epsilon_next*z_older)/gamma;
    
    //NOTE updating epsilon_next after using it to calculate z_new is important!!
    epsilon_next = s_old*beta_next; // calculate epsilon_{j+1} of matrix L_bar_{j+1}

    // calculate residual of current solution x_C without computing this solution x_C before
    res_x_C *= (s_new*s_new)/(c_new*c_new);
    
    // we only update our solution x (originally x_C ) if the residual is smaller
    if ( res_x_C < res_x_C_min ) 
    {
      x = x_L + (z_new/c_new)*(*w_bar);  // x_C = x_L + (z_new/c_new)*(*w_bar); // update x
      res_x_C_min = res_x_C;
    }
        
    // calculate new vectors w_{j} and w_bar_{j+1} according to equation 5.9 of the paper mentioned above
    *w_new = c_new*(*w_bar) + s_new*(*v_next);
    *w_bar = s_new*(*w_bar) - c_new*(*v_next);
   
    x_L += z_new*(*w_new); // update x_L
        
    if ( verbose ) {
      cerr << "ILSSymmLqLanczos: iteration " << j << " / " << maxIterations << endl;
      if ( x.size() <= 20 )
        cerr << "ILSSymmLqLanczos: current solution x_L: " << x_L << endl;
    }

    // check convergence
    delta_x_L = fabs(z_new) * w_new->normL2();
    if ( verbose ) {
      cerr << "ILSSymmLqLanczos: delta_x_L = " << delta_x_L << endl;
      cerr << "ILSSymmLqLanczos: residual = " << res_x_C << endl;
    }  

    if ( delta_x_L < minDelta ) {
      if ( verbose )
        cerr << "ILSSymmLqLanczos: small delta_x_L" << endl;
      break;
    } 
    
    j++;
  }
  
//   if ( verbose ) {
    cerr << "ILSSymmLqLanczos: iterations needed: " << std::min<uint>(j,maxIterations) << endl;
    cerr << "ILSSymmLqLanczos: minimal residual achieved: " << res_x_C_min << endl;
    if ( x.size() <= 20 )
      cerr << "ILSSymmLqLanczos: optimal solution: " << x << endl;
//   }
  
//  WE DO NOT WANT TO CALCULATE THE RESIDUAL EXPLICITLY  
//  
//   Vector tmp;
//   gm.multiply(tmp,x_C);
//   Vector res ( b - tmp );
//   double res_x_C = res.scalarProduct(res);
//   
//   gm.multiply(tmp,x_L);
//   res = b - tmp;
//   double res_x_L = res.scalarProduct(res);
//   
//   if ( res_x_L < res_x_C )
//   {
//     x = x_L;
//     if ( verbose )
//       cerr << "ILSSymmLqLanczos: x_L used with residual " << res_x_L << " < " << res_x_C << endl;
//     
//   } else 
//   {
//     
//     x = x_C;
//     if ( verbose )
//       cerr << "ILSSymmLqLanczos: x_C used with residual " << res_x_C << " < " << res_x_L << endl;    
//     
//   }
   
  delete v_new;
  delete v_old;
  delete v_next;
  delete w_new;
  delete w_bar;
  
  return 0;
}

