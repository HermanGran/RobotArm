add_executable(Example_ Example.cpp)
add_executable(Kinematics Kinematics.cpp)

target_link_libraries(Example_ PUBLIC threepp::threepp imgui::imgui)
target_link_libraries(Kinematics PUBLIC Robot threepp::threepp imgui::imgui)