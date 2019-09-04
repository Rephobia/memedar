cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(memedar LANGUAGES CXX)

set(MEMEDAR_INCLUDE_DIRECTORY "${CMAKE_SOURCE_DIR}/include")
include(${CMAKE_SOURCE_DIR}/cmake/cppcheck_targets.cmake)

add_subdirectory(src)
enable_testing()
add_subdirectory(test)

get_property(memedar_cppcheck_commands GLOBAL PROPERTY memedar_cppcheck_property)
add_custom_target(memedar_cppcheck ALL VERBATIM COMMAND ${memedar_cppcheck_commands})
