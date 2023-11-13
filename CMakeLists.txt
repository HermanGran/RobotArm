cmake_minimum_required(VERSION 3.15)
project(MappeEksamen)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_subdirectory(src)
add_subdirectory(examples)

add_executable(mightDelete main.cpp)

target_link_libraries(mightDelete PUBLIC Robot)
target_link_libraries(mightDelete PRIVATE threepp::threepp imgui::imgui)
target_include_directories(mightDelete PUBLIC "${CMAKE_SOURCE_DIR}/include")