cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(memedar LANGUAGES CXX)

set(MEMEDAR_INCLUDE_DIRECTORY ${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE MEMEDAR_SOURCE_FILES ${CMAKE_SOURCE_DIR} "src/*.cpp")

add_executable(${PROJECT_NAME} ${MEMEDAR_SOURCE_FILES})

add_custom_target(
	cppcheck ALL
	COMMAND /usr/bin/cppcheck
	--enable=all
	--std=c++11
	--template=gcc
	--inconclusive
	--suppress=uninitMemberVar
	--suppress=missingIncludeSystem
	--quiet
	-I ${MEMEDAR_INCLUDE_DIRECTORY}
	${MEMEDAR_SOURCE_FILES}
)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets sqlite3 stdc++fs)
target_include_directories(${PROJECT_NAME} PRIVATE ${MEMEDAR_INCLUDE_DIRECTORY})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -Weffc++
				       -Wold-style-cast -Wunreachable-code
				       -Wfatal-errors -pedantic-errors -Winit-self)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
