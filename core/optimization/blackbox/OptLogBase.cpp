//////////////////////////////////////////////////////////////////////
//
//  OptLogBase.cpp: Implementation of the Log class.
//
//  Written By: Matthias Wacker
//
//////////////////////////////////////////////////////////////////////

#include "core/optimization/blackbox/OptLogBase.h"

#include <stdio.h>
#include <stdarg.h>

using namespace OPTIMIZATION;

OptLogBase::OptLogBase()
{
  m_nMessageBufferSize = 8 * 1024;
  m_pMessageBuffer = new char[m_nMessageBufferSize];
}

OptLogBase::~OptLogBase()
{
  delete[] m_pMessageBuffer;
}

void OptLogBase::logError(const char* format,...)
{
  va_list arguments;
  va_start(arguments,format);
  //_vsnprintf(m_pMessageBuffer, m_nMessageBufferSize, format, arguments);
  vsnprintf(m_pMessageBuffer, m_nMessageBufferSize, format, arguments);
  va_end(arguments);

  m_pMessageBuffer[m_nMessageBufferSize - 1] = '\0';
  writeLogError(m_pMessageBuffer);
}

void OptLogBase::logWarning(const char* format,...)
{
  va_list arguments;
  va_start(arguments,format);
  //_vsnprintf(m_pMessageBuffer, m_nMessageBufferSize, format, arguments);
  vsnprintf(m_pMessageBuffer, m_nMessageBufferSize, format, arguments);
  va_end(arguments);

  m_pMessageBuffer[m_nMessageBufferSize - 1] = '\0';
  writeLogWarning(m_pMessageBuffer);
}

void OptLogBase::logTrace(const char* format,...)
{
  va_list arguments;
  va_start(arguments,format);
  //_vsnprintf(m_pMessageBuffer, m_nMessageBufferSize, format, arguments);
  vsnprintf(m_pMessageBuffer, m_nMessageBufferSize, format, arguments);
  va_end(arguments);

  m_pMessageBuffer[m_nMessageBufferSize - 1] = '\0';
  writeLogTrace(m_pMessageBuffer);
}


void OptLogBase::init()
{
}

