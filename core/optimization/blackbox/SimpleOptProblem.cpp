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
                        Matthias Wacker <Matthias.Wacker@mti.uni-jena.de>
*/

#include "core/optimization/blackbox/SimpleOptProblem.h"

using namespace OPTIMIZATION;

// note: all matrices are of size 0x0 meaning that they are not initialised!
SimpleOptProblem::SimpleOptProblem() : m_costfunc(NULL),
                           m_numParams(0),
                           m_numActiveParams(0),
                           m_maximize(false),
                           m_lowerBoundsActive(false),
                           m_upperBoundsActive(false),
                           m_dimwrapper(NULL)
{
}


SimpleOptProblem::SimpleOptProblem(CostFunction* costfunc, OPTIMIZATION::matrix_type& initialParams, OPTIMIZATION::matrix_type& scales, bool allactive)
{
  // if dimension of initial parameter matrix and/or scale matrix do not fit the given dimension, stop
  assert((int)initialParams.rows() == (int)costfunc->getNumOfParameters() && (int)scales.rows() == (int)costfunc->getNumOfParameters());
  
  // pointer to costfunction
  m_costfunc= costfunc;
  
  // full dimension of optimization problem
  m_numParams= m_costfunc->getNumOfParameters();
  
  matrix_type tmp(m_numParams,1);
  m_selection= tmp;
  m_upperBounds= tmp;
  m_lowerBounds= tmp;
  
  // number of active parameters (all or none?)
  if(allactive)
  {
      m_numActiveParams= m_numParams;
      for(int i= 0; i< m_numParams; ++i)
          m_selection(i,0)= 1;
  }
  else
  {
      m_numActiveParams= 0;
      for(int i= 0; i< m_numParams; ++i)
          m_selection(i,0)= 0;
  }
  
  // init parameters and scales
  m_currentparams= initialParams;
  m_scales= scales;
  
  // init upper and lower bounds with infitniy and -infinity
  for(int i= 0; i< m_numParams; ++i)
  {
  m_lowerBounds(i,0)= -1.0*std::numeric_limits<double>::max( );
  // -1.0*numeric_limits<double>::infinity( );//-1.0*numeric_limits<float>::max( );
  m_upperBounds(i,0)= std::numeric_limits<double>::max( );
  //numeric_limits<double>::infinity( );//numeric_limits<float>::max( );
  }
  
  // per default minimization will be perfomed and no bounds are active
  m_maximize= false;
  m_lowerBoundsActive= false;
  m_upperBoundsActive= false;
  
  m_dimwrapper= NULL;
}


SimpleOptProblem::SimpleOptProblem(const SimpleOptProblem& opt)
{
  m_costfunc= opt.getOriginalCostFunction();
  m_numParams= opt.getNumParams();
  m_numActiveParams= opt.getNumActiveParams();
  m_currentparams= opt.getAllCurrentParams();
  m_scales= opt.getAllScales();
  m_selection=opt.m_selection; // direct member access
  m_maximize= opt.getMaximize();
  m_lowerBoundsActive= opt.lowerBoundsActive();
  m_upperBoundsActive= opt.upperBoundsActive();
  m_lowerBounds= opt.getAllLowerBounds();
  m_upperBounds= opt.getAllUpperBounds();
      
  m_dimwrapper= NULL;
}


SimpleOptProblem::~SimpleOptProblem()
{
  if(m_dimwrapper != NULL)
      delete m_dimwrapper;
}


SimpleOptProblem& SimpleOptProblem::operator=(const SimpleOptProblem& opt)
{
  m_costfunc= opt.m_costfunc;
  m_selection=opt.m_selection; // direct member access
  m_numParams= opt.getNumParams();
  m_numActiveParams= opt.getNumActiveParams();
  m_currentparams= opt.getAllCurrentParams();
  m_scales= opt.getAllScales();
  m_maximize= opt.getMaximize();
  m_lowerBoundsActive= opt.lowerBoundsActive();
  m_upperBoundsActive= opt.upperBoundsActive();
  m_lowerBounds= opt.getAllLowerBounds();
  m_upperBounds= opt.getAllUpperBounds();
      
  m_dimwrapper= NULL;
  
  return *this;
}


void SimpleOptProblem::activateAllParams(bool status)
{
  for(int i= 0; i< this->getNumParams(); ++i)
  {
      m_selection(i,0) = (int)(status);
  }

  if(status == true)
  {
    m_numActiveParams=m_numParams;
  }
  else
  {
    m_numActiveParams=0;
  }
}


void SimpleOptProblem::activateParam(int paramnum, bool status)
{
  assert(paramnum < m_numParams && paramnum >= 0);
  
  m_selection(paramnum,0)= (int)(status);

  int count = 0;
  for(int i =0; i < m_numParams; ++i)
  {
    if(m_selection(i,0)==1)
    {
      count++;
    }
  }
  m_numActiveParams=count;
}


bool SimpleOptProblem::isActive(int paramnum) const
{
  assert(paramnum < m_numParams && paramnum >= 0);
  
  if(m_selection(paramnum,0) == 1)
      return true;
  else
      return false;
}


bool SimpleOptProblem::allActive() const
{
  if(m_numActiveParams == m_numParams)
      return true;
  else
      return false;
}


int SimpleOptProblem::getNumParams() const
{
  return m_numParams;
}


int SimpleOptProblem::getNumActiveParams() const
{
  return m_numActiveParams;
}


