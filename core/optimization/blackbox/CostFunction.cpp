//////////////////////////////////////////////////////////////////////
//
//  CostFunction.cpp: implementation of the CostFunction class.
//
//  Written By: Matthias Wacker
//
//////////////////////////////////////////////////////////////////////

#include "core/optimization/blackbox/CostFunction.h"

using namespace OPTIMIZATION;

CostFunction::CostFunction() : SuperClass()
{
  m_hasAnalyticGradient = false;
  m_hasAnalyticHessian = false;
  m_numEval = 0;

}

CostFunction::CostFunction(unsigned int numOfParameters) : SuperClass(numOfParameters)
{
  m_hasAnalyticGradient = false;
  m_hasAnalyticHessian = false;
  m_numEval = 0;
}


CostFunction::CostFunction(const CostFunction &func) : SuperClass(func)
{
  m_hasAnalyticGradient = func.m_hasAnalyticGradient;
  m_hasAnalyticHessian = func.m_hasAnalyticHessian;
  m_numEval = func.m_numEval;
}

CostFunction::~CostFunction()
{
}

CostFunction &CostFunction::operator=(const CostFunction &func)
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
    m_hasAnalyticGradient = func.m_hasAnalyticGradient;
    m_hasAnalyticHessian = func.m_hasAnalyticHessian;
    m_numEval = func.m_numEval;
  
  }

    return *this;
}


const matrix_type CostFunction::getAnalyticGradient(const matrix_type &x)
{
  /*
    FIXME: WACKER: Throw exception as default behaviour ?
  */
  
  
  return x * 0;
}

void CostFunction::init()
{
}

const matrix_type CostFunction::getAnalyticHessian(const matrix_type &x)
{
  /*
    FIXME: WACKER: Throw exception as default behaviour
  */
  
  
  return matrix_type( x.rows(), x.rows(), 0.0 );
}

bool CostFunction::setX0(const matrix_type &x0)
{
  if((int)x0.rows() == static_cast<int>(m_numOfParameters) && x0.cols() == 1)
  {
    m_x_0 = x0;
    return true;
  }
  else
    return false;
}


bool CostFunction::setH0(const matrix_type &H0)
{
  if((int)H0.rows() == static_cast<int>(m_numOfParameters) && H0.cols() == 1)
  {
    m_h_0 = H0;
    return true;
  }
  else
    return false;
}

double CostFunction::evaluateSub(double lambda)
{
  return evaluate(m_x_0 + m_h_0 * lambda);
}

