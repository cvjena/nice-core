///
/// @file SimpleSimpleOptimizer.h: interface of the SimpleOptimizer class.
/// @author Matthias Wacker, Esther Platzer
///

#ifndef _SIMPLEOPTIMIZER_H_
#define _SIMPLEOPTIMIZER_H_

#include "core/optimization/blackbox/Optimizer.h"
#include "core/optimization/blackbox/SimpleOptProblem.h"
#include "core/optimization/blackbox/Definitions_core_opt.h"

namespace OPTIMIZATION {

  /*!
    Abstract base class of all optimizers.
  */
  class SimpleOptimizer : public Optimizer
  {
    public:
      /// the SuperClass is Optimizer
      typedef   Optimizer   SuperClass;

      
      ///
      /// Constructor (also the default constructor)
      /// @param loger OptLogBase * to existing log class or NULL
      ///
      SimpleOptimizer(OptLogBase *loger=NULL);

      ///
      /// Copy constructor
      /// @param opt .. optimizer to copy
      ///
      SimpleOptimizer( const SimpleOptimizer &opt);

      ///
      /// assignment opterator
      /// @param opt optimizer to "copy"
      /// @return self-reference
      ///
      SimpleOptimizer  &operator=(const SimpleOptimizer &opt);


      ///
      ///   Destructor.
        ///
        virtual ~SimpleOptimizer();

      ///
      /// start the optimization for the simple optimization problem
      /// @param optProb the optimization problem to solve
      ///
      virtual int optimizeProb(SimpleOptProblem &optProb);


  protected:
      ///
      /// redeclaring the interface of opt
      ///
      virtual int optimize() = 0;

      ///
      /// do initializations (this is called from child class and calls superclass::init)
      ///
      void init();

      ///
      /// call after optimization to store the result in the optProblem 
      ///
      /// @param optProb the optimization problem 
      ///
      void setResult(SimpleOptProblem &optProb);

      ///
      /// get all settings from the optimization problem
      ///
      /// @param optProb the optimization problem
      ///
      void getSettings(SimpleOptProblem &optProb);


  };
  
} // namespace  

#endif
