//////////////////////////////////////////////////////////////////////
//
//  SimpleOptimizer.cpp: Implementation of the SimpleOptimizer class.
//
//  Written by Matthias Wacker
//
//////////////////////////////////////////////////////////////////////

#include <iostream>

#include "core/optimization/blackbox/SimpleOptimizer.h"

using namespace OPTIMIZATION;

SimpleOptimizer::SimpleOptimizer(OptLogBase *loger) : SuperClass(loger)
{
}

SimpleOptimizer::SimpleOptimizer( const SimpleOptimizer &opt) : SuperClass(opt)
{
}

SimpleOptimizer  & SimpleOptimizer::operator=(const SimpleOptimizer &opt)
{
    
  /*
      avoid self-copy
  */
  if(this != &opt)
  {
    
    //
    //  =operator of SuperClass
    //
    SuperClass::operator=(opt);

    //
    //  own values:
    // currently no member variables
  }

    return *this;
}

SimpleOptimizer::~SimpleOptimizer()
{
}


void SimpleOptimizer::init()
{
  SuperClass::init();
}


int SimpleOptimizer::optimizeProb(SimpleOptProblem &optProb)
{
  // get settings
  getSettings(optProb);

  // run optimization
  int returnReason = optimize(); // implementation in child!

  //store result
  setResult(optProb); 

  // return the return reason 
  return returnReason;
}


void SimpleOptimizer::setResult(SimpleOptProblem &optProb)
{
  matrix_type tmp = this->getLastParameters(); 
  optProb.setActiveCurrentParameters(tmp);
}

void SimpleOptimizer::getSettings(SimpleOptProblem &optProb)
{
  // Costf
  m_costFunction=optProb.getCostFunction();
  m_numberOfParameters=m_costFunction->getNumOfParameters();
  
  // bounds
  setLowerParameterBound(optProb.lowerBoundsActive(),optProb.getActiveLowerBounds());
  setUpperParameterBound(optProb.upperBoundsActive(),optProb.getActiveUpperBounds());

  // scales
  setScales(optProb.getActiveScales());
  
  // initial params
  setParameters(optProb.getActiveCurrentParams());

  // max
  setMaximize(optProb.getMaximize());
}

