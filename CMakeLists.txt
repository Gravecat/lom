# CMakeLists.txt -- CMake build file for LOM. Mainly built for GCC but should support
# some other popular compilers too.

# SPDX-FileType: SOURCE
# SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
# SPDX-License-Identifier: AGPL-3.0-or-later

cmake_minimum_required(VERSION 3.13)
project(lom LANGUAGES CXX)

# Automatically default to debug builds if a type is not specified.
# This code borrowed from BearLibTerminal, copyright (c) 2013-2017 Cfyz.
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Build type was not specified, switching to 'Debug'.")
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Determine target platform.
if(WIN32)
  set(TARGET_WINDOWS 1)
elseif(MINGW)
  set(TARGET_WINDOWS 1)
  set(TARGET_MINGW 1)
elseif(UNIX AND NOT APPLE)
  set(TARGET_LINUX 1)
endif()

# Detect if MinGW is being used to cross-compile to Windows. There are simpler ways, but this way guarantees success when using WSL.
include(CheckCXXSourceCompiles)
check_cxx_source_compiles("
  #ifdef __MINGW32__
    int main() { return 0; }
  #else
    #error Not MinGW
  #endif
" HAVE_MINGW_MACRO)
if (HAVE_MINGW_MACRO)
  set(TARGET_WINDOWS 1)
  set(TARGET_MINGW 1)
  unset(TARGET_LINUX)
endif()

# An extra marker for the source files, to tell what kind of build type we're using.
if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
  add_compile_definitions(LOM_BUILD_RELEASE)
  set(RELEASE_BUILD 1)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
  add_compile_definitions(LOM_BUILD_DEBUG)
  set(DEBUG_BUILD 1)
else()
  message(FATAL_ERROR "Unrecognized build type!")
endif()

# Non-platform-specific stuff.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_definitions(__STDC_LIMIT_MACROS)
add_compile_definitions(_USE_MATH_DEFINES)
set(LOM_BIN "$<TARGET_FILE:lom>")

# Source files.
set(LOM_CPPS
  src/main.cpp
)

# Binary file. LOM_RC should be blank for non-Windows builds.
add_executable(lom ${LOM_CPPS} ${LOM_RC})
target_link_libraries(lom PRIVATE ${CMAKE_THREAD_LIBS_INIT})

# Compiler-specific flags.
target_compile_options(lom PRIVATE
  $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
    -Wall -Wextra -pedantic -pedantic-errors>
  $<$<CXX_COMPILER_ID:MSVC>:
    /W4 /permissive->
)

# Compiler-specific optimization and debug flags.
target_compile_options(lom PRIVATE
  $<$<CONFIG:Release>:
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-O2>
	$<$<CXX_COMPILER_ID:MSVC>:/O2>>
  $<$<CONFIG:Debug>:
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-g -Og>
	$<$<CXX_COMPILER_ID:MSVC>:/Od /Zi>>
)

# Compiler-specific stripping of symbols.
target_link_options(lom PRIVATE
  $<$<AND:$<CONFIG:Release>,$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>>:-s>
)

# Windows-specific stuff.
if(TARGET_WINDOWS)
  target_compile_definitions(lom PRIVATE
    LOM_TARGET_WINDOWS
	WIN32_LEAN_AND_MEAN
  )
  target_link_libraries(lom PRIVATE
    $<$<BOOL:${TARGET_MINGW}>:mingw32>
	shlwapi
	ntdll
  )
  set(LOM_BIN "$<TARGET_FILE:lom>.exe")
endif(TARGET_WINDOWS)

# Post-build, make a 'bin' folder and copy the binary file in there.
add_custom_command(TARGET lom POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/bin"
  COMMAND ${CMAKE_COMMAND} -E copy "${LOM_BIN}" "${CMAKE_BINARY_DIR}/bin"
)
