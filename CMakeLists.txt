# cmake version minimum required 2.6
cmake_minimum_required(VERSION 2.6)

# set the project name with "skyline", and contains C and C++ languages.
project(skyline C CXX)

# Release is the default build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

# only build examples if this is the main project
if(CMAKE_PROJECT_NAME STREQUAL "skyline")
  # option provide a boolean variable
  option(SKYLINE_BUILD_EXAMPLES "Build Skyline examples" ON)
endif()

# CXX_FLAGS is the C++ compile options
set(CXX_FLAGS
  -g # debug information colecttion
  # _DVALGRID
  -DCHECK_PTHREAD_RETURN_VALUE # customer
  -D_FILE_OFFSET_BITS=64 # customer
  -Wall # warning
  -Wextra # extention warning
  -Werror # convert warning to error
  -Wconversion # Warnings can change the implicit conversion of values
  -Wno-ununsed-paramter
  -Wold-style-cast
  -Woverloaded-virtual
  -Wpointer-arith # Warning any void depending on the size of function type or function type
  -Wshadow
  -Wwrite-strings
  -march=native
  # -MMD
  -std=c++11
  -rdynamic
  )
if(CMAKE_BUILD_BITS EQUAL 32)
  list(APPEND CXX_FLAGS "-m32")
endif()
if(CMAKE_BUILD_COMPILER_ID STREQUAL "Clang")
  message("CMAKE_BUILD_COMILER_ID Clang")
  list(APPEND CXX_FLAGS "-Wno-null-dereferenct")
  list(APPEND CXX_FLAGS "-Wno-sign-conversion")
  list(APPEND CXX_FLAGS "-Wno-unused-local-typedef")
  list(APPEND CXX_FLAGS "-Wthread-safety")
  list(REMOVE_ITEM CXX_FLAGS "-rdynamic")
endif()
# message(${CXX_FLAGS}) without ";" split
# message("${CXX_FLAGS}") with ";" split
# replace all ";" to " " in CXX_FLAGS and write result into CMAKE_CXX_FLAGS
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG") # NDEBUG customer
# message(${PROJECT_BINARY_DIR}) # current dir
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

message("project source dir" ${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR})

# toupper and save into BUILD_TYPE
string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
message(STATUS "CXX_FLAGS = " ${CMAKE_CXX_FLAGS} " " ${CMAKE_CXX_FLAGS_${BUILD_TYPE}})

add_subdirectory(skyline/base)
add_subdirectory(skyline/net)
