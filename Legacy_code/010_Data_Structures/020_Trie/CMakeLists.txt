cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "Trie")
set(EXE_NAME "Trieapp")

project(${PROJECT_NAME})

INCLUDE_DIRECTORIES("C:/Program Files (x86)/googletest-distribution/include")
LINK_DIRECTORIES("C:/Program Files (x86)/googletest-distribution/lib")

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

file(GLOB project_SRC
    "src/*.h"
    "src/*.cpp"
)

add_executable(${EXE_NAME} ${project_SRC})

TARGET_LINK_LIBRARIES(${EXE_NAME} gtest gmock)

install(TARGETS ${EXE_NAME} DESTINATION ./bin)
