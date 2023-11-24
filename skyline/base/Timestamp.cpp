
#include "skyline/base/Timestamp.h"

#include <sys/time.h>

using namespace skyline;

Timestamp Timestamp::now()
{
  struct timeval tv;
  gettimeofday(&tv, nullptr);
  int64_t second = tv.tv_sec;
  return Timestamp(second * kMicroSecondsPerSecond + tv.tv_usec);
}
