cmake_minimum_required(VERSION 3.15)
project(MappeEksamen)

set(CMAKE_CXX_STANDARD 20)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(Robot main.cpp)
target_link_libraries(Robot PRIVATE threepp::threepp imgui::imgui)
