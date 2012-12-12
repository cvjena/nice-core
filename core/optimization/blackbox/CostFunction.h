//////////////////////////////////////////////////////////////////////
//
//  CostFunction.h: interface of the CostFunction class.
//
//  Written By: Matthias Wacker
//
//////////////////////////////////////////////////////////////////////

#ifndef _COST_FUNCTION_H_
#define _COST_FUNCTION_H_

#include "core/optimization/blackbox/Optimizable.h"
#include "core/optimization/blackbox/Definitions_core_opt.h"

namespace OPTIMIZATION {

  /*!
      class Abstract base class for all cost functions.
  */

  class CostFunction : public Optimizable
  {
    public:

      typedef   Optimizable   SuperClass;
      typedef OPTIMIZATION::matrix_type  matrix_type;
      
      /*!
        DefaultConstructor
      */
      CostFunction();

      /*!
        Constructor.
        \param numOfParameters
            */
      CostFunction(unsigned int numOfParamters);
          
      /*
        Copy constructor
      */
      CostFunction(const CostFunction &func);

      
      /*!
        Destructor.
      */
        virtual ~CostFunction();

      /*!
        =operator
      */
      CostFunction &operator=(const CostFunction &costFunc);


      inline bool hasAnalyticGradient(){return m_hasAnalyticGradient;}

      /*!
        get the analytic gradient
      */
      virtual const OPTIMIZATION::matrix_type getAnalyticGradient(const OPTIMIZATION::matrix_type &x);
      
      
      inline bool hasAnalyticHessian(){return m_hasAnalyticHessian;}

      /*!
        get the analytic hessian
      */
      virtual const OPTIMIZATION::matrix_type getAnalyticHessian(const OPTIMIZATION::matrix_type & x);

      /*!
        get number of Evaluations
      */
      inline unsigned int getNumberOfEvaluations(){return m_numEval;};

      /*!
        reset the evaluation counter
      */
      inline void resetNumberOfEvaluations(){m_numEval = 0;};

      /*!
        Initialization for the cost function
      */
      virtual void init();

      /*!
        set an x0 for 1dim line search
      */
      bool setX0(const OPTIMIZATION::matrix_type &x0);

      /*!
        set an h0 for 1dim line search
      */
      bool setH0(const OPTIMIZATION::matrix_type &H0);

      /*!
        evaluate 1dimension sub function fsub(lambda) = f(x0 + lambda * h0) 
      */
      double evaluateSub(double lambda);

      /*!
      * This function returns the full parameter vector. If the costfunction performs dimension reduction
      * this method will return the current parameter vector with full dimension. Otherwise the costfunction works with
      * the full parameter vector in any case and it is returned unchanged.
      * @param x current parameter vector (from optimizer)
      * @return full parameter vector
      */
      virtual OPTIMIZATION::matrix_type getFullParamsFromSubParams(const OPTIMIZATION::matrix_type &x)
      {
        matrix_type fullparamvec(x);
        return x;
      }

    protected:

      /*!
        has analytic gradient ?
      */
      bool m_hasAnalyticGradient;
    
      /*!
        has analytic hessian ?
      */
      bool m_hasAnalyticHessian;

      /*!
        x_0   
      */
      OPTIMIZATION::matrix_type m_x_0;

      /*!
        direction h_0
      */
      OPTIMIZATION::matrix_type m_h_0;

      /*!
        number of evaluations
      */
      unsigned int m_numEval;
  };
  
} // namespace  

#endif

