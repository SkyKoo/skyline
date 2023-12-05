
#ifndef SKYLINE_NET_ACCEPTOR_H
#define SKYLINE_NET_ACCEPTOR_H

#include "skyline/base/noncopyable.h"
#include "skyline/net/Channel.h"
#include "skyline/net/Socket.h"

namespace skyline
{
namespace net
{

class EventLoop;
class InetAddress;

///
/// Acceptor of incoming TCP connections.
///
class Acceptor : noncopyable
{
 public:
  typedef std::function<void (int sockfd, const InetAddress&)> NewConnectionCallback;

  Acceptor(EventLoop* loop, const InetAddress& listenAddr, bool reuseport);
  ~Acceptor();

  void setNewConnectionCallback(const NewConnectionCallback& cb)
  { newConnectionCallback_ = cb; }

  void listen();

  bool listening() const { return listening_; }

 private:
  void handleRead();

  EventLoop* loop_;
  Socket acceptSocket_;
  Channel acceptChannel_;
  NewConnectionCallback newConnectionCallback_;
  bool listening_;
  int idleFd_;
};

} // namespace net
} // namespace skyline

#endif // SKYLINE_NET_ACCEPTOR_H
