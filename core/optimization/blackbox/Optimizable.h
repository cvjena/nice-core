//////////////////////////////////////////////////////////////////////
//
//  Optimizable.h: interface of the Optimizable class.
//
//  Written by Matthias Wacker
//
//////////////////////////////////////////////////////////////////////

#ifndef _OPTIMIZABLE_H_
#define _OPTIMIZABLE_H_

#include "core/optimization/blackbox/Definitions_core_opt.h"

  namespace OPTIMIZATION {

  /*!
      \class
  */
  class Optimizable
  {
    public:
      
    /*!
      default Constructor
    */
    Optimizable();

          /*!
              Constructor.
          */
          Optimizable(unsigned int numOfParameters);

    /*!
        Copy Constructor
    */
          Optimizable(const Optimizable &optimizable);

          /*!
              Destructor.
          */
          virtual ~Optimizable();

    /*!
      operator=
    */
    Optimizable & operator=(const Optimizable &opt);
      
    /*!
      get Number of Parameters
    */
    inline unsigned int getNumOfParameters(){return m_numOfParameters;};

    /*!
        Evaluation of objective function.
        \param parameter double matrix (numOfParameters X 1) ^= column vector
        \return objective function value
    */
        virtual double evaluate(const OPTIMIZATION::matrix_type &parameter) = 0;

    /*!
      Evaluation of objection function 
      \param parameterset [x_1, x_2, x_3, .... ,x_n]
      \return doubleMatrix containing 
          [evaluate(x_1), .... evaluate(x_n)];
      
      can be overloaded for parallel computation

    */
    OPTIMIZATION::matrix_type evaluateSet(const OPTIMIZATION::matrix_type &parameterSet);

    protected:
      

      /*!
        the number of parameters
      */
      unsigned int m_numOfParameters;

  };
  
} // namespace

#endif

