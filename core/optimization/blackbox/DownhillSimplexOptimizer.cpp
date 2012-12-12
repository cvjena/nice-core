/**
*
* @file: DownhillSimplexOptimizer.cpp: implementation of the downhill Simplex Optimier
*
* @author: Matthias Wacker, Esther Platzer, Alexander Freytag
*
*/

#include <iostream>

// #include "mateigen.h" // for SVD

#include "core/optimization/blackbox/DownhillSimplexOptimizer.h"
#include "core/optimization/blackbox/Definitions_core_opt.h"

using namespace OPTIMIZATION;

DownhillSimplexOptimizer::DownhillSimplexOptimizer(OptLogBase *loger): SuperClass(loger)
{
  m_abort = false;
  m_simplexInitialized = false;
  //note that we use the negative value of alpha in amoeba
  m_alpha = 1.0;
  m_beta = 0.5;
  // m_gamma was previously 1.0, but this actually deactivates extrapolation. We use 2.0 as suggested in Num. Recipes
  m_gamma = 2.0;
  m_rankdeficiencythresh = 0.01;
  m_rankcheckenabled = false;
}

DownhillSimplexOptimizer::DownhillSimplexOptimizer(const DownhillSimplexOptimizer &opt) : SuperClass(opt)
{
  m_abort = opt.m_abort;
  m_simplexInitialized = opt.m_simplexInitialized;
  m_vertices = opt.m_vertices;
  m_y = opt.m_y;
  m_alpha = opt.m_alpha;
  m_beta = opt.m_beta;
  m_gamma = opt.m_gamma;
  m_rankdeficiencythresh= 0.01;
  m_rankcheckenabled= false;
}

DownhillSimplexOptimizer::~DownhillSimplexOptimizer()
{
}

bool DownhillSimplexOptimizer::setWholeSimplex(const matrix_type &simplex)
{
  if((int)simplex.rows() == static_cast<int>(m_numberOfParameters) && (int)simplex.cols() == static_cast<int>(m_numberOfParameters + 1))
  {
    //Check if simplex has rank(simplex)=numberOfParameters
    //otherwise return false because of bad posed simplex 
    if(m_rankcheckenabled)
    {
      //TODO do we need this?!?!?!
        int rank = 0;
//         getRank(simplex, m_rankdeficiencythresh);
        
        if(rank < static_cast<int>(m_numberOfParameters))
        {
            m_simplexInitialized = false;
            return false;
        }
    }

    m_vertices = simplex;
    m_simplexInitialized = true;
    
    for (int k = 0; k < static_cast<int>(m_numberOfParameters +1); k++)
    {
        m_y(k,0) = evaluateCostFunction(m_vertices(0,k,m_numberOfParameters-1,k));
    }
        
    return true;
  }
  else
  {
    m_simplexInitialized = false;
    return false;
  }
}

void DownhillSimplexOptimizer::init()
{
  SuperClass::init();
  
  // allocate matrices
  m_vertices = matrix_type(m_numberOfParameters, m_numberOfParameters + 1);
  m_y = matrix_type(m_numberOfParameters + 1,1);

  m_abort = false;
  
  //this forces a re-initialization in all cases
  //it is even more advisable, if we would perform a random initialization
  //remark of erik: there was a bug here
  m_simplexInitialized = false;

  // previously, we did a random initialization
  // right now, we rely on our first guess and move it in one dimension by m_scales[i]
  // as suggested in Numerical Recipes
  if (m_simplexInitialized == false)
  {
    //this aborting stuff was formerly needed to ensure a valid simplex for random initializations
    bool abort = false;
    while(abort == false)
    {
      matrix_type simplex(m_numberOfParameters,m_numberOfParameters+1);      

      //move every point in a single dimension by m_scales[i]
      //we first iterate over dimensions
      for(int i = 0; i < static_cast<int>(m_numberOfParameters); i++)
      {
        //and internally over the different points
        for(int j = 0; j < static_cast<int>(m_numberOfParameters+1); j++)
        {
          simplex(i,j) = m_parameters(i,0);
          
          if( j == i+1 )
          {
            double tmpRand = m_scales(i,0);// * ((double)rand()) / RAND_MAX;
            simplex(i,j) += tmpRand;
          }
        }
      }
      
      //evaluate function values in simplex corners and 
      //check if simplex is degenerated (less than d dimensions)
      if(this->setWholeSimplex(simplex) == true)
      {
        // simplexInitializen is only to indicate manual initialization ..
        //actually, this is not needed anymore.
        m_simplexInitialized = false;
        //we computed a valid solution, so break the while loop
        //actually, this is always the case, since we de-activated the random init
        abort =true;
      }
    }
  }
  // if the simplex was already initialized, we only have to compute the function values
  // of its corners
  else
  {
    //compute the function values of the initial simplex points
    for (int k = 0; k < static_cast<int>(m_numberOfParameters +1); k++)
    {
      m_y(k,0) = evaluateCostFunction(m_vertices(0,k,m_numberOfParameters-1,k));
    }
  }
}


