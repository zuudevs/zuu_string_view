add_test_target(api_test
	${CMAKE_CURRENT_SOURCE_DIR}/unit/string_view_assignment_operator.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/unit/string_view_constructor.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/unit/string_view_find_apis.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/unit/string_view_substr_apis.cpp
)

add_custom_target(unit_tests)
add_dependencies(unit_tests
	api_test
)