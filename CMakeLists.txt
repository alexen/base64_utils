cmake_minimum_required(VERSION 3.5)

add_definitions(-std=c++11 -Wall -pedantic)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(BUILD_TEST "Build tests" ON)
option(BUILD_BENCHMARK "Speed tests using Celero C++" ON)

set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0 -DDEBUG -D_GLIBCXX_DEBUG")

set(LOCAL_ROOT "$ENV{HOME}/.local")
set(LOCAL_INCLUDE_DIR "${LOCAL_ROOT}/include")
set(LOCAL_LIBRARY_DIR "${LOCAL_ROOT}/lib")

include_directories("${LOCAL_INCLUDE_DIR}")
include_directories("${CMAKE_SOURCE_DIR}")
link_directories("${LOCAL_LIBRARY_DIR}")

if(BUILD_TEST)
     add_subdirectory(googletest)
     include_directories("${CMAKE_SOURCE_DIR}/googletest/googletest/include")
     enable_testing()
endif()

if(BUILD_BENCHMARK)
     add_subdirectory(Celero)
     include_directories("${CMAKE_SOURCE_DIR}/Celero/include")
endif()

add_subdirectory(base64)

add_executable(main
     main.cpp
)
target_link_libraries(main
     boost_based
)