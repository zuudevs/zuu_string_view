include("${CMAKE_SOURCE_DIR}/cmake/packages/google-test.cmake")

function(add_test_target name)
	add_executable(${name} ${ARGN})
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