include("${CMAKE_SOURCE_DIR}/cmake/packages/google-test.cmake")

function(add_test_target name)
	add_executable(${name} ${ARGN})
	set_target_properties(${name} PROPERTIES
		CXX_STANDARD 11
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF
	)
	target_link_libraries(${name} 
		PRIVATE 
			GTest::gtest_main
	)
	target_include_directories(${name}
		PUBLIC
			${CMAKE_SOURCE_DIR}/include
		PRIVATE
			${CMAKE_SOURCE_DIR}/src
	)
	gtest_discover_tests(${name})
endfunction()

function(add_cxx17_test_target name)
	add_test_target(${name} ${ARGN})
	set_target_properties(${name} PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF
	)
endfunction()
