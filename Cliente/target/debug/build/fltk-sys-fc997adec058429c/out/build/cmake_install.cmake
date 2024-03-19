# Install script for directory: /home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk

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
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/lib/libcfltk.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/lib" TYPE STATIC_LIBRARY FILES "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/build/libcfltk.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk/cfl.h;/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk/cfl_box.h;/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk/cfl_browser.h;/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk/cfl_button.h;/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk/cfl_dialog.h;/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk/cfl_draw.h;/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk/cfl_enums.h;/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk/cfl_group.h;/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk/cfl_image.h;/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk/cfl_input.h;/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk/cfl_lock.h;/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk/cfl_macros.h;/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk/cfl_menu.h;/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk/cfl_misc.h;/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk/cfl_prefs.h;/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk/cfl_printer.h;/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk/cfl_surface.h;/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk/cfl_table.h;/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk/cfl_text.h;/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk/cfl_tree.h;/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk/cfl_utils.h;/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk/cfl_valuator.h;/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk/cfl_widget.h;/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk/cfl_widget.hpp;/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk/cfl_window.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/include/cfltk" TYPE FILE FILES
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/include/cfl.h"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/include/cfl_box.h"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/include/cfl_browser.h"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/include/cfl_button.h"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/include/cfl_dialog.h"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/include/cfl_draw.h"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/include/cfl_enums.h"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/include/cfl_group.h"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/include/cfl_image.h"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/include/cfl_input.h"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/include/cfl_lock.h"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/include/cfl_macros.h"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/include/cfl_menu.h"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/include/cfl_misc.h"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/include/cfl_prefs.h"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/include/cfl_printer.h"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/include/cfl_surface.h"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/include/cfl_table.h"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/include/cfl_text.h"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/include/cfl_tree.h"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/include/cfl_utils.h"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/include/cfl_valuator.h"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/include/cfl_widget.h"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/include/cfl_widget.hpp"
    "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/include/cfl_window.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/share/cmake/cfltk/cfltkConfig.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/share/cmake/cfltk/cfltkConfig.cmake"
         "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/build/CMakeFiles/Export/cb06824e5b4844e182a9dea0f59a92a4/cfltkConfig.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/share/cmake/cfltk/cfltkConfig-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/share/cmake/cfltk/cfltkConfig.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/share/cmake/cfltk/cfltkConfig.cmake")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/share/cmake/cfltk" TYPE FILE FILES "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/build/CMakeFiles/Export/cb06824e5b4844e182a9dea0f59a92a4/cfltkConfig.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/share/cmake/cfltk/cfltkConfig-release.cmake")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    file(INSTALL DESTINATION "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/share/cmake/cfltk" TYPE FILE FILES "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/build/CMakeFiles/Export/cb06824e5b4844e182a9dea0f59a92a4/cfltkConfig-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/share/cmake/cfltk/cfltkConfigVersion.cmake")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/share/cmake/cfltk" TYPE FILE FILES "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/build/cfltkConfigVersion.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/share/pkgconfig/cfltk.pc")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/share/pkgconfig" TYPE FILE FILES "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/build/cfltk.pc")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/build/fltk/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