int DownhillSimplexOptimizer::optimize()
{
  //before optimizing, we initialize our simplex in all cases
  // if you are pretty sure, that you already have a suitable initial
  // simplex, you can skip this part
  
  //if(m_simplexInitialized == false)
  //{
      this->init();
  //}

  if(m_loger)
    m_loger->logTrace("Starting Downhill Simplex Optimization\n");

  //tmp contains the index of the best vertex point after running DHS
  int tmp=amoeba();
  m_parameters = m_vertices(0,tmp,m_numberOfParameters-1,tmp);

  //final evaluation of the cost function with our optimal parameter settings
  m_currentCostFunctionValue = evaluateCostFunction(m_parameters);
  return m_returnReason;
}


/*
* Taken from Numerical Recipies in C
*/
int DownhillSimplexOptimizer::amoeba()
{
  //define the desired tolerance of our solution
  double tol = m_funcTol;

  //how many parameters do we optimize?
  const int ndim=m_numberOfParameters;
  if (m_verbose)
  {
    std::cerr << "ndim: " << ndim << std::endl;
  }  

  // number of vertices
  const int spts=ndim+1;
  int i,j, max_val;
    
  // index of worst (lowest) vertex-point
  int ilo;
  // index of best (hightest) vertex point
  int ihi;
  // index of second worst (next hightest) vertex point
  int inhi;

  double rtol,ytry;
    
  // buffer to save a function value 
  double ysave;
  matrix_type psum(1,ndim);

  //start time criteria
  m_startTime = clock();

  // get sum of vertex-coordinates
  for (j=0;j<ndim;j++)
  { 
    double sum(0.0);
    for (i=0;i<spts;i++)
      sum += m_vertices(j,i);
    psum(0,j)=sum;
  }
    
  if (m_verbose)
  {
    std::cerr << "initial psum: ";
    for (j=0;j<ndim;j++)
    { 
      std::cerr << psum(0,j) << " " ;
    }
    std::cerr << std::endl;    
  }
  
  // loop until terminating
  //this is our main loop for the whole optimization
  for (;;)
  {
    //what is our current solution?
    if(m_verbose)
    {
      for(int u = 0; u < ndim+1; u++)
      {
        for(int v = 0; v < ndim ; v++)
        {
          std::cerr << m_vertices(v,u) << " ";
        }
        std::cerr<< " " << m_y(u,0) << std::endl;
      }
      std::cerr << std::endl;
    }


    // first we must determine 
    // which point is highest, 
    // next-highest
    // and lowest
    // by looping over the simplex
    ilo = 0;

    //this works only, if m_numberOfParameters=ndim >= 2
    if(ndim >= 2)
    {
      ihi = m_y(1,0)>m_y(2,0) ? (inhi=1,2) : (inhi=2,1);   
      for (i=0;i<spts;i++)
      {                             
        if (m_y(i,0) <= m_y(ilo,0)) ilo=i;
        if (m_y(i,0) > m_y(ihi,0)) {
          inhi=ihi;
          ihi=i;
        }
        else
          if ( m_y(i,0) > m_y(inhi,0) )
            if (i != ihi) 
              inhi=i;
      }
    }
    //if we have less than 3 dimensions, the solution is straight forward
    else
    {
      if(m_y(0,0)>m_y(1,0))
      {
        ilo  = 1;
        inhi = 1;
        ihi  = 0;
      }
      else
      {
        ilo  = 0;
        inhi = 0;
        ihi  = 1;
      }
    }
    
    // log parameters if parameter logger is given (does nothing for other loggers!)
    if(m_loger)
    {
      // extract optimal parameters from simplex
      matrix_type optparams(m_vertices.rows(),1,0);

      for(int i= 0; i< (int)m_vertices.rows(); ++i)
      {
          optparams(i,0)= m_vertices(i,ilo);
      }
      matrix_type fullparams= m_costFunction->getFullParamsFromSubParams(optparams);
      m_loger->writeParamsToFile(fullparams);
    }
    
    //Check m_abort .. outofbounds may have occurred in amotry() of last iteration
    if(m_abort == true)
    {
      break;
    }

    //Check time criterion
    //in the default setting, this is deactivated
    if(m_maxSecondsActive)
    {
      m_currentTime = clock();

      /* time limit exceeded ? */
      if(((float)(m_currentTime - m_startTime )/CLOCKS_PER_SEC) >= m_maxSeconds )
      {
        /* set according return status and end optimization */
        m_returnReason = SUCCESS_TIMELIMIT;
        break;
      }
    }

    
    //check functol criterion
    if(m_funcTolActive == true)
    {
      // compute the fractional 
      // range from highest to lowest    
      // avoid division by zero
      rtol=2.0*fabs(m_y(ihi,0)-m_y(ilo,0))/(fabs(m_y(ihi,0))+fabs(m_y(ilo,0))+1e-10);
      
      #ifdef OPT_DEBUG        
        std::cout<<"rtol"<<"  "<<rtol<< std::endl;
      #endif    
      
      // if the found solution is satisfactory, than terminate
      if (rtol<tol)  
      {
        // save lowest value, which is our desired solution
        max_val=(int)m_y(ilo,0);
        m_returnReason = SUCCESS_FUNCTOL;
        //break the main loop and end this method
        break;
      }
    }

    //check param tol criterion
    if (m_paramTolActive == true)
    {
      // get norm of
      //matrix_type tmp = m_vertices(0,ihi,m_numberOfParameters-1,ihi) - m_vertices(0,ilo,m_numberOfParameters,ilo);
      //double norm)
      if (   (m_vertices(0,ihi,m_numberOfParameters-1,ihi) - 
        m_vertices(0,ilo,m_numberOfParameters-1,ilo)).frobeniusNorm() < m_paramTol)
      {
        /*
          set according return reason and end optimization
        */
        m_returnReason = SUCCESS_PARAMTOL;
        break;
      }
    }
    
    m_numIter++;

    //check max num iter criterion
    if(m_maxNumIterActive == true)
    {
      if (m_numIter >= m_maxNumIter)
      {                   
        //max_val=(int)m_y[ilo][0];
        m_returnReason = SUCCESS_MAXITER;
        break;
      }
    }
    
    //informative output
    if (m_verbose)
    {    
      std::cerr << "start new iteration with amotry -alpha, i.e., reflect worst point through simplex" << std::endl;
    }

    // Begin a new iteration. 
    // First extrapolate by the 
    // factor alpha through the 
    // face of the simplex across 
    // from the high point, i.e. 
    // reflect the simplex from the
    // high point:
    ytry=amotry(psum,ihi,-m_alpha);
    //did we got a new point better than anything else so far?
    if ( ytry < m_y(ilo,0) )
    {
      //informative output
      if (m_verbose)
      {
        std::cerr << "reflected point is better than best point, perform further extrapolation with gamma" << std::endl;
      }

      // result is better than best
      // point, try additional 
      // extrapolation
      ytry=amotry(psum,ihi,m_gamma);
      
      #ifdef OPT_DEBUG        
        std::cout<<"Case one .. reflected highest through simplex" << std::endl;
      #endif
    }
    //new point is not better as anything else
    else
    {
      //perhaps it is better than our second worst point
      if ( ytry >= m_y(inhi,0) ) 
      {
        //informative output
        if (m_verbose)
        {
          std::cerr << "reflected point is worse then second worst, looking for intermediate point with beta" << std::endl;
        }

        // The reflected point is worse
        // than the second worst
        ysave=m_y(ihi,0);

        // let's  look for an intermediate lower point.
        ytry=amotry(psum,ihi,m_beta);
        #ifdef OPT_DEBUG        
          std::cout<<"Case two .. looking for intermediate point" << std::endl;
        #endif   
        //unfortunately, the intermediate point is still worse
        //then the original one
        if (ytry >= ysave)
        {
          #ifdef OPT_DEBUG        
            std::cout<<"Case three .. contract around lowest point" << std::endl;
          #endif 
          //informative output
          if (m_verbose)
          {
            std::cerr <<  "Intermediate point is also worse, contract around current best point with factor 0.5." << std::endl;
          }
          // Since we can't get rid 
          // of that bad point, we better 
          // our simplex around the current best point
          // note: contraction is performed by a factor of 0.5
          // as suggested in Numerical Recipes
          
          //contract all points
          for (i=0;i<spts;i++) 
          {
            // but the best point has not to be contracted
            if (i!=ilo) 
            {
              //contract in every dimension
              for (j=0;j<ndim;j++) 
              {
                psum(0,j)=0.5*(m_vertices(j,i)+m_vertices(j,ilo) ); 
                #ifdef OPT_DEBUG                    
                printf( "psum(%d)=%f\n",j,psum(0,j) );
                #endif                  
                m_vertices(j,i)=psum(0,j);
              }
              //TODO what does this?
              if (checkParameters(!psum)) 
              {
                m_y(i,0)=  evaluateCostFunction(!psum); 
                // count function evaluations
                //not needed in the current implementation
                //eval_count++; 
              }
              else
              {    
                m_returnReason = ERROR_XOUTOFBOUNDS; // out of domain !!!
                break;
              }
            }
            // update psum: get sum of vertex-coordinates
            for (j=0;j<ndim;j++)
            {
              double sum=0.0;
              for (int ii=0;ii<spts;ii++)
                sum += m_vertices(j,ii);
              psum(0,j)=sum;
            }//for
              }//for-loop for contracting all points
        }//if (ytry >= ysave)
      }//if (ytry >= m_y(inhi))
    }//else
  }// next iteration
   
  // finally, return index of best point
  return ilo;
}


double DownhillSimplexOptimizer::amotry(matrix_type & psum, int ihi, double fac)
{
    // extrapolate by a factor fac through the face of the simplex across
    // from the low point, try this point it, and replace the low point if
    // the new point is better
    
    const double maxreal= (m_maximize == true)? -1.0e+300 : 1.0e+300;
    double fac1,fac2,ytry;
    int ndim=m_numberOfParameters;
    matrix_type ptry(1,ndim);
    
    //compute the factors as suggested in Numerical Recipes
    fac1=(1.0-fac)/ndim;
    fac2=fac1-fac;
      
    //compute the new point by performing a weighted superposition of the previous point and the surface of our simplex
    for (int j=0;j<ndim;j++) 
    {
      ptry(0,j) = psum(0,j)*fac1-m_vertices(j,ihi)*fac2;
    }

    //informative output
    if (m_verbose)
    {
      std::cerr << "amotry fac: " <<  fac << std::endl;
      std::cerr << "fac1: " << fac1 << " fac2: " << fac2 << std::endl;
      std::cerr << "ptry: ";
      for (int j=0;j<ndim;j++) 
      {
        std::cerr << ptry(0,j) << " ";
      }
      std::cerr << std::endl;
      
    }
    
    //is the new point valid?
    if (checkParameters(!ptry)) 
    { 
      // evaluate function at the 
      // new trial point
      ytry=evaluateCostFunction(!ptry);
                         
      // count function evaluations
      //not needed in the current implementation      
      // eval_count++;
      
      // if the new point is better than the old one
      // we replace the old one with the new point
      if ( ytry<m_y(ihi,0) )
      {
        //save function value of the new point
        m_y(ihi,0) = ytry;
        
        //update the surface of our simplex
        for (int j=0; j<ndim;j++)
        {
          // update psum
          psum(0,j) = psum(0,j) + ptry(0,j)-m_vertices(j,ihi);
          // replace lowest point
          m_vertices(j,ihi) = ptry(0,j);
        }
      }
    }
    // out of domain
    else 
    {
      ytry=maxreal;
      m_abort = true;
      m_returnReason = ERROR_XOUTOFBOUNDS;     
    }
    return ytry;
}


