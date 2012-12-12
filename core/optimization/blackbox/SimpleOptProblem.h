/*
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License version 2 as published by the Free Software Foundation.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.

    ---
    Copyright (C) 2009, Esther-Sabrina Platzer <esther.platzer@uni-jena.de>
                        Matthias Wacker <matthias.wacker@mti.uni-jena.de>
*/

    /// @class SimpleOptProblem
    /// This class encapsulats simple optimization problems. Parameter values, scales and upper and lower bounds can be managed. Furthermore individual parameters can be deactivated,
    /// which allows an optimization of just a parameter subset. Activation and Deactivation can also be done with help of the class interface.
    ///
    /// @author Esther-Sabrina Platzer, Matthias Wacker
    /// @date 2009-07-02

#ifndef _SimpleOptProblem_h_
#define _SimpleOptProblem_h_

#include <assert.h>

#include "core/optimization/blackbox/Definitions_core_opt.h"
#include "core/optimization/blackbox/CostFunction.h"
#include "core/optimization/blackbox/DimWrapperCostFunction.h"

namespace OPTIMIZATION {

  class SimpleOptProblem 
  {
    public:
      ///
      /// Standard Constructor
      ///
      SimpleOptProblem( );
      
      /// 
      /// Parametrized Constructor allows to specify the initial parameter values, the parameter scales and the costfunction which should be used. Furthermore it is possible to optimize just a subset of the parameter set. For this the wanted parameters have to be activated and the unwanted must be deactivated. By usage of the allactive flag it is possible to activate/deactivate the initial parameter setting in advance. By default all parameters are activeted.
      ///
      /// @param costfunc pointer to costfunction
      /// @param initialParams matrix containing the initial parameter values
      /// @param scales matrix containing the scales for every parameter
      /// @param allactive boolean flag for activating (true) or deactivating (false) all parameters
      ///
      SimpleOptProblem(CostFunction* costfunc, OPTIMIZATION::matrix_type& initialParams, OPTIMIZATION::matrix_type& scales, bool allactive=true);

      /// 
      /// Copy Constructor
      ///
      /// @param opt the optimization problem to copy
      ///
      SimpleOptProblem(const SimpleOptProblem& opt);
      
      ///
      /// Destructor
      ///
      ~SimpleOptProblem();

      ///
      /// Assignment Operator
      /// @param opt the optimization problem to assign
      /// @return SimpleOptProblem
      ///
      SimpleOptProblem& operator=(const SimpleOptProblem& opt);
      
      ///
      /// Depending on the value of status all parameters (the whole parameter set) is activated (status=true) or deactivated (status= false)
      ///
      /// @param status boolean activation flag
      ///
      void activateAllParams(bool status);
      
      ///
      /// Given the number of a certain parameter it status (activated/deactivated) can be set individually
      ///
      /// @param paramnum number of the parameter in the overall parameter set
      /// @param status activation status (true= activated, false= deactivated)
      ///
      void activateParam(int paramnum, bool status);
      
      /// 
      /// Returns the status of individual parameters
      ///
      /// @param paramnum parameter number in the overall parameter set
      /// @retval true, if the actual parameter is active
      /// @retval false, if the actual parameter is inactive
      ///
      bool isActive(int paramnum) const;
      
      ///
      /// Returns wether all params are active or not
      /// @retval true, if all parameters are active (m_numParams == m_numActiveParams)
      /// @retval false, if none or not all parameters are active (m_numParams != m_numActiveParams)
      bool allActive() const;
      
      
      ///
      /// @name Getters
      ///
      
      ///
      /// Returns the size of the overall parameter set
      ///
      int getNumParams() const;
      
      ///
      /// Returns the number of active parameters
      ///
      int getNumActiveParams() const;
      
      /// 
      /// Returns the current parameter set
      ///
      /// @return current parameter matrix
      ///
      OPTIMIZATION::matrix_type getAllCurrentParams() const;

      /// 
      /// Returns the current parameter set
      ///
      /// @return current parameter matrix
      ///
      OPTIMIZATION::matrix_type getActiveCurrentParams() const;
      
      ///
      /// Returns the current parameter scales
      ///
      /// @return current scale matrix
      ///
      OPTIMIZATION::matrix_type getAllScales() const;

      ///
      /// Returns the current parameter scales
      ///
      /// @return current scale matrix
      ///
      OPTIMIZATION::matrix_type getActiveScales() const;
      
      ///
      /// Returns the upper bounds (if no upper bounds are active, the matrix just contains infinity)
      ///
      /// @return upper bound matrix
      ///
      OPTIMIZATION::matrix_type getAllUpperBounds() const;

      ///
      /// Returns the upper bounds (if no upper bounds are active, the matrix just contains infinity)
      ///
      /// @return upper bound matrix
      ///
      OPTIMIZATION::matrix_type getActiveUpperBounds() const;
      
      ///
      /// Returns the lower bounds (if no lower bounds are active, the matrix just contains -infinity)
      ///
      /// @return lower bound matrix
      ///
      OPTIMIZATION::matrix_type getAllLowerBounds() const;

