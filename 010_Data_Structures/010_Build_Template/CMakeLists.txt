cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "Template")
set(EXE_NAME "myapp")

project(${PROJECT_NAME})

INCLUDE_DIRECTORIES("C:/Program Files/googletest/googletest/include")
INCLUDE_DIRECTORIES("C:/Program Files/googletest/googlemock/include")

LINK_DIRECTORIES("C:/Program Files/googletest/build/googlemock/gtest")
LINK_DIRECTORIES("C:/Program Files/googletest/build/googlemock")


set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/020_build)

add_executable(${EXE_NAME} 010_src/unittest.cpp
                     src/*.hpp
                     src/*.cpp)

TARGET_LINK_LIBRARIES(EXE_NAME gtest gmock)

install(TARGETS ${EXE_NAME} DESTINATION ./bin)
