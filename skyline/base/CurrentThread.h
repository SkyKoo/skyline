#ifndef SKYLINE_BASE_CURRENTTHREAD_H
#define SKYLINE_BASE_CURRENTTHREAD_H

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
} // namespace CurrentThread

} // namespace skyline

#endif // SKYLINE_BASE_CURRENTTHREAD_H
