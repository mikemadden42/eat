cmake_minimum_required(VERSION 2.8)

project(eat CXX)

set (CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -march=native")

add_executable(eat eat.cc)
