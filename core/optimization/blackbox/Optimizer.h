///
/// @file Optimizer.h: interface of the Optimizer class.
/// @author Matthias Wacker, Esther Platzer
///

#ifndef _OPTIMIZER_H_
#define _OPTIMIZER_H_

#include <time.h>

#include "core/optimization/blackbox/CostFunction.h"
#include "core/optimization/blackbox/OptLogBase.h"
#include "core/optimization/blackbox/Definitions_core_opt.h"

namespace OPTIMIZATION {
  /*!
    Abstract base class of all optimizers.
  */
  class Optimizer
  {
    public:
      typedef OPTIMIZATION::matrix_type matrix_type;

      ///
      /// Constructor (also Default constructor)
      /// @param optProb pointer to optimization problem object 
      /// @param loger OptLogBase * to existing log class or NULL
      ///
      Optimizer(OptLogBase *loger=NULL);

      ///
      /// Copy constructor
      /// @param opt .. optimizer to copy
      ///
      Optimizer( const Optimizer &opt);

      ///
      /// assignment opterator
      /// @param opt optimizer to "copy"
      /// @return self-reference
      ///
      Optimizer  & operator=(const Optimizer &opt);

      ///
      ///   Destructor.
            ///
            virtual ~Optimizer();
      
      ///
      /// enumeration for the return reasons of an optimizer
      ///
      enum {
        SUCCESS_FUNCTOL,
        SUCCESS_PARAMTOL,
        SUCCESS_MAXITER,
        SUCCESS_TIMELIMIT,
        ERROR_XOUTOFBOUNDS,
        ERROR_COMPUTATION_UNSTABLE,
        _to_continue_
      };

        
      ///
      /// setScales means the parameters are internally handled scaled to compensate for illposed
      /// Parameter relations. 
      /// The scales are used multiplicative: higher scales mean bigger steps
      /// (For Example rotation has much more effect than translation, 
      /// so steps should be much smaller than for translation, i.g. use small scales for the
      /// rotation parameters and higher scales for the translation parameters)
      ///
      /// @brief Set the scaling vector for the parameters.
      /// @param scales vector for the scales (i-th scale for i-th parameter dimension)
      ///
      void setScales(const OPTIMIZATION::matrix_type & scales);

      /// 
      /// @brief Get the scales
      /// 
      /// @return matrix with the scales
      ///
      inline const OPTIMIZATION::matrix_type & getScales(){return m_scales;};
      
      ///
      /// @brief Set bounds for x
      /// 
      /// Sets an upper bound for the parameter space. Optimization aborts if it iterates over these given bound.
      ///
      void setUpperParameterBound(bool active, const OPTIMIZATION::matrix_type & upperBound);
      
      ///
      /// @brief Set bounds for x.
      /// 
      /// Sets a lower bound for the parameter space. Optimization aborts if it iterates over these given bound.
      ///
      void setLowerParameterBound(bool active, const OPTIMIZATION::matrix_type & lowerBound);

      ///
      /// @brief get the upper bound
      /// @return matrix containing the upper bound
      ///
      inline const OPTIMIZATION::matrix_type & getUpperParameterBound(){  return m_upperParameterBound;};


      ///
      /// @brief get the lower parameter bound
      /// @return matrix containing the lower bound
      ///
      inline const OPTIMIZATION::matrix_type & getLowerParameterBound(){return m_lowerParameterBound;};

      ///
      /// @brief Set function tolerance abort criteria
      /// 
      /// Set function tolerance abort criteria. While iterating, if the change of the objective function between
      /// two iterations is below the given difference threshold. The optimization stops and returns SUCCESS if 
      /// active is 'true'
      ///
      /// @param active bool to activate the criteria (true == active..)
      /// @param difference double to set the threshold
      ///
      void setFuncTol(bool active, double difference);
      
      ///
      /// @brief Get the function tolerance abort criteria
      /// @return double representing the threshold
      ///
      inline double getFuncTol(){return m_funcTol;};

      ///
      /// @brief Set parameter tolerance abort criteria
      /// 
      /// Set parameter tolerance abort criteria. While iterating, if the change of the parameters between
      /// two iterations is below the given difference threshold. The optimization stops and returns SUCCESS if 
      /// active is 'true'
      ///
      /// @param active : bool to activate the criteria (true == active..)
      /// @param difference : representing the threshold
      ///
      void setParamTol(bool active, double difference);
      
      ///
      /// @brief Get the parameter tolerance abort criteria
      /// @return double representing the threshold
      ///
      inline double getParamTol(){return m_paramTol;};
    
      ///
      /// @brief Set maximum number of Iterations
      /// @param active : bool to enable the criteria
      /// @param num : unsigned int -> max number of iterations
      ///
      void setMaxNumIter(bool active, unsigned int num);

      ///
      /// @brief get maximum number of Iterations
      /// @return unsigned int representing the max number of iterations
      ///
      inline unsigned int getMaxNumIter(){return m_maxNumIter;};

      ///
      /// @brief get actual Iteration count
      /// @return unsigned int represention the actual iteration count
      ///
      inline unsigned int getNumIter(){return m_numIter;};

      ///
      /// @brief set time limit in sec
      /// @param active: bool to set the timelimit active or not
      /// @param seconds: double representing the timelimit in seconds
      ///
      void setTimeLimit(bool active, double seconds);

      ///
      /// @brief get time limit in sec
      /// @return time limit
      ///
      inline double getTimeLimit(){return m_maxSeconds;};

      ///
      /// @brief get return reason
      /// @return returns an int representing the return reason. Compare with enumeration
      ///
      inline int getReturnReason(){return m_returnReason;};

      ///
      /// @brief setMaximize 'true' Changes Optimization to maximization instead of the default: 'false' ^= minimization. 
      /// @param maximize maximize? 
      ///
      void setMaximize(bool maximize);
    
      ///
      /// @brief set loger
      /// @param loger OptLogBase * to an instance of a loger
      ///
      void setLoger(OptLogBase *loger);

      ///
      /// @brief setVerbose = true to enable a lot of outputs 
      ///
      inline void setVerbose(bool verbose){m_verbose = verbose;};
    
    protected:
      //  pure virtual definitions
      
      ///
      /// @brief virtual function that will start the optimization
      /// @return integer representing abortion status from enum
            ///
      virtual int optimize() = 0;

      ///
      /// @brief Initializations
      ///
      void init();

      //  end of pure virtual definitions

          
      ///
      /// @brief Checks if parameters are valid
      /// @param parameters : parameters to check.
      ///
      bool checkParameters(const OPTIMIZATION::matrix_type & parameters);
      
      ///
      /// @brief Get the last parameters
      /// @return OPTIMIZATION::matrix_type containing the last parameters used in Optimization
      ///
      inline OPTIMIZATION::matrix_type  getLastParameters(){return m_parameters;}

      ///
      ///  @brief get number of paramters
      ///
      inline unsigned int getNumberOfParameters(){return m_numberOfParameters;}

        
      ///
      /// @brief Sets parameters used as initial point for Optimization
      /// @param startParameters :  used as initial point
      ///
      void setParameters(const OPTIMIZATION::matrix_type & startParameters);
    
    
      ///
      /// @brief get loger
      /// @return pointer to the loger
      ///
      inline OptLogBase * getLoger(){return m_loger;};

      ///
      /// @brief Change cost function.
      ///
      void changeCostFunction(CostFunction* costFunction);

      //////////////////////////////////////////
      //          //
      //   member definitions   //
        //          //
        //////////////////////////////////////////

            ///
      /// pointer to cost function
      ///
      CostFunction* m_costFunction;

      ///
      /// number of parameters to be optimized
      ///
      unsigned int m_numberOfParameters;
      
      ///
      /// parameter vector
      ///
      OPTIMIZATION::matrix_type   m_parameters;

      ///
      /// function value corresponding to m_parameters
      ///
      double m_currentCostFunctionValue;

      ///
      /// scales vector
      ///
      OPTIMIZATION::matrix_type   m_scales;

      ///
      /// parameters tolerance threshold
      ///
      double m_paramTol;

      ///
      /// parameters tolerance active
      ///
      bool m_paramTolActive;

      ///
      /// function tolerance threshold
      ///
      double m_funcTol;

      ///
      /// function tolerance active
      ///
      bool m_funcTolActive;
          
      ///
      /// Maximum number of Iterations
      ///
      unsigned int m_maxNumIter;

      ///
      /// Iteration limit active
      ///
      bool m_maxNumIterActive;

      ///
      /// Iteration counter
      ///
      unsigned int m_numIter;

      ///
      /// Time limit in seconds
      ///
      double m_maxSeconds;

      ///
      /// Time limit active
      ///
      bool m_maxSecondsActive;

      ///
      /// start time sturct
      ///
      clock_t m_startTime;

      ///
      /// current time struct
      ///
      clock_t m_currentTime;

      ///
      /// container to store the return reason until it is returned from optimize()
      ///
      int m_returnReason ;
      
      ///
      /// upper parameter bound
      ///
      OPTIMIZATION::matrix_type  m_upperParameterBound;
      ///
      /// upper parameter bound active
      ///
      bool m_upperParameterBoundActive;
    
      ///
      /// lower parameter bound
      ///
      OPTIMIZATION::matrix_type  m_lowerParameterBound;
      ///
      /// lower parameter bound active
      ///
      bool m_lowerParameterBoundActive;

      ///
      /// maximize
      ///
      bool m_maximize;

      ///
      /// log class OptLogBase
      ///
      OptLogBase *m_loger;
      
      ///
      /// bool to enable a bunch of outputs 
      ///
      bool m_verbose;

      ///
      /// function that calls costfunction->evaluate but inverts the sign if neccesary (min or max..)
      ///
      double evaluateCostFunction(const OPTIMIZATION::matrix_type & x);

      ///
      /// function that calls costfunction->evaluate for every column in x and inverts the sign in neccesary
      ///
      OPTIMIZATION::matrix_type evaluateSetCostFunction(const OPTIMIZATION::matrix_type & xSet);

  };
  
} //namespace

#endif

