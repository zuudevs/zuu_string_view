cmake_minimum_required(VERSION 3.20)
project(
	zuu_string_view
	DESCRIPTION "A lightweight, non-owning `string_view` implementation bringing C++17 `string_view` features to C++11 with zero-copy efficiency."
	VERSION 0.4.0
	LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/modules/init.cmake)
include(cmake/modules/output.cmake)
include(cmake/modules/warning.cmake)
include(cmake/modules/sanitizing.cmake)
include(cmake/modules/optimizing.cmake)
include(cmake/modules/testing.cmake)
include(cmake/modules/benchmarking.cmake)
include(cmake/tools/clang-tidy.cmake)
include(cmake/tools/clang-format.cmake)

add_subdirectory(${CMAKE_SOURCE_DIR}/tests)
add_subdirectory(${CMAKE_SOURCE_DIR}/benchmarks)
add_subdirectory(${CMAKE_SOURCE_DIR}/examples)