add_subdirectory(Example)

set(SOURCE_FILES
        Robotics/Segment2D.cpp
        Robotics/Segment3D.cpp
        Robotics/CCDSolver.cpp
        Math/Math.cpp
)

add_library(Robot STATIC "${SOURCE_FILES}")

target_link_libraries(Robot PUBLIC threepp::threepp imgui::imgui)
target_include_directories(Robot PUBLIC "${CMAKE_SOURCE_DIR}/include")