      ///
      /// Returns the lower bounds (if no lower bounds are active, the matrix just contains -infinity)
      ///
      /// @return lower bound matrix
      ///
      OPTIMIZATION::matrix_type getActiveLowerBounds() const;
      
      /// 
      /// Returns a pointer to the CURRENT CostFunction with regard to the actual parameter selection
      ///
      /// @return CostFunction pointer
      ///
      CostFunction* getCostFunction();
      
      ///
      /// Returns a pointer to the ORIGINAL CostFunction ignoring the acutal parameter selection
      ///
      /// @return CostFunction pointer
      ///
      CostFunction* getOriginalCostFunction() const;
      
      /// 
      /// Current description of the optimization strategy
      /// 
      /// @retval true, if a maximization of the CostFunction is performed
      /// @retval false, if a minimization of the CostFunction is performed
      ///
      bool getMaximize() const;
      
      /// 
      /// Returns the current status of lower bounds
      /// 
      /// @retval true, if at least on lower bound (different from -infinity) is set
      /// @retval false, if no lower bounds are set (lower bound matrix just contains -infinity)
      ///
      bool lowerBoundsActive() const;
      
      /// 
      /// Returns the current status of upper bounds
      /// 
      /// @retval true, if at least on upper bound (different from infinity) is set
      /// @retval false, if no upper bounds are set (lower bound matrix just contains infinity)
      ///
      bool upperBoundsActive() const;
      
      
      ///
      /// @name Setters
      ///
      
      ///
      /// (Re)initialization of the current parameter values
      ///
      /// @param params parameter value matrix (must be m_numParams x 1)
      ///
      void setAllCurrentParameters(OPTIMIZATION::matrix_type& params);

      ///
      /// (Re)initialization of the current parameter values of active parameters
      ///
      /// @param params parameter value matrix (must be m_numActiveParams x 1)
      ///
      void setActiveCurrentParameters(OPTIMIZATION::matrix_type& params);
      
      /// 
      /// (Re)initialization of the current scale setting
      /// 
      /// @param scales parameter scale matrix (must be m_numParams x 1)
      ///
      void setAllScales(OPTIMIZATION::matrix_type& scales);

      /// 
      /// (Re)initialization of the current scale setting for active parameters
      /// 
      /// @param scales parameter scale matrix (must be m_numActiveParams x 1)
      ///
      void setActiveScales(OPTIMIZATION::matrix_type& scales);
      
      ///
      /// Definition of a lower bound for an individual parameter
      /// 
      /// @param paramnumber number of the parameter in the overall parameter set
      /// @param lowerbound the lower bound for this parameter
      ///
      void setLowerBound(int paramnumber, float lowerbound);
      
      ///
      /// Definition of an upper bound for an individual parameter
      /// 
      /// @param paramnumber number of the parameter in the overall parameter set
      /// @param upperbound the upper bound for this parameter
      ///
      void setUpperBound(int paramnumber, float upperbound);
      
      ///
      /// Deactivates all lower bounds resulting in a lower bound matrix just containing -infinity.
      ///
      void resetLowerBounds();
      
      ///
      /// Deactivates upper bounds and results in an upper bound matrix just containing infinity
      ///
      void resetUpperBounds();
      
      ///
      /// Exchange of CostFunction. 
      /// 
      /// @param costfunc new CostFunction pointer
      ///
      void changeCostFunc(CostFunction* costfunc);
      
      ///
      /// Definition of the optimization strategy. 
      ///
      /// @param maximize if maximize=true a maximization of the CostFunction will be performed, otherwise it is minimized (Default)
      void setMaximize(bool maximize);
      
      
    protected:

    private:
      ///
      /// Computes a selection matrix out of the selection vector used for selecting active parameters which can be used to compute smaller dimension matrices containing just the active params (or scales and bounds for active params)
      ///
      /// @return selection matrix with dimension m_numActiveParams x m_numParams
      OPTIMIZATION::matrix_type computeSelectionMatrix() const;

      //! cost function pointer
      CostFunction* m_costfunc;  
        
      //! number of parameters
      int m_numParams;
      
      //! number of active parameters (active parameters are the ones, which currently should be optimized)
      int m_numActiveParams;
      
      //! holds the current parameters as parameter vector
      OPTIMIZATION::matrix_type m_currentparams;
      
      //! holds the current scales for the parameters
      OPTIMIZATION::matrix_type m_scales;
      
      //! upper bounds for parameters
      OPTIMIZATION::matrix_type m_upperBounds;
      
      //! lower bounds for parameters 
      OPTIMIZATION::matrix_type m_lowerBounds;
      
      //! selection matrix: defines the active parameters
      OPTIMIZATION::matrix_type m_selection;
      
      //! flag defining wether the optimization problem is a maximization problem (true) or a minimization problem (false)
      bool m_maximize; 
      
      //! flag defining wether lowerBounds are set
      bool m_lowerBoundsActive;
      
      //! flag defining wether upperBounds are set
      bool m_upperBoundsActive;
      
      //! pointer to dimension wrapper function
      CostFunction* m_dimwrapper;
  };
  
} //namespace


#endif /* _SimpleOptProblem_h_ */

