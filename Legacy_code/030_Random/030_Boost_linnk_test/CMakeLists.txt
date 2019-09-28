cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "Template")
set(EXE_NAME "myapp")

project(${PROJECT_NAME} LANGUAGES CXX)


INCLUDE_DIRECTORIES("C:/Program Files/Boost_1_63_0/boost_1_63_0/build/include/boost-1_63")
LINK_DIRECTORIES("C:/Program Files/Boost_1_63_0/boost_1_63_0/build/lib")

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

file(GLOB project_SRC
    "src/*.h"
    "src/*.cpp"
)

add_executable(${EXE_NAME} ${project_SRC})
target_link_libraries(${EXE_NAME} boost_system-mgw63-mt-1_63 boost_thread-mgw63-mt-1_63)
