# Install script for directory: /home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/fltk/zlib

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/build/fltk/lib/libfltk_z.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/FL/images" TYPE FILE FILES
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/fltk/zlib/zconf.h"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/fltk/zlib/zlib.h"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/fltk/zlib/zutil.h"
    )
endif()

