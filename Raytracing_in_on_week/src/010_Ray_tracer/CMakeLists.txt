set(EXE_NAME "Ray_tracer")

set(CMAKE_CXX_STANDARD 20)

file(GLOB project_SRC
    "*.h"
    "*.hpp"
    "*.c"
    "*.cpp"
)

add_executable(${EXE_NAME} ${project_SRC})
