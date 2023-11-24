set(net_SRCS
  EventLoop.cpp
  )

add_library(skyline_net ${net_SRCS})
target_link_libraries(skyline_net skyline_base)

install(TARGETS skyline_net DESTINATION lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/skyline/net)
