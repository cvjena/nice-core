//////////////////////////////////////////////////////////////////////
//
//  OptLogBase.h: interface of the Log class.
//
//  Written By: Matthias Wacker
//
//////////////////////////////////////////////////////////////////////

#ifndef _OPT_LOG_BASE_H_
#define _OPT_LOG_BASE_H_

#include <string>
#include <sstream>
#include "core/optimization/blackbox/Definitions_core_opt.h"

namespace OPTIMIZATION {
    
  /*!
      base class for all log classes
  */

  class OptLogBase
  {
    public:
      
          /*!
              Constructor.
      */
      OptLogBase();
          
          /*!
              Destructor.
          */
          virtual ~OptLogBase();
      
      /*!
        Logs an error
      */  
      void logError(const char* format,...);

      /*!
        Logs a warning
      */  
      void logWarning(const char* format,...);

      /*!
        Logs a trace message
      */  
      void logTrace(const char* format,...);

      /**! Write parameter vector to output device (file, stdio, etc.)
          *
          * @param parammatrix parameter matrix
          */
          // empty for all loger except the ParamLogger
          virtual void writeParamsToFile(OPTIMIZATION::matrix_type& parammatrix)
          {
          }

      void init();

    protected:

      /**! Write error message to an output device (file, stdio, etc.)
      */
      virtual void writeLogError(const char* szMessage) = 0;

      /**! Write warning message to an output device (file, stdio, etc.)
      */
      virtual void writeLogWarning(const char* szMessage) = 0;

      /**! Write trace message to an output device (file, stdio, etc.)
      */
      virtual void writeLogTrace(const char* szMessage) = 0;

    private:

      //! Character buffer used to format messages to be logged
      char* m_pMessageBuffer;

      //! Size of the message format buffer
      int m_nMessageBufferSize;
      
  };
  
} // namespace  

#endif

