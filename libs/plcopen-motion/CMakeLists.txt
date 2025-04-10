cmake_minimum_required(VERSION 3.10)
project(RTmotion VERSION 0.3.0 LANGUAGES CXX)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -Wno-unused-parameter -Wno-unused-function -Wno-unused-but-set-variable)
endif()

# Default options
option(COBALT "Enable compiling with Xenomai" OFF)
option(TEST "Enable unit test" OFF)
option(DEBUG "Enable debug print" OFF)

# Default file directory path 
set(XENOMAI_DIR "/usr/xenomai" CACHE PATH "Root directory of Xenomai.")
set(XENO_BINDIR "${XENOMAI_DIR}/bin" CACHE PATH "Root directory of Xenomai.")
set(SYSTEM_ROOT "/usr" CACHE PATH "System root directory used to find Python")

if(DEBUG)
  add_definitions(-DDEBUG)
endif(DEBUG)

# Set C C++ flags
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3 -fPIC -ggdb3")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS} -std=c++17")

# Set default install directories
SET(CMAKE_INSTALL_INCLUDEDIR include)
SET(CMAKE_INSTALL_LIBDIR lib)
SET(CMAKE_INSTALL_BINDIR bin)

# INSTALL_BINDIR is used at command line to define executable output directory
if(NOT INSTALL_BINDIR)
  set(INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR})
endif()

include_directories(
  include
)

find_package(ruckig REQUIRED)

# Add Xenomai compile flags
if (COBALT)
  execute_process(COMMAND ${XENO_BINDIR}/xeno-config --skin posix --cc OUTPUT_VARIABLE XENO_CC OUTPUT_STRIP_TRAILING_WHITESPACE)
  execute_process(COMMAND ${XENO_BINDIR}/xeno-config --skin posix --cflags OUTPUT_VARIABLE XENO_CFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
  execute_process(COMMAND ${XENO_BINDIR}/xeno-config --skin posix --auto-init-solib --ldflags OUTPUT_VARIABLE XENO_LDFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
  set(CMAKE_CC "${CMAKE_CC} ${XENO_CC}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${XENO_CFLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${XENO_LDFLAGS}")

  message(STATUS "XENO_CC: ${XENO_CC}")
  message(STATUS "XENO_CFLAGS: ${XENO_CFLAGS}")
  message(STATUS "XENO_LDFLAGS: ${XENO_LDFLAGS}")
endif(COBALT)

add_subdirectory(src)

if (TEST)
  # Find GTEST
  find_package(GTest REQUIRED)
  message(STATUS "GTEST_INCLUDE_DIRS: ${GTEST_INCLUDE_DIRS}")
  message(STATUS "GTEST_BOTH_LIBRARIES: ${GTEST_BOTH_LIBRARIES}")
  # Include gtest headers
  include_directories(
    ${GTEST_INCLUDE_DIRS}
  )

  add_subdirectory(test)
endif(TEST)

install(
  DIRECTORY include/${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
