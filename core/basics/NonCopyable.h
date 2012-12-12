#ifndef _FBASICS_NONCOPYABLE_H_
#define _FBASICS_NONCOPYABLE_H_

#include <memory>

// Note: this file is taken from the C++ Boost library (with minor adaptations).

/**
 * The namespace of NICE.
 */
namespace NICE {

// protection from unintended ADL
namespace noncopyable_ {
  /**
   * Private copy constructor and copy assignment ensure classes derived from
   * class NonCopyable cannot be copied.
   *
   * @note
   *  Contributed by Dave Abrahams
   *
   *  (C) Copyright Beman Dawes 1999-2003. Distributed under the Boost
   *  Software License, Version 1.0. (See accompanying file
   *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
   *
   *  See http://www.boost.org/libs/utility for documentation.
   */
  class NonCopyable {
   protected:
      NonCopyable() {}
      ~NonCopyable() {}
   private:  // emphasize the following members are private
      NonCopyable( const NonCopyable& );
      const NonCopyable& operator=( const NonCopyable& );
  };
} // namespace noncopyable_

typedef noncopyable_::NonCopyable NonCopyable;

} // namespace

#endif // _FBASICS_NONCOPYABLE_H_
