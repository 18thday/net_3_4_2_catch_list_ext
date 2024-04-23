cmake_minimum_required(VERSION 3.26)
project(net_3_4_2_catch_list_ext)

set(CMAKE_CXX_STANDARD 17)

find_package(Catch2 3 REQUIRED)

add_executable(net_3_4_2_catch_list_ext main.cpp list.h)
target_link_libraries(net_3_4_2_catch_list_ext PRIVATE Catch2::Catch2)
