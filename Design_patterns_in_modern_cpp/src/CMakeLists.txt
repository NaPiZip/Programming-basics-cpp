cmake_minimum_required(VERSION 2.8.8 FATAL_ERROR)

set(EXE_NAME "Runner")

set(CMAKE_CXX_STANDARD 17)

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

file(GLOB project_SRC
    "*.h"
    "*.cpp"
)

add_executable(${EXE_NAME} ${project_SRC})
target_link_libraries(${EXE_NAME} gtest gmock)
