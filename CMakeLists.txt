cmake_minimum_required(VERSION 3.0...3.28)
# set(CMAKE_C_COMPILER "/opt/rh/devtoolset-8/root/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/opt/rh/devtoolset-8/root/usr/bin/g++")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(ServerDMASampling VERSION 0.1.0 LANGUAGES C CXX)

enable_testing()

# boost
find_package(Boost REQUIRED COMPONENTS system filesystem)
if(NOT Boost_FOUND)
message(FATAL_ERROR "Boost Not found")
endif()

add_executable(ServerDMASampling src/ServerDMASampling.cpp)
include_directories(src/include src/include/proc)

target_link_libraries(ServerDMASampling
Boost::system
Boost::filesystem
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
