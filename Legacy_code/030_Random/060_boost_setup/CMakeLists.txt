cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME "accumulaters")
set(EXE_NAME "example")

project(${PROJECT_NAME} LANGUAGES CXX)

set(Boost_DEBUG OFF)
set(Boost_USE_STATIC_LIBS       OFF)
set(Boost_USE_MULTITHREADED     ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(boost 1.72.0 REQUIRED serialization)

if(NOT Boost_FOUND)
    message(fatal_error "Boost was not found. See FindBoost.cmake for details.")
endif()

file(GLOB project_SRC
    "*.h"
    "*.cpp"
)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
    add_executable(${EXE_NAME} ${project_SRC})
endif()
