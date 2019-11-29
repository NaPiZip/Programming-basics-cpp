set(RUNNER_NAME "benchmark")

set(CMAKE_CXX_STANDARD 17)

find_package(Celero)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../010_Ray_tracer)

file(GLOB project_SRC
    "*.h"
    "*.hpp"
    "*.c"
    "*.cpp"
)

include_directories(${CELERO_INCLUDE_DIRS})
add_executable(${RUNNER_NAME} ${project_SRC} )
target_link_libraries(${RUNNER_NAME} ${CELERO_LIBRARIES})
