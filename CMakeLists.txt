cmake_minimum_required(VERSION 3.20)
project(
	zuu_strv
	DESCRIPTION "`string_view` is a lightweight, non-owning reference object that stores only a pointer to the start of the data and the character length, without copying or allocating new memory. It is used to enhance performance through a zero-copy approach, enabling efficient reading, searching, or processing of various text sources in high-performance applications."
	VERSION 0.1.0
	LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/modules/init.cmake)
include(cmake/modules/output.cmake)
include(cmake/modules/warning.cmake)
include(cmake/modules/sanitizing.cmake)
include(cmake/modules/optimizing.cmake)

add_subdirectory(${CMAKE_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_SOURCE_DIR}/tests)
add_subdirectory(${CMAKE_SOURCE_DIR}/benchmarks)
add_subdirectory(${CMAKE_SOURCE_DIR}/examples)