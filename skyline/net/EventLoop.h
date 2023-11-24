#ifndef SKYLING_NET_EVENTLOOP_H
#define SKYLING_NET_EVENTLOOP_H

#include <atomic>
#include <functional>

#include "skyline/base/noncopyable.h"
#include "skyline/base/CurrentThread.h"

namespace skyline
{
namespace net
{

///
/// Reactor, at most one per thread.
///
/// This is an interface class, so don't expose too much details.
class EventLoop : noncopyable
{
 public:
  typedef std::function<void()> Functor;

  EventLoop();
  ~EventLoop(); // force out-line dtor, for std::unique_ptr members.

  ///
  /// Loops forever.
  ///
  /// Must be called in the same thread as creation of the object.
  ///
  void loop();

  /// Quits loop.
  ///
  /// This is not 100% thread safe, if you call throught a raw pointer,
  /// better to call through share_ptr<EventLoop> for 100% safety.
  void quit();

  ///
  /// Time when poll returns, usually means data arrival.
  ///
  // Timestame pollReturnTime() const { return pollReturnTime_; }

  // pid_t threadId() const { return threadId_; }
  void assertInLoopThread()
  {
    if (!isInLoopThread())
    {
      abortNotInLoopThread();
    }
  }
  bool isInLoopThread() const { return threadId_ == CurrentThread::tid(); }

 private:
  void abortNotInLoopThread();

  bool looping_; /* atomic */
  std::atomic<bool> quit_;
  const pid_t threadId_;
};

} // namespace net
} // namespace skyline

#endif // SKYLING_NET_EVENTLOOP_H
