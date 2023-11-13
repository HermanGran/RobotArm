set(SOURCE_FILES

        geometry/Ball.cpp

        Math/Math.cpp

        Robotics/Segment2D.cpp
        Robotics/Segment3D.cpp
        Robotics/Segments.cpp

)

add_library(Robot STATIC "${SOURCE_FILES}")

target_link_libraries(Robot PUBLIC threepp::threepp imgui::imgui)
target_include_directories(Robot PUBLIC "${CMAKE_SOURCE_DIR}/include")