
#ifndef SKYLINE_NET_TIMERID_H
#define SKYLINE_NET_TIMERID_H

#include "skyline/base/copyable.h"
#include "skyline/base/Types.h"

namespace skyline
{
namespace net
{

class Timer;

class TimerId : copyable
{
 public:
  TimerId()
    : timer_(NULL),
      sequence_(0)
  {
  }

  TimerId(Timer* timer, int64_t seq)
    : timer_(timer),
      sequence_(seq)
  {
  }

  // default copy-ctor, dtor and assignment are okay

  friend class TimerQueue;

 private:
  Timer* timer_;
  int64_t sequence_;
};

} // namespace net
} // namespace skyline

#endif // SKYLINE_NET_TIMERID_H
