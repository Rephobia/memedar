project(memedar_test LANGUAGES CXX)

file(GLOB_RECURSE cpp_files ${PROJECT_SOURCE_DIR} "*.cpp")

add_executable(${PROJECT_NAME} ${cpp_files})

find_package(Catch2 REQUIRED)
target_link_libraries(${PROJECT_NAME} memedar_core Catch2::Catch2)

include(Catch)
catch_discover_tests(${PROJECT_NAME})
add_custom_target(ctest_target ALL COMMAND ctest DEPENDS ${PROJECT_NAME})

cppcheck_targets(TARGETS ${PROJECT_NAME}
                 INCLUDE ${MEMEDAR_INCLUDE_DIRECTORY}
                 SUPPRESS knownConditionTrueFalse)
