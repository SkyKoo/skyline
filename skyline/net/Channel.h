
#ifndef SKYLINE_NET_CHANNEL_H
#define SKYLINE_NET_CHANNEL_H

#include "skyline/base/noncopyable.h"
#include "skyline/base/Timestamp.h"

#include <functional>
#include <memory>

namespace skyline
{
namespace net
{

class EventLoop;

///
/// A selectable I/O channel.
///
/// This channel class doesn't own the file descriptor.
/// every channel class only manager one file descriptor.
/// The file descriptor could be a socket,
/// an eventfd, a timerfd, or a signalfd
class Channel : noncopyable
{
 public:
  typedef std::function<void()> EventCallback;
  typedef std::function<void(Timestamp)> ReadEventCallback;

  Channel(EventLoop* loop, int fd);
  ~Channel();

  // This Timestamp is pool return time, it should earlier than the msg be read
  // So we need to record this time for calculate whole duration
  void handleEvent(Timestamp receiveTime);
  void setReadCallback(ReadEventCallback cb)
  { readCallback_ = std::move(cb); }
  void setWriteCallback(EventCallback cb)
  { writeCallback_ = std::move(cb); }
  void setCloseCallback(EventCallback cb)
  { closeCallback_ = std::move(cb); }
  void setErrorCallback(EventCallback cb)
  { errorCallback_ = std::move(cb); }

  /// Tie this channel to the owner object managed by shared_ptr,
  /// prevent the owner object being destroyed in handleEvent.
  void tie(const std::shared_ptr<void>&);

  int fd() const { return fd_; }
  int events() const { return events_; }
  void set_revents(int revt) { revents_ = revt; } // used by pollers
  // int revents() const { return revents_; }
  bool isNoneEvent() const { return events_ == kNoneEvent; }

  void enableReading() { events_ |= kReadEvent; update(); } // call update()
  void disableReading() { events_ &= ~kReadEvent; update(); } // call update()
  void enableWriting() { events_ |= kWriteEvent; update(); } // call update()
  void disableWriting() { events_ &= ~kWriteEvent; update(); } // call update()
  void disableAll() { events_ = kNoneEvent; update(); } // call update()
  bool isWriting() { return events_ & kWriteEvent; }
  bool isReading() { return events_ & kReadEvent; }

  // for Poller
  int index() const { return index_; }
  void set_index(int idx) { index_ = idx; }

  // for debug
  string reventsToString() const;
  string eventsToString() const;

  void doNotLogHup() { logHup_ = false; }

  EventLoop* ownerLoop() const { return loop_; }
  void remove();

 private:
  static string eventsToString(int fd, int ev);

  void update(); // important func, call -> EventLoop::updateChannel() -> Poller::updateChannel()
  void handleEventWithGuard(Timestamp receiveTime);

  static const int kNoneEvent;
  static const int kReadEvent;
  static const int kWriteEvent;

  EventLoop* loop_; // one channel only belong to one eventloop
  const int fd_; // file descriptor
  int events_; // all events this channel care about

  int revents_; // it's the received eventy types of epoll or poll, current activity events
  int index_; // used by Poller

  bool logHup_;

  std::weak_ptr<void> tie_;
  bool tied_;

  bool eventHandling_;
  bool addedToLoop_;

  ReadEventCallback readCallback_;
  EventCallback writeCallback_;
  EventCallback closeCallback_;
  EventCallback errorCallback_;
};

} // namespace net
} // namespace skyline

#endif // SKYLINE_NET_CHANNEL_H
