
add_executable(Robot main.cpp)

target_link_libraries(Robot PUBLIC Kinematics)

target_include_directories(Robot PUBLIC "${CMAKE_SOURCE_DIR}/include")