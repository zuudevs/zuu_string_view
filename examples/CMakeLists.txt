add_executable(example_strv
	${CMAKE_SOURCE_DIR}/examples/example_strv.cpp
)

target_include_directories(internal
	PUBLIC
		${CMAKE_SOURCE_DIR}/include
	PRIVATE
		${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(example_strv PRIVATE internal)