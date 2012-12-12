///
///
/// @file: DownhillSimplexOptimizer.h: interface of the downhill Simplex Optimier
/// @author: Matthias Wacker, Esther Platzer, Alexander Freytag
/// @date: 27-09-2012 (last updated)
///
///

#ifndef _DOWNHILL_SIMPLEX_OPTIMIZER_H_
#define _DOWNHILL_SIMPLEX_OPTIMIZER_H_

#include <cmath>
#include "core/optimization/blackbox/SimpleOptimizer.h"


namespace OPTIMIZATION {

  ///
  /// @class DownhillSimplexOptimizer
  ///
  ///  HowToUse:
  ///
  ///  * use setWholeSimplex to initialize the whole simplex OR use setParameters()
  ///  * use setParameters() to specify one point of the simplex (currently not implemented)
  ///    the init call will then generate random disturbations to 
  ///    generate a full rank simplex
  ///  * use setDownhillParams() to use others than the default to "move"
  ///    the simplex
  ///  * call init() for setting up everything and evaluate your function on your initial simplex
  ///  * call optimize() to run the actual optimization
  ///
  ///
  /// Implemented Abort criteria:
  ///
  ///  * maximum number of iterations (currently deactivated)
  ///  * time limit exceeded (default: deactivated)
  ///  * parameter bounds
  ///  * function value tolerance (default: 1e-6)
  ///  * parameter tolerance
  ///  
  ///  Additional return reason:
  ///     - none
  ///
  class DownhillSimplexOptimizer : public SimpleOptimizer
  {
    public:

      typedef SimpleOptimizer SuperClass;
      typedef SuperClass::matrix_type matrix_type;
      ///
      /// Constructor
      /// @param loger : OptLogBase * to existing log class or NULL
      ///
      DownhillSimplexOptimizer(OptLogBase *loger=NULL);

      ///
      /// CopyConstructor
      /// @param opt : DownhillSimplexOptimizer to copy
      ///
      DownhillSimplexOptimizer(const DownhillSimplexOptimizer &opt);

      ///
      ///
      ///
      ~DownhillSimplexOptimizer();
      


      ///
      /// set downhill specific parameters
      /// @param alpha
      /// @param beta
      /// @param gamma
      ///
      void setDownhillParams(const double alpha, const double beta, const double gamma);
          
      ///
      /// Sets the rank deficiency threshold
      /// @param rankdeficiencythresh rank deficiency threshold (DEFAULT= 0.01)
      ///
      void setRankDeficiencyThresh(float rankdeficiencythresh);
      
      ///
      /// Enable or disable the rank check
      /// @param status give the status for a rank check
      ///
      void setRankCheckStatus(bool status);
      
      /**
      * @brief get the downhill simplex parameter alpha, needed for the reflection
      * @date 27-09-2012
      * @author Alexander Freytag
      */        
      double getDownhillParameterAlpha() const;
      
      /**
      * @brief get the downhill simplex parameter alpha, needed for the contraction
      * @date 27-09-2012
      * @author Alexander Freytag
      */        
      double getDownhillParameterBeta() const;
      
      /**
      * @brief get the downhill simplex parameter alpha, needed for the expansion
      * @date 27-09-2012
      * @author Alexander Freytag
      */        
      double getDownhillParameterGamma() const;
      
      ///
      /// Returns the status of rankcheck
      /// @retval true, if rankcheck is enabled
      /// @retval false, if rankcheck is disabled
      ///
      bool getRankCheckStatus();

      ///
      /// Do internal initializations
      ///
      void init();

    protected:
      ///
      /// start optimization
      ///
      virtual int optimize();

      
    private:
      ///
      /// Initialize the whole simplex, for that, numOfParameters+1 points a needed.
      /// (You might want to detemine these points by a random search before)
      /// @param simplex : Matrix containing numOfParameters+1 points 
      ///                 that are numOfParameters-dimensional
      /// @return bool : indicating if attempt was successfull 
      ///               (might not, if dimensions don't match)
      ///
      bool setWholeSimplex(const matrix_type &simplex);
      
      ///
      /// internal bool to store if simplex is initialized
      ///
      bool m_simplexInitialized;
      
      
      ///
      /// internal bool to offer a break in all internal functions
      ///
      bool m_abort;

      ///
      /// internal parameter to control the transformations of the simplex
      ///
      double m_alpha;
      
      ///
      /// internal parameter to control the transformations of the simplex
      ///
      double m_gamma;
      
      ///
      /// internal parameter to control the transformations of the simplex
      ///
      double m_beta;



      ///
      /// This method does the optimization itself.
      /// It is called by optimize and returns the index of the "final"
      /// vertice matrix that is the lowest / highest point found (int).
      ///
      int amoeba();

      ///
      /// This method does the extrapolation of highest vertice through the
      /// simplex by the factor fac. It is called by amoeba()
      ///
      double amotry(matrix_type& psum,int ihi, double fac);

      ///
      /// Matrix containing the vertices of the simplex
      ///
      matrix_type m_vertices;
      
      ///
      /// Matrix(1dim) containing the function values corresponding to 
      /// vertices
      ///
      matrix_type m_y;

      ///
      /// Rang deficiency threshold
      ///
      float m_rankdeficiencythresh;
      
      ///
      /// Rank check status: if false, a rank check is disabled (default)
      ///
      bool m_rankcheckenabled;
  }; //class

//       ///
//       /// Check Rank of a matrix_type where singular values lower than numZero
//       /// are treated as zero. The computation is done by singular value
//       /// decomposition. Returns the numerical rank 
//       /// of the matrix
//       ///
//       /// @param A matrix to compute rank of..
//       /// @param numZero threshold to decide for numerical zero
//       /// @return (numerical) rank of A
//       ///
//       unsigned int getRank(const optimization::matrix_type& A, double numZero);
      
} // namespace
    
#endif

