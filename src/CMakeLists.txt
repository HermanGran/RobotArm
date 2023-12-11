set(SOURCE_FILES
        kinematics/CCDSolver.cpp
        kinematics/RobotArm.cpp

        scene/RobotScene.cpp
        scene/Controls.cpp
    )

add_library(Kinematics STATIC "${SOURCE_FILES}")
target_link_libraries(Kinematics PUBLIC threepp::threepp imgui::imgui)
target_include_directories(Kinematics PUBLIC "${CMAKE_SOURCE_DIR}/include")

add_subdirectory(robot)
