#include "skyline/base/CurrentThread.h"

// #include <cxxabi.h>
// #include <execinfo.h>
#include <stdlib.h>
#include <type_traits>

namespace skyline
{

namespace CurrentThread
{
__thread int t_cachedTid = 0;
__thread char t_tidString[32];
__thread int t_tidStringLength = 6;
__thread const char* t_threadName = "unknown";
static_assert(std::is_same<int, pid_t>::value, "pid_t should be int");

string stackTrace(bool demangle)
{
  (void)demangle;
  return "";
}

} // namespace CurrentThread

} // namespace skyline
