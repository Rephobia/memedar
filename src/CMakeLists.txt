project(memedar_core LANGUAGES CXX)

# library
file(GLOB_RECURSE cpp_files ${PROJECT_SOURCE_DIR} "*.cpp")
list(REMOVE_ITEM cpp_files "${PROJECT_SOURCE_DIR}/main.cpp")
add_library(${PROJECT_NAME} OBJECT ${cpp_files})

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets sqlite3 stdc++fs)
target_include_directories(${PROJECT_NAME} PUBLIC "${MEMEDAR_INCLUDE_DIRECTORY}")
target_compile_options(${PROJECT_NAME} PUBLIC
                       -Wall -Wextra -Werror -Weffc++ -Wold-style-cast
                       -Wunreachable-code -Wfatal-errors -pedantic-errors -Winit-self)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# executable
add_executable(memedar "${PROJECT_SOURCE_DIR}/main.cpp")
target_link_libraries(memedar ${PROJECT_NAME})
set_target_properties(memedar PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# cppcheck source
cppcheck_targets(TARGETS ${PROJECT_NAME} memedar
                 PROPERTY memedar_cppcheck_property
                 INCLUDE ${MEMEDAR_INCLUDE_DIRECTORY}
                 SUPPRESS uninitMemberVar functionConst)

