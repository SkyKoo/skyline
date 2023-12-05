#ifndef SKYLINE_NET_EVENTLOOPTHREAD_H
#define SKYLINE_NET_EVENTLOOPTHREAD_H

#include "skyline/base/noncopyable.h"
#include "skyline/base/Thread.h"

namespace skyline
{
namespace net
{

class EventLoop;

class EventLoopThread : noncopyable
{
 public:
  typedef std::function<void(EventLoop*)> ThreadInitCallback;

  EventLoopThread(const ThreadInitCallback& cb = ThreadInitCallback(),
                  const string& name = string());
  ~EventLoopThread();
  EventLoop* startLoop();

 private:
  void threadFunc();

  EventLoop* loop_ GUARDED_BY(mutex_);
  bool exiting_;
  Thread thread_;
  MutexLock mutex_;
  Condition cond_ GUARDED_BY(mutex_);
  ThreadInitCallback callback_;
};

} // namespace net
} // namespace skyline

#endif // SKYLINE_NET_EVENTLOOPTHREAD_H
