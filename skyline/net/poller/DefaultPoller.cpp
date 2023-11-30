
#include "skyline/net/Poller.h"
#include "skyline/net/poller/PollPoller.h"
#include "skyline/net/poller/EPollPoller.h"

#include <stdlib.h>

using namespace skyline::net;

Poller* Poller::newDefaultPoller(EventLoop* loop)
{
  // if (::getenv("SKYLINE_USE_POLL"))
  {
    return new PollPoller(loop);
  }
  //else
  {
    // return new EPollPoller(loop);
  }
}
