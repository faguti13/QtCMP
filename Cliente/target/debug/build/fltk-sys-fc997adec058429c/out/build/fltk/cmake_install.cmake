# Install script for directory: /home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/fltk

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/build/fltk/zlib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/build/fltk/png/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/build/fltk/jpeg/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/build/fltk/src/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/fltk/FL" USE_SOURCE_PERMISSIONS FILES_MATCHING REGEX "/[^/]*\\.[hH]$" REGEX "/fl\\_config\\.h$" EXCLUDE)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/build/fltk/FL" USE_SOURCE_PERMISSIONS FILES_MATCHING REGEX "/[^/]*\\.[hH]$")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fltk/FLTK-Targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fltk/FLTK-Targets.cmake"
         "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/build/fltk/CMakeFiles/Export/d834f99d2561e0cf606204aa52b7071e/FLTK-Targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fltk/FLTK-Targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/fltk/FLTK-Targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/fltk" TYPE FILE FILES "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/build/fltk/CMakeFiles/Export/d834f99d2561e0cf606204aa52b7071e/FLTK-Targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/fltk" TYPE FILE FILES "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/build/fltk/CMakeFiles/Export/d834f99d2561e0cf606204aa52b7071e/FLTK-Targets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/fltk" TYPE FILE FILES "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/build/fltk/etc/FLTKConfig.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/fltk" TYPE FILE FILES "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/fltk/CMake/FLTK-Functions.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM FILES "/home/emmanuel/CLionProjects/Cliente2/target/debug/build/fltk-sys-fc997adec058429c/out/build/fltk/bin/fltk-config")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man1" TYPE FILE RENAME "fltk-config.1" FILES "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/fltk/documentation/src/fltk-config.man")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man3" TYPE FILE RENAME "fltk.3" FILES "/home/emmanuel/.cargo/registry/src/index.crates.io-6f17d22bba15001f/fltk-sys-1.4.26/cfltk/fltk/documentation/src/fltk.man")
endif()

