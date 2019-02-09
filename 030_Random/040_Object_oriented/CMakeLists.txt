cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "Chapter_01")
set(EXE_NAME "Runner")

project(${PROJECT_NAME} LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic-errors")

INCLUDE_DIRECTORIES("C:/Program Files (x86)/googletest-distribution/include")
LINK_DIRECTORIES("C:/Program Files (x86)/googletest-distribution/lib")

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

file(GLOB project_SRC
    "src/*.h"
    "src/*.cpp"
)

add_executable(${EXE_NAME} ${project_SRC})
target_link_libraries(${EXE_NAME} gtest gmock)
