cmake_minimum_required(VERSION 3.4)
project(lout)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lout)
add_subdirectory("test")


#test depends on lout
add_dependencies( Test lout )