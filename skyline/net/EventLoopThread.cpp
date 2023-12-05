
#include "skyline/net/EventLoopThread.h"

#include "skyline/net/EventLoop.h"

using namespace skyline;
using namespace skyline::net;

EventLoopThread::EventLoopThread(const ThreadInitCallback& cb,
                                 const string& name)
  : loop_(NULL),
    exiting_(false),
    thread_(std::bind(&EventLoopThread::threadFunc, this), name),
    mutex_(),
    cond_(mutex_),
    callback_(cb)
{
}

EventLoopThread::~EventLoopThread()
{
  exiting_ = true;
  if (loop_ != NULL) // not 100% race-free, eg. threadFunc could be running callback_.
  {
    // still a tiny chance to call destructed object, if threadFunc exits just now.
    // but when EventLoopThread destructs, usually programming is exiting anyway.
    loop_->quit();
    thread_.join();
  }
}

EventLoop* EventLoopThread::startLoop()
{
  assert(!thread_.started());
  thread_.start();

  EventLoop* loop = NULL;
  {
    MutexLockGuard lock(mutex_);
    while (loop_ == NULL)
    {
      // waiting here till eventloop is created in threadfunc
      cond_.wait();
    }
    loop = loop_;
  }

  // return loop to caller
  return loop;
}

void EventLoopThread::threadFunc()
{
  // stack variable is ok.
  EventLoop loop;

  if (callback_)
  {
    // thread init callback first
    callback_(&loop);
  }

  {
    MutexLockGuard lock(mutex_);
    loop_ = &loop;
    cond_.notify();
  }

  // run
  loop.loop();
  // assert(exiting_);
  MutexLockGuard lock(mutex_);
  loop_ = NULL;
}
