set(TEST_RUNNER_NAME "unit_test")

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../010_Ray_tracer)

file(GLOB project_SRC
    "*.h"
    "*.hpp"
    "*.c"
    "*.cpp"
)

add_executable(${TEST_RUNNER_NAME} ${project_SRC})
target_link_libraries(${TEST_RUNNER_NAME} gtest gmock)
