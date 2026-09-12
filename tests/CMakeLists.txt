add_test_target(test_strv
	${CMAKE_CURRENT_SOURCE_DIR}/unit/strv_constructor.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/unit/strv_assignment_op.cpp
)

add_custom_target(unit_tests)
add_dependencies(unit_tests
	test_strv
)