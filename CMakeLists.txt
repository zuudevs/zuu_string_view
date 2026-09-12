cmake_minimum_required(VERSION 3.20)
project(
	zuu_strv
	DESCRIPTION "A lightweight, non-owning `string_view` implementation bringing C++17 `string_view` features to C++11 with zero-copy efficiency."
	VERSION 0.3.0
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
include(cmake/modules/testing.cmake)

add_subdirectory(${CMAKE_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_SOURCE_DIR}/tests)
add_subdirectory(${CMAKE_SOURCE_DIR}/benchmarks)
add_subdirectory(${CMAKE_SOURCE_DIR}/examples)