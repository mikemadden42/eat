cmake_minimum_required(VERSION 2.8)

project(eat CXX)

add_definitions(-Wall -O2 -std=c++14 -march=native)

# https://cmake.org/cmake/help/v3.0/module/FindBoost.html
find_package(Boost COMPONENTS program_options)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(eat eat.cc)
    target_link_libraries(eat ${Boost_LIBRARIES})
endif()
