#include "skyline/net/EventLoop.h"

#include "skyline/base/Logging.h"

#include <assert.h>
#include <poll.h>

using namespace skyline;
using namespace skyline::net;

namespace
{
// one eventloop per thread
__thread EventLoop* t_loopInThisThread = 0;

} // namespace

EventLoop* EventLoop::getEventLoopOfCurrentThread()
{
  return t_loopInThisThread;
}

EventLoop::EventLoop()
  : looping_(false),
    quit_(false),
    threadId_(CurrentThread::tid())
{
  LOG_DEBUG << "Event created " << this << " in thread " << threadId_;
  // should be null when creating
  if (t_loopInThisThread)
  {
    LOG_FATAL << "Another EventLoop " << t_loopInThisThread
      << " exists in this thread " << threadId_;
  }
  else
  {
    t_loopInThisThread = this;
  }
}

EventLoop::~EventLoop()
{
  LOG_DEBUG << "EventLoop " << this << " of thread " << threadId_
    << " destructs in thread " << CurrentThread::tid();

  t_loopInThisThread = NULL;
}

void EventLoop::loop()
{
  assert(!looping_);
  assertInLoopThread();
  looping_ = true;
  quit_ = false; // FIXME: what if someone calls quit() before loop() ?

  while (!quit_)
  {
    ::poll(NULL, 0, 5*1000);
    break;
  }

  LOG_TRACE << "EventLoop " << this << " stop looping";
  looping_ = false;
}

void EventLoop::abortNotInLoopThread()
{
  LOG_FATAL << "EventLoop::abortNotInLoopThread - EventLoop " << this
            << " was created in threadId_ = " << threadId_
            << ", current thread id = " << CurrentThread::tid();
}
