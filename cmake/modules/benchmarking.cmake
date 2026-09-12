include(${CMAKE_SOURCE_DIR}/cmake/packages/google-benchmark.cmake)
	
function(add_benchmark_target name)
	add_executable(${name} ${ARGN})
	target_link_libraries(${name} 
		PRIVATE 
			benchmark::benchmark_main
	)
	target_include_directories(${name}
		PUBLIC
			${CMAKE_SOURCE_DIR}/include
		PRIVATE
			${CMAKE_SOURCE_DIR}/src
	)
endfunction()