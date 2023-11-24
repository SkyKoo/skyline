
#include "skyline/base/Thread.h"
#include "skyline/base/CurrentThread.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/syscall.h>

namespace skyline
{

namespace detail
{

pid_t gettid()
{
  return static_cast<pid_t>(::syscall(SYS_gettid));
}

} // namespace detail

void CurrentThread::cacheTid()
{
  if (t_cachedTid == 0)
  {
    t_cachedTid = detail::gettid();
    t_tidStringLength = snprintf(t_tidString, sizeof t_tidString, "%5d ", t_cachedTid);
  }
}

} // namespace skyline
