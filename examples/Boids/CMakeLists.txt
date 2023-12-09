add_executable(Boids main.cpp)

target_link_libraries(Boids PUBLIC Kinematics)
target_include_directories(Boids PUBLIC "${CMAKE_SOURCE_DIR}/include")