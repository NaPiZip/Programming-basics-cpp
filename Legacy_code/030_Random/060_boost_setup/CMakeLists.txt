cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "accumulaters")
set(EXE_NAME "example")

project(${PROJECT_NAME} LANGUAGES CXX)
set(CMAKE_PREFIX_PATH E:/010_GitHub/boost/stage/lib/cmake/Boost-1.72.0)

find_package(boost REQUIRED 1.72.0 serialization regex)

file(GLOB project_SRC
    "*.h"
    "*.cpp"
)

if(NOT Boost_FOUND)
    message(fatal_error "Boost was not found. See FindBoost.cmake for details.")
endif()

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(${EXE_NAME} ${project_SRC})
    target_link_libraries(${EXE_NAME} ${Boost_LIBRARIES})
    message(STATUS ${Boost_LIBRARIES})
endif()


#INCLUDE_DIRECTORIES($ENV{Boost_INCLUDEDIR})
#LINK_DIRECTORIES($ENV{Boost_LIBRARYDIR})

#file(GLOB project_SRC
#    "*.h"
#    "*.cpp"
#)

#add_executable(${EXE_NAME} ${project_SRC})
