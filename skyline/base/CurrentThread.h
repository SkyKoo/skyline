#ifndef SKYLINE_BASE_CURRENTTHREAD_H
#define SKYLINE_BASE_CURRENTTHREAD_H

#include "skyline/base/Types.h"

namespace skyline
{

namespace CurrentThread
{
  // internal
  // thread local storage
  extern __thread int t_cachedTid;
  extern __thread char t_tidString[32];
  extern __thread int t_tidStringLength;
  extern __thread const char* t_threadName;
  void cacheTid();

  inline int tid()
  {
    // branch prediction information, most of time, the t_cachedTid == 0 is false(0)
    if (__builtin_expect(t_cachedTid == 0, 0))
    {
      cacheTid();
    }
    return t_cachedTid;
  }

  inline const char* tidString() // for logging
  {
    return t_tidString;
  }

  inline int tidStringLength() // for logging
  {
    return t_tidStringLength;
  }

  inline const char* name()
  {
    return t_threadName;
  }

  bool isMainThread();

  void sleepUsec(int64_t usec); // for testing

  string stackTrace(bool demangle);
} // namespace CurrentThread

} // namespace skyline

#endif // SKYLINE_BASE_CURRENTTHREAD_H
