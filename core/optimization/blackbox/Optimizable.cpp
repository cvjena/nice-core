//////////////////////////////////////////////////////////////////////
//
//  Optimizable.cpp: implementation of the Optimizable class.
//
//  Written By: Matthias Wacker
//
//////////////////////////////////////////////////////////////////////

#include "core/optimization/blackbox/Optimizable.h"

using namespace OPTIMIZATION;

Optimizable::Optimizable() : m_numOfParameters(0)
{
}

Optimizable::Optimizable(unsigned int numOfParameters) : m_numOfParameters(numOfParameters)
{
}

Optimizable::Optimizable(const Optimizable &optimizable)
{
  m_numOfParameters = optimizable.m_numOfParameters;
}

Optimizable::~Optimizable()
{
}

Optimizable &Optimizable::operator=(const Optimizable &opt)
{
    
  /*
      avoid self-copy
  */
  if(this != &opt)
  {
    
    /*
      own values:
    */
    m_numOfParameters = opt.m_numOfParameters;
  
  }

    return *this;
}

matrix_type Optimizable::evaluateSet(const matrix_type &parameterSet)
{
  unsigned int iMax = parameterSet.cols();
  matrix_type result(parameterSet.cols(),1);

  for(unsigned int i = 0; i < iMax; i++)
  {
    //result(i) = this->evaluate(parameterSet.Sub(m_numOfParameters,1,0,i));
    result(i,0) = this->evaluate(parameterSet(0,i,m_numOfParameters-1,i));
  }

  return result;
}

