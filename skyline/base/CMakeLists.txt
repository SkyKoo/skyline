set(base_SRCS
  Thread.cpp
  CurrentThread.cpp
  Logging.cpp
  LogStream.cpp
  Timestamp.cpp
  TimeZone.cpp
  )

add_library(skyline_base ${base_SRCS})
target_link_libraries(skyline_base pthread rt)

install(TARGETS skyline_base DESTINATION lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/skyline/base)
