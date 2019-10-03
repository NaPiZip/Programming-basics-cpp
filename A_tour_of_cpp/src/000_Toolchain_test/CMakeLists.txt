set(EXE_NAME "000_Toolchain_test")

set(CMAKE_CXX_STANDARD 17)

file(GLOB project_SRC
    "*.h"
    "*.cpp"
)

add_executable(${EXE_NAME} ${project_SRC})
target_link_libraries(${EXE_NAME} gtest gmock)
