cmake_minimum_required(VERSION 3.16)

project(yadro_task)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES
		src/*.cpp
		src/*.h
	)

add_executable(yadro_task ${SOURCES})
