cmake_minimum_required(VERSION 3.0.0)
project(ServerDMASampling VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
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
