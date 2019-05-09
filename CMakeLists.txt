cmake_minimum_required(VERSION 3.13)

project(epi-code)

set(CGAL_DO_NOT_WARN_ABOUT_CMAKE_BUILD_TYPE TRUE)

add_definitions(-D_LIBCPP_INLINE_VISIBILITY= -D'_LIBCPP_EXTERN_TEMPLATE\(...\)=')

set(CMAKE_CXX_STANDARD 17)

find_package(boost REQUIRED)
find_package(CGAL REQUIRED COMPONENTS Core)

include_directories(src
                    ${Boost_INCLUDE_DIRS})

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
    message(STATUS "dir='${dir}'")
endforeach()

add_subdirectory(src/bitCount)
add_subdirectory(src/cgalBoolean2D)
add_subdirectory(src/graphCycles)
add_subdirectory(src/listCycles)
add_subdirectory(src/maxSubarrayXOR)
add_subdirectory(src/mergeLists)
add_subdirectory(src/parity)
add_subdirectory(src/partition)
