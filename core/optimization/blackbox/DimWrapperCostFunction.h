//////////////////////////////////////////////////////////////////////
//
//  DimWrapperCostFunction.h: 
//  Defines a wrapper around a cost function. Given a parameter matrix (parameter initalizations) and a selection matrix a flexible optimization of different, individual parameters becomes possible. 
//  Written By: Matthias Wacker, Esther Platzer
//
//////////////////////////////////////////////////////////////////////

#ifndef _DIMWRAP_COST_FUNCTION_H_
#define _DIMWRAP_COST_FUNCTION_H_

//#include "Optimizable.h"
#include "core/optimization/blackbox/CostFunction.h"
#include "core/optimization/blackbox/Definitions_core_opt.h"

namespace OPTIMIZATION {

  class DimWrapperCostFunction : public CostFunction 
  {
    public:

      typedef  CostFunction SuperClass;
      
      /*!
        DefaultConstructor
      */
      DimWrapperCostFunction();

      /*!
      *  Useful constructor
      *
      *  @param orig pointer to the original cost function with paramDim dim_orig
      *  @param selectionVecotor (dim_orig x 1) selection vector with nonzero values 
      *    for the ones that should be used in new costfunction
      *  @param fixedValues vector to be able to specify fixed values for the unused paramters
      *
      *  the parameters of this costfunction will be mapped to the original ones. Offset will be 
      *  added to the paramter vector. evaluate() will return the result of the original function
      *
      *  x_orig = m_selMatTransposed * x_this + fixedValues
      * */
      DimWrapperCostFunction(CostFunction *orig, const OPTIMIZATION::matrix_type &selectionVector, const OPTIMIZATION::matrix_type &fixedValues);

      /*!
      *  copy constructor
      *
      * */
      DimWrapperCostFunction(const DimWrapperCostFunction & costFunc);
          
      /*!
              Destructor.
      */
      virtual ~DimWrapperCostFunction();

      /*!
        =operator
      */
      DimWrapperCostFunction &operator=(const DimWrapperCostFunction &costFunc);

      /*!
      *  
      *  @param selectionVecotor (dim_orig x 1) selection vector with nonzero values 
      *    for the ones that should be used in new costfunction
      *  @param fixedValues vector to be able to specify fixed values for the unused paramters
      * */
      void changeSelection(const OPTIMIZATION::matrix_type & selectionVector, const OPTIMIZATION::matrix_type &fixedValues);


      /*!
        Initialization for the cost function
      */
      virtual void init();
            
      /*!
      *
      * */
      virtual double evaluate(const OPTIMIZATION::matrix_type &parameter);
      
      /**
      * Returns the current full parameter vector (no dimension reduction for inactive params)
      * @param x the current parameter vector containing just active parameters
      * @return the full parameter vector with current active params
      */
      virtual OPTIMIZATION::matrix_type getFullParamsFromSubParams(const OPTIMIZATION::matrix_type &x);

    
    private:
    
      /*!
      *  the original costfunciton
      *
      *
      * */
      CostFunction *m_pOrigCostFunc;


      /*!
      *  this is the mapping matrix
      *
      *  x_orig = m_selMatTransposed * x + offset
      *
      * */
      OPTIMIZATION::matrix_type  m_selMatTransposed;

      /*!
      *  fixed values
      *
      * */
      OPTIMIZATION::matrix_type  m_fixedValues;
      
  };

  #endif
}

