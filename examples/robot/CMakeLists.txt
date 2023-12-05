
add_executable(Robot main.cpp)
target_link_libraries(Robot PUBLIC Kinematics threepp::threepp imgui::imgui)