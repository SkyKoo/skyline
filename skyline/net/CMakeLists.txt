set(net_SRCS
  EventLoop.cpp
  Channel.cpp
  Poller.cpp
  poller/DefaultPoller.cpp
  poller/PollPoller.cpp
  poller/EPollPoller.cpp
  Timer.cpp
  TimerQueue.cpp
  SocketsOps.cpp
  EventLoopThread.cpp
  SocketsOps.cpp
  Socket.cpp
  InetAddress.cpp
  Acceptor.cpp
  TcpConnection.cpp
  Buffer.cpp
  EventLoopThreadPool.cpp
  TcpServer.cpp
  Connector.cpp
  TcpClient.cpp
  )

add_library(skyline_net ${net_SRCS})
target_link_libraries(skyline_net skyline_base)

install(TARGETS skyline_net DESTINATION lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/skyline/net)

if(SKYLINE_BUILD_EXAMPLES)
  add_subdirectory(tests)
endif()
