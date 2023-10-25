add_library(
        Robot
        Segment.cpp
)

target_link_libraries(Robot PUBLIC threepp::threepp imgui::imgui)
target_include_directories(Robot PUBLIC "${CMAKE_SOURCE_DIR}/include")


