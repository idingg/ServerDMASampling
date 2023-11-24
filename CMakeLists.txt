cmake_minimum_required(VERSION 3.0...3.28)

if(UNIX)
    # set(CMAKE_C_COMPILER "/opt/rh/devtoolset-8/root/usr/bin/gcc")
    # set(CMAKE_CXX_COMPILER "/opt/rh/devtoolset-8/root/usr/bin/g++")
    set(CMAKE_C_COMPILER "/opt/rh/gcc-toolset-13/root/usr/bin/gcc")
    set(CMAKE_CXX_COMPILER "/opt/rh/gcc-toolset-13/root/usr/bin/g++" CACHE STRING "C++ Compiler")
elseif(WIN32)
    set(CMAKE_C_COMPILER "C:\\MinGW\\bin\\gcc.exe")
    set(CMAKE_CXX_COMPILER "C:\\MinGW\\bin\\g++.exe")
    include_directories("C:\\Users\\idingg\\Downloads\\boost_1_83_0\\bin.v2\\libs")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

project(ServerDMASampling VERSION 0.1.0 LANGUAGES C CXX)

enable_testing()

# boost
find_package(Boost REQUIRED COMPONENTS system filesystem)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost Not found")
endif()
include_directories(${Boost_INCLUDE_DIRS})
message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")

add_executable(ServerDMASampling ${CMAKE_CURRENT_SOURCE_DIR}/src/ServerDMASampling.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include ${CMAKE_CURRENT_SOURCE_DIR}/src/include/proc)

target_link_libraries(ServerDMASampling
Boost::system
Boost::filesystem
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
