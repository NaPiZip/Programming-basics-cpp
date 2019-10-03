cmake_minimum_required(VERSION 3.6)


set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

project(A_tour_of_cpp)

add_subdirectory(thirdparty/googletest)
add_subdirectory(src)