matrix_type SimpleOptProblem::getAllCurrentParams() const
{
  return m_currentparams;
}


matrix_type SimpleOptProblem::getActiveCurrentParams() const
{
  //compute selection matrix (X x m_numParamsx)
  matrix_type selmatrix= this->computeSelectionMatrix();
  return (selmatrix*m_currentparams);
}


matrix_type SimpleOptProblem::getAllScales() const
{
  return m_scales;
}


matrix_type SimpleOptProblem::getActiveScales() const
{
  //compute selection matrix (X x m_numParamsx)
  matrix_type selmatrix= this->computeSelectionMatrix();
  return(selmatrix* m_scales);
}


matrix_type SimpleOptProblem::getAllUpperBounds() const
{
  return m_upperBounds;
}


matrix_type SimpleOptProblem::getActiveUpperBounds() const
{
  //compute selection matrix (X x m_numParamsx)
  matrix_type selmatrix= this->computeSelectionMatrix();
  return (selmatrix*m_upperBounds);
}


matrix_type SimpleOptProblem::getAllLowerBounds() const
{
  return m_lowerBounds;
}


matrix_type SimpleOptProblem::getActiveLowerBounds() const
{
  //compute selection matrix (X x m_numParamsx)
  matrix_type selmatrix= this->computeSelectionMatrix();
  return (selmatrix*m_lowerBounds);
}


CostFunction* SimpleOptProblem::getCostFunction() 
{
  // if number of active params is less then m_numParams we need a Wrapper function
  if(m_numActiveParams < m_numParams)
  {
      // if there is still existing an old dimwrapper function
      /// @todo little problem: if the opt problem was not changed concerning its selection and a dimension reduced version is already existing it will be deleted and newly allocated nevertheless; that is not so nice :(
      if(m_dimwrapper != NULL)
          delete m_dimwrapper;
      
      // new dimension reduction, wrapper function
      m_dimwrapper= new DimWrapperCostFunction(m_costfunc, m_selection, m_currentparams);
      return m_dimwrapper;
  }
  
  // else we return just the normal costfunction
  return m_costfunc;
}


CostFunction* SimpleOptProblem::getOriginalCostFunction() const
{
  return m_costfunc;
}


bool SimpleOptProblem::getMaximize() const
{
  return m_maximize;
}


bool SimpleOptProblem::lowerBoundsActive() const
{
  return m_lowerBoundsActive;
}


bool SimpleOptProblem::upperBoundsActive() const
{
  return m_upperBoundsActive;
}


void SimpleOptProblem::setAllCurrentParameters(matrix_type& params)
{
  assert((int)params.rows() == m_numParams && (int)params.cols() == 1);
  m_currentparams= params;
}


void SimpleOptProblem::setActiveCurrentParameters(matrix_type& params)
{
  assert((int)params.rows() == m_numActiveParams && (int)params.cols() == 1);

  int paramcopied= 0;
  for(int i= 0; i< m_numParams; ++i)
  {
    if(m_selection(i,0) == 1)
    {
        m_currentparams(i,0)= params(paramcopied,0);
        paramcopied++;
    }
  }
}


void SimpleOptProblem::setAllScales(matrix_type& scales)
{
  assert((int)scales.rows() == m_numParams && scales.cols() == 1);
  m_scales= scales;
}


void SimpleOptProblem::setActiveScales(matrix_type& scales)
{
  assert((int)scales.rows() == m_numActiveParams && scales.cols() == 1);

  int scalecopied= 0;
  for(int i= 0; i< m_numParams; ++i)
  {
    if(m_selection(i,0) == 1)
    {
        m_scales(i,0)= scales(scalecopied,0);
        scalecopied++;
    }
  }
}


void SimpleOptProblem::setLowerBound(int paramnumber, float lowerbound)
{
  assert(paramnumber >= 0 && paramnumber < m_numParams);
  m_lowerBoundsActive= true;
  m_lowerBounds(paramnumber,0)= lowerbound;
}


void SimpleOptProblem::setUpperBound(int paramnumber, float upperbound)
{
  assert(paramnumber >= 0 && paramnumber < m_numParams);
  m_upperBoundsActive= true;
  m_upperBounds(paramnumber,0)= upperbound;
}


void SimpleOptProblem::resetLowerBounds()
{
  m_lowerBoundsActive= false;
  for(int i= 0; i< m_numParams; ++i)
  {
      m_lowerBounds(i,0) = -1.0*std::numeric_limits<double>::infinity( );
  }
}


void SimpleOptProblem::resetUpperBounds()
{
  m_upperBoundsActive= false;
  for(int i= 0; i< m_numParams; ++i)
  {
      m_upperBounds(i,0) = std::numeric_limits<double>::infinity( );
  }
}


void SimpleOptProblem::changeCostFunc(CostFunction* costfunc)
{
  m_costfunc= costfunc;
}


void SimpleOptProblem::setMaximize(bool maximize)
{
  m_maximize=maximize;
}


matrix_type SimpleOptProblem::computeSelectionMatrix() const
{
  matrix_type selectionmatrix(m_numActiveParams,m_numParams,0);
  int index= 0;
  for(int i= 0; i < m_numParams; ++i)
  {
    if(m_selection(i,0) == 1)
    {
        selectionmatrix(index,i)= 1.0;
        index++;
    }
  }
  return selectionmatrix;
}
