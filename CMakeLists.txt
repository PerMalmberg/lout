cmake_minimum_required(VERSION 3.28)
project(lout)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lout)
add_subdirectory(test)

add_dependencies(Test lout)
