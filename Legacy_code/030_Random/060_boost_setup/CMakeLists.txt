cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "accumulaters")
set(EXE_NAME "example")

project(${PROJECT_NAME} LANGUAGES CXX)

set(Boost_VERBOSE ON)
find_package(boost REQUIRED 1.72.0)

file(GLOB project_SRC
    "*.h"
    "*.cpp"
)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(${EXE_NAME} ${project_SRC})
    message(STATUS ${Boost_LIBRARIES})
    target_link_libraries(${EXE_NAME} ${Boost_LIBRARIES})
endif()


#INCLUDE_DIRECTORIES($ENV{Boost_INCLUDEDIR})
#LINK_DIRECTORIES($ENV{Boost_LIBRARYDIR})

#file(GLOB project_SRC
#    "*.h"
#    "*.cpp"
#)

#add_executable(${EXE_NAME} ${project_SRC})
