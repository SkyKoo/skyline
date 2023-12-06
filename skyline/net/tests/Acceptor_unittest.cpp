
#include "skyline/net/Acceptor.h"
#include "skyline/net/InetAddress.h"
#include "skyline/net/EventLoop.h"
#include "skyline/net/SocketsOps.h"

using namespace skyline;
using namespace skyline::net;

void print(EventLoop* p = NULL)
{
  printf("print: pid = %d, tid = %d, loop = %p\n",
         getpid(), CurrentThread::tid(), p);
}

void newConnection(int sockfd, const InetAddress& peerAddr)
{
  printf("newConnection(): accepted a new connection from %s\n",
      peerAddr.toIpPort().c_str());
  ::write(sockfd, "How are you?\n", 13);
  sockets::close(sockfd);
}

int main()
{
  print();

  InetAddress listenAddr(9981);
  EventLoop loop;

  Acceptor acceptor(&loop, listenAddr, true);
  acceptor.setNewConnectionCallback(newConnection);
  acceptor.listen();

  InetAddress listenAddr2(9980);
  Acceptor acceptor2(&loop, listenAddr2, true);
  acceptor2.setNewConnectionCallback(newConnection);
  acceptor2.listen();

  loop.loop();
}

// nc 127.0.0.1 9981 to test
