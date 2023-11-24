#include "skyline/net/EventLoop.h"

// #include "skyline/base/Logging.h"

using namespace skyline;
using namespace skyline::net;

namespace
{


} // namespace

EventLoop::EventLoop()
  : looping_(false),
    quit_(false),
    threadId_(CurrentThread::tid())
{
}

void EventLoop::abortNotInLoopThread()
{
  /*
  LOG_FATAL << "EventLoop::abortNotInLoopThread - EventLoop " << this
            << " was created in threadId_ = " << threadId_
            << ", current thread id = " << CurrentThread::tid();
            */
}
