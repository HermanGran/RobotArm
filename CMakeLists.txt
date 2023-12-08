cmake_minimum_required(VERSION 3.15)
project(RobotArm)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_subdirectory(src)
add_subdirectory(examples)