set(SOURCE_FILES
        geometry/Ball.cpp
        geometry/RobotArm.cpp
        geometry/Segment.cpp

        kinematics/CCDSolver.cpp

        scene/RobotScene.cpp
    )

add_library(Kinematics STATIC "${SOURCE_FILES}")

target_link_libraries(Kinematics PUBLIC threepp::threepp imgui::imgui)

target_include_directories(Kinematics PUBLIC "${CMAKE_SOURCE_DIR}/include")

