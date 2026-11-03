cmake_minimum_required(VERSION 3.10)

project(eat CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(eat eat.cc)
if (NOT MSVC)
  target_compile_options(eat PRIVATE -Wall -Wextra -pedantic)
endif()

enable_testing()
add_test(NAME allocate_1gb COMMAND eat 1)
foreach(arg abc 5abc 0 -1 99999999999999999999 17179869184)
  add_test(NAME reject_${arg} COMMAND eat ${arg})
  set_tests_properties(reject_${arg} PROPERTIES WILL_FAIL TRUE)
endforeach()
