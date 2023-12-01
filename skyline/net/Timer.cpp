
#include "skyline/net/Timer.h"

using namespace skyline;
using namespace skyline::net;

AtomicInt64 Timer::s_numCreated_;

void Timer::restart(Timestamp now)
{
  if (repeat_)
  {
    expiration_ = addTime(now, interval_); // now + interval_
  }
  else
  {
    expiration_ = Timestamp::invalid(); // 0
  }
}
