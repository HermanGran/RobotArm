cmake_minimum_required(VERSION 3.15)
project(MappeEksamen)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(Main main.cpp)

target_link_libraries(Main PUBLIC Robot)

target_link_libraries(Main PRIVATE threepp::threepp imgui::imgui)
target_include_directories(Main PUBLIC "${CMAKE_SOURCE_DIR}/include")


add_subdirectory(src)



