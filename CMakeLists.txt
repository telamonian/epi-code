cmake_minimum_required(VERSION 3.13)

project(epi-code)

set(CMAKE_CXX_STANDARD 11)

find_package(boost REQUIRED)

include_directories(src
                    ${Boost_INCLUDE_DIRS})

add_subdirectory(src/bitCount)
add_subdirectory(src/graphCycles)
add_subdirectory(src/listCycles)
add_subdirectory(src/mergeLists)
add_subdirectory(src/parity)
add_subdirectory(src/partition)
