set(SOURCE_FILES

        geometry/Ball.cpp

        Kinematics/CCDSolver.cpp
        Kinematics/Cylinder.cpp
        Kinematics/Segment2D.cpp
        Kinematics/Segment3D.cpp
        Kinematics/Segments.cpp

)

add_library(Kinematics STATIC "${SOURCE_FILES}")

target_link_libraries(Kinematics PUBLIC threepp::threepp imgui::imgui)

target_include_directories(Kinematics PUBLIC "${CMAKE_SOURCE_DIR}/include")