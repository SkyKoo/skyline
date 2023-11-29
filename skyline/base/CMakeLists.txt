set(base_SRCS
  Thread.cpp
  CurrentThread.cpp
  Logging.cpp
  LogStream.cpp
  Timestamp.cpp
  TimeZone.cpp
  Date.cpp
  Condition.cpp
  CountDownLatch.cpp
  )

add_library(skyline_base ${base_SRCS})
target_link_libraries(skyline_base pthread rt)

install(TARGETS skyline_base DESTINATION lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/skyline/base)

if (SKYLINE_BUILD_EXAMPLES)
  add_subdirectory(tests)
endif()
