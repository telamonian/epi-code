cmake_minimum_required(VERSION 3.13)

project(epi-code)

include_directories(src)

add_subdirectory(src/parity)
add_subdirectory(src/bitCount)
add_subdirectory(src/partition)

