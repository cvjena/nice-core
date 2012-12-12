//////////////////////////////////////////////////////////////////////
//
//  Optimizer.cpp: Implementation of the Optimizer class.
//
//  Written by Matthias Wacker
//
//////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cassert>

#include "core/optimization/blackbox/Optimizer.h"

using namespace OPTIMIZATION;

//Optimizer::Optimizer(unsigned int numOfParameters, CostFunction *objectiveFunction, OptLogBase *loger)
Optimizer::Optimizer(OptLogBase *loger)
{
  m_costFunction      = NULL;
  // may be NULL
  m_loger       = loger;
  
  //  SET defaults
  m_numberOfParameters    = 0;
  m_maximize      = false;
  m_lowerParameterBoundActive   = false;
  m_upperParameterBoundActive   = false;
  m_funcTolActive     = false;
  m_paramTolActive    = false;
  m_maxNumIterActive    = false;
  m_maxSecondsActive    = false;
  m_verbose       = false;
  m_paramTol  = 0.0001;
  m_funcTol = 0.000001;
}


Optimizer::Optimizer( const Optimizer &opt)
{
  
  //  no deep copies!  
  m_costFunction = opt.m_costFunction;
  m_loger = opt.m_loger;
  
  // 
  m_numberOfParameters = opt.m_numberOfParameters;
  m_parameters = opt.m_parameters;
  m_scales = opt.m_scales;
  m_upperParameterBound = opt.m_upperParameterBound;
  m_lowerParameterBound = opt.m_lowerParameterBound;
  
  m_funcTol = opt.m_funcTol;
  m_paramTol = opt.m_paramTol;
  m_maxNumIter = opt.m_maxNumIter;
  m_maxSeconds = opt.m_maxSeconds;
    
  m_maximize    = opt.m_maximize;
  m_funcTolActive   = opt.m_funcTolActive;
  m_paramTolActive  = opt.m_paramTolActive;
  m_maxNumIterActive  = opt.m_maxNumIterActive;
  m_maxSecondsActive  = opt.m_maxSecondsActive;
  m_lowerParameterBoundActive = opt.m_lowerParameterBoundActive;
  m_upperParameterBoundActive = opt.m_upperParameterBoundActive;
  m_verbose = opt.m_verbose;

}

Optimizer  & Optimizer::operator=(const Optimizer &opt)
{
    
  /*
      avoid self-copy
  */
  if(this != &opt)
  {
    
    //
    //  =operator of SuperClass
    //
    //SuperClass::operator=(opt);

    //
    //  own values:
    //
  
    //  no deep copies!  
    m_costFunction = opt.m_costFunction;
    m_loger = opt.m_loger;
    
    // 
    m_numberOfParameters = opt.m_numberOfParameters;
    m_parameters = opt.m_parameters;
    m_scales = opt.m_scales;
    m_upperParameterBound = opt.m_upperParameterBound;
    m_lowerParameterBound = opt.m_lowerParameterBound;
    
    m_funcTol = opt.m_funcTol;
    m_paramTol = opt.m_paramTol;
    m_maxNumIter = opt.m_maxNumIter;
    m_maxSeconds = opt.m_maxSeconds;
      
    m_maximize      = opt.m_maximize;
    m_funcTolActive   = opt.m_funcTolActive;
    m_paramTolActive    = opt.m_paramTolActive;
    m_maxNumIterActive  = opt.m_maxNumIterActive;
    m_maxSecondsActive  = opt.m_maxSecondsActive;
    m_lowerParameterBoundActive = opt.m_lowerParameterBoundActive;
    m_upperParameterBoundActive = opt.m_upperParameterBoundActive;
    m_verbose = opt.m_verbose;

  }

    return *this;
}

Optimizer::~Optimizer()
{
}

void Optimizer::setMaximize(bool maximize)
{
  m_maximize = maximize;
}

void Optimizer::setParameters(const matrix_type & startParameters)
{
  if(checkParameters(startParameters) == true)
  {
    m_parameters = startParameters;
  }
  else
  {
    if(m_loger)
      m_loger->logError("the parameters that were tried to set are not within the Bounds. Startparameters are set to the lower Bound");

    assert(false); // :)
    m_parameters = m_lowerParameterBound;
  }
}


bool Optimizer::checkParameters(const matrix_type & parameters)
{
  assert( ((int)parameters.rows() == static_cast<int>(m_numberOfParameters)) && ((int)parameters.cols() == 1 ) );
  
  if(m_lowerParameterBoundActive || m_upperParameterBoundActive)
  {
    for(int i=0; i < static_cast<int>(m_numberOfParameters); i++)
    {
      if( m_upperParameterBoundActive)
      {
        if(parameters(i,0) >= m_upperParameterBound(i,0))
        {
          return false;
        }
      }
      if( m_lowerParameterBoundActive)
      {
        if(parameters(i,0) <= m_lowerParameterBound(i,0))
        {
          return false;
        }
      }
    }
  }
  return true;
}


void Optimizer::setScales(const matrix_type & scales)
{
  assert ((int)scales.rows() == static_cast<int>(m_numberOfParameters) && ((int)scales.cols() == 1 ) );

  m_scales=scales;
}

void Optimizer::setUpperParameterBound(bool active, const matrix_type & upperBound)
{
  m_upperParameterBoundActive = active;
  m_upperParameterBound = upperBound;
}

void Optimizer::setLowerParameterBound(bool active, const matrix_type & lowerBound)
{
  m_lowerParameterBoundActive = active;
  m_lowerParameterBound = lowerBound;
}

void Optimizer::setFuncTol(bool active, double difference)
{
  m_funcTolActive = active;
  m_funcTol = difference;
}

void Optimizer::setParamTol(bool active, double difference)
{
  m_paramTolActive = active;
  m_paramTol = difference;
}

void Optimizer::setMaxNumIter(bool active, unsigned int num)
{
  m_maxNumIterActive = active;
  m_maxNumIter = num;
}

void Optimizer::setTimeLimit(bool active, double seconds)
{
  m_maxSecondsActive = active;
  m_maxSeconds = seconds;
}


void Optimizer::setLoger(OptLogBase *loger)
{
  m_loger = loger;

  if(loger)
  {
    loger->init();
  }
}

void Optimizer::changeCostFunction(CostFunction* costFunction)
{
  m_costFunction = costFunction;

  if (m_costFunction)
  { 
    m_costFunction->init();
  }
}

double Optimizer::evaluateCostFunction(const matrix_type & x)
{
  return ( m_maximize == true ? (-1.0 * m_costFunction->evaluate(x)):(m_costFunction->evaluate(x)));
}

void Optimizer::init()
{
  /* Check costfunctin and loger */
  if( !m_costFunction)
  {
    if(m_loger)
      m_loger->logError("Optimizer init() failed because of missing costfunction");
    assert(false); // :) 
  }
  else
  {
    m_costFunction->init();
  }

  m_numIter = 0;

}

/*!
  function that calls costfunction->evaluate for every column in x and inverts the sign in neccesary
*/
Optimizer::matrix_type Optimizer::evaluateSetCostFunction(const matrix_type & xSet)
{
  return ( m_maximize == true ? (m_costFunction->evaluateSet(xSet) * -1.0):(m_costFunction->evaluateSet(xSet)));
}

