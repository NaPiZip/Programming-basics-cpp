set(EXE_NAME "020_Section")

set(CMAKE_CXX_STANDARD 20)

file(GLOB project_SRC
    "*.h"
    "*.hpp"
    "*.c"
    "*.cpp"
)

add_executable(${EXE_NAME} ${project_SRC})