void DownhillSimplexOptimizer::setDownhillParams(const double alpha, const double beta, const double gamma)
{
  m_alpha = alpha;
  m_beta = beta;
  m_gamma = gamma;
}


void DownhillSimplexOptimizer::setRankDeficiencyThresh(float rankdeficiencythresh)
{
    m_rankdeficiencythresh= rankdeficiencythresh;
}


void DownhillSimplexOptimizer::setRankCheckStatus(bool status)
{
    m_rankcheckenabled= status;
}

double DownhillSimplexOptimizer::getDownhillParameterAlpha() const
{
  return m_alpha;
}

double DownhillSimplexOptimizer::getDownhillParameterBeta() const
{
  return m_beta;
}

double DownhillSimplexOptimizer::getDownhillParameterGamma() const
{
  return m_gamma;
}


bool DownhillSimplexOptimizer::getRankCheckStatus()
{
    return m_rankcheckenabled;
}

//only works with ICE and the method SingularValueDcmp
// unsigned int getRank(const matrix_type &A,double numZero)
// {
//   unsigned int tmpCount = 0;
//   matrix_type U,s,Vt;
// 
//   if(A.rows() < A.cols())
//   {
//     // call of the singular value decomp.
//     SingularValueDcmp(!A, U, s, Vt);
//   }
//   else
//   {
//     // call of the singular value decomp.
//     SingularValueDcmp(A, U, s, Vt);
//   }
//   
//   // count singular values > numZero
//   for(int i= 0; i < s.rows();i++)
//   {
//     if( s[i][i] > numZero )
//     {
//       tmpCount++;
//     }
//   }
//   
//   return tmpCount;
// }

