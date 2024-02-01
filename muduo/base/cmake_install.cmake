# Install script for directory: /home/kali/Desktop/muduo-cpp17/muduo/base

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/kali/Desktop/muduo-cpp17/lib/libmuduo_base.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/muduo/base" TYPE FILE FILES
    "/home/kali/Desktop/muduo-cpp17/muduo/base/AsyncLogging.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/Atomic.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/BlockingQueue.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/BoundedBlockingQueue.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/Condition.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/CountDownLatch.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/CurrentThread.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/Date.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/Exception.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/FileUtil.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/GzipFile.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/LogFile.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/LogStream.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/Logging.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/MoveToThread.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/Msgpack.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/Mutex.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/ProcessInfo.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/Signal.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/Singleton.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/StringPiece.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/Thread.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/ThreadLocal.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/ThreadLocalSingleton.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/ThreadPool.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/TimeZone.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/Timestamp.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/Types.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/WeakCallback.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/copyable.h"
    "/home/kali/Desktop/muduo-cpp17/muduo/base/noncopyable.h"
    )
endif()

