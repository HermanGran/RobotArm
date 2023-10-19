add_library(Robot Segment.cpp)
target_include_directories(Robot PUBLIC "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(Robot PUBLIC threepp::threepp imgui::imgui)