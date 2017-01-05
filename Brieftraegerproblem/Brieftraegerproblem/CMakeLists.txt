message(STATUS "Building tests")

set(target brieftraegerproblem_tests)
message(STATUS "Building application ${target}")

set(sources
	main.cpp
)

add_executable(${target} ${sources})
add_test(all "${EXECUTABLE_OUTPUT_PATH}/${target}")
