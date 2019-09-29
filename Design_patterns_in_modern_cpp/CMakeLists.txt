cmake_minimum_required(VERSION 3.6)


set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

project(Design_patterns_in_modern_cpp_cmake)

add_subdirectory(thirdparty/googletest)
add_subdirectory(src)
