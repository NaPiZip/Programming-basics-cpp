cmake_minimum_required(VERSION 3.6)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

project(Ray_tracing_in_one_weekend)

add_subdirectory(src/thirdparty/googletest)
add_subdirectory(src)
