set(EXE_NAME "170_Chapter_17")

set(CMAKE_CXX_STANDARD 17)

file(GLOB project_SRC
    "*.h"
    "*.hpp"
    "*.c"
    "*.cpp"
)

add_executable(${EXE_NAME} ${project_SRC})
target_link_libraries(${EXE_NAME} gtest gmock)
