
#ifndef SKYLINE_NET_TCPCONNECTION_H
#define SKYLINE_NET_TCPCONNECTION_H

#include "skyline/base/noncopyable.h"
#include "skyline/net/InetAddress.h"
#include "skyline/net/Callbacks.h"
#include "skyline/net/Buffer.h"

#include <boost/any.hpp>

#include <memory>

// struct tcp_info is in <netinet/tcp.h>
struct tcp_info;

namespace skyline
{
namespace net
{

class EventLoop;
class Channel;
class Socket;

///
/// TCP connection, for both client and server usage.
///
/// This is an interface class, so don't expose too much details.
class TcpConnection : noncopyable,
                      public std::enable_shared_from_this<TcpConnection>
{
 public:
  /// Constructs a TcpConnection with a connected sockfd
  ///
  /// User should not create this object.
  TcpConnection(EventLoop* loop,
                const string& name,
                int sockfd,
                const InetAddress& localAddr,
                const InetAddress& peerAddr);
  ~TcpConnection();

  EventLoop* getLoop() const { return loop_; }
  const string& name() const { return name_; }
  const InetAddress& localAddress() const { return localAddr_; }
  const InetAddress& peerAddress() const { return peerAddr_; }
  bool connected() const { return state_ == kConnected; }
  bool disconnected() const { return state_ == kDisconnected; }

  // return true if success.
  bool getTcpInfo(struct tcp_info*) const;
  string getTcpInfoString() const;

  // void send(string&& message); // C++11
  void send(const void* message, int len);
  void send(const StringPiece& message);
  // void send(Buffer&& messgae); // C++11
  void send(Buffer* message); // this one will swap data
  void shutdown();

  void forceClose();
  void forceCloseWithDelay(double seconds);
  void setTcpNoDelay(bool on);

  // reading or not
  void startRead();
  void stopRead();
  bool isReading() const { return reading_; } // NOT thread safe, may race with start/stopReadInLoop

  void setContext(const boost::any& context)
  { context_ = context; }

  const boost::any& getContext() const
  { return context_; }

  boost::any* getMutableContext()
  { return &context_; }

  void setConnectionCallback(const ConnectionCallback& cb)
  { connectionCallback_ = cb; }

  void setMessageCallback(const MessageCallback& cb)
  { messageCallback_ = cb; }

  void setWriteCompleteCallback(const WriteCompleteCallback& cb)
  { writeCompleteCallback_ = cb; }

  void setHighWaterMarkCallback(const HighWaterMarkCallback& cb)
  { highWaterMarkCallback_ = cb; }

  /// Advanced interface
  Buffer* inputBuffer()
  { return &inputBuffer_; }

  Buffer* outputBuffer()
  { return &outputBuffer_; }

  /// Internal use only.
  void setCloseCallback(const CloseCallback& cb)
  { closeCallback_ = cb; }

  // called from TcpServer or TcpClient
  // called when TcpServer accepts a new connection
  void connectEstablished(); // should be called only once
  // called from TcpServer or TcpClient
  // called when TcpServer has removed me from its map
  void connectDestroyed(); // should be called only once

 private:
  enum StateE { kDisconnected, kConnecting, kConnected, kDisconnecting };

  void handleRead(Timestamp receiveTime);
  void handleWrite();
  void handleClose();
  void handleError();

  // void sendInLoop(string&& message);
  void sendInLoop(const StringPiece& message);
  void sendInLoop(const void* message, size_t len);
  void shutdownInLoop();
  void forceCloseInLoop();

  void setState(StateE s) { state_ = s; }
  const char* stateToString() const;

  void startReadInLoop();
  void stopReadInLoop();

  EventLoop* loop_;
  const string name_;
  StateE state_; // FIXME: use atomic variable
  bool reading_;
  // we don't expose those classes to client.
  std::unique_ptr<Socket> socket_;
  std::unique_ptr<Channel> channel_;
  const InetAddress localAddr_;
  const InetAddress peerAddr_;
  ConnectionCallback connectionCallback_;
  MessageCallback messageCallback_;
  WriteCompleteCallback writeCompleteCallback_;
  HighWaterMarkCallback highWaterMarkCallback_;
  CloseCallback closeCallback_;
  size_t highWaterMark_;
  Buffer inputBuffer_;
  Buffer outputBuffer_; // FIXME: use list<Buffer> as output buffer.
  boost::any context_;
  // FIXME: creationTime_, lastReceiveTime_
  //        bytesReceived_, bytesSent_
};

} // namespace net
} // namespace skyline

#endif // SKYLINE_NET_TCPCONNECTION_H
