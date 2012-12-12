//////////////////////////////////////////////////////////////////////
//
//  DimWrapperCostFunction.cpp: implementation of the DimWrapperCostFunction class.
//
//  Written By: Matthias Wacker
//
//////////////////////////////////////////////////////////////////////

#include <iostream>
#include "DimWrapperCostFunction.h"

using namespace OPTIMIZATION;

DimWrapperCostFunction::DimWrapperCostFunction() : SuperClass()
{
  m_pOrigCostFunc=NULL;
  m_numOfParameters=0;
}


DimWrapperCostFunction::DimWrapperCostFunction(const DimWrapperCostFunction &func) : SuperClass(func)
{
  m_pOrigCostFunc= func.m_pOrigCostFunc;
  m_selMatTransposed = func.m_selMatTransposed;
  m_fixedValues = func.m_fixedValues;
}

DimWrapperCostFunction::~DimWrapperCostFunction()
{
  // nothing dynamically allocated..
}

DimWrapperCostFunction::DimWrapperCostFunction(CostFunction *orig, const matrix_type &selectionVector,
            const matrix_type &fixedValues)
{
  if(orig == NULL)
  {
    std::cerr << "DimWrapperCostFunction::DimWrapperCostFunction NULL pointer error" << std::endl;
    exit(1);
  }
  m_pOrigCostFunc = orig;

  changeSelection(selectionVector,fixedValues);

}


void DimWrapperCostFunction::changeSelection(const matrix_type & selectionVector, const matrix_type &fixedValues)
{
  // BUILD MATRIX
  //count nonzero values:
  m_fixedValues=fixedValues;
  int count=0;
  int dim = selectionVector.rows();
  std::vector<int> indices;
  for(int i=0; i < dim ; ++i)
  {
    if (selectionVector(i,0) != 0.0 )
    {
      count++;
      indices.push_back(i);
      m_fixedValues(i,0)= 0.0; // resets fixed values to zero for active params
    }
  }
  m_numOfParameters = count;  
  m_selMatTransposed = matrix_type(dim,count);
  for(int i =0; i < (int)m_selMatTransposed.rows(); ++i)
  {
    for(int j =0; j < (int)m_selMatTransposed.cols(); ++j)
    {
      if( indices[j]==i )
      {
        m_selMatTransposed(i,j)=1.0;
      }
      else
      {
        m_selMatTransposed(i,j)=0.0;
      }
    }
  }
}

DimWrapperCostFunction &DimWrapperCostFunction::operator=(const DimWrapperCostFunction &func)
{
    
  /*
      avoid self-copy
  */
  if(this != &func)
  {
    
    /*
      =operator of SuperClass
    */
    SuperClass::operator=(func);

    /*
      own values:
    */
    m_pOrigCostFunc= func.m_pOrigCostFunc;
    m_selMatTransposed = func.m_selMatTransposed;
    m_fixedValues = func.m_fixedValues;
  
  }

    return *this;
}


void DimWrapperCostFunction::init()
{
  m_pOrigCostFunc->init();
}

double DimWrapperCostFunction::evaluate(const matrix_type &x)
{
  return m_pOrigCostFunc->evaluate(m_selMatTransposed * x + m_fixedValues);
}

OPTIMIZATION::matrix_type DimWrapperCostFunction::getFullParamsFromSubParams(const OPTIMIZATION::matrix_type &x)
{
    return m_selMatTransposed * x + m_fixedValues;
}

