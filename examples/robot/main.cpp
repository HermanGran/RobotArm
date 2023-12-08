#include "geometry/Ball.hpp"
#include "threepp/extras/imgui/ImguiContext.hpp"
#include "scene/RobotScene.hpp"
#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace threepp;

int main () {

    // Setting up Canvas
    Canvas canvas("Kinematics", {{"aa", 4}, {"vsync", true}});
    canvas.setSize({1000, 1000});
    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::aliceblue);

    // Creating scene
    auto scene = std::make_shared<RobotScene>(40);

    OrbitControls controls(scene->camera(), canvas);

    // Sliders for controlling target point and number of segments
    int numSegments = 3;
    Vector3 target{0, 0, 0};
    ImguiFunctionalContext ui(canvas.windowPtr(), [&] {
        ImGui::SetNextWindowPos({0, 0}, 0, {0, 0});
        ImGui::SetNextWindowSize({230, 0}, 0);
        ImGui::Begin("Robot Arm");
        ImGui::SliderFloat("x Position", &target.x, -20, 20.f);
        ImGui::SliderFloat("y Position", &target.y, -20, 20.f);
        ImGui::SliderFloat("z position", &target.z, -20, 20.f);
        ImGui::Text("Segments: %d", numSegments);
        controls.enabled = !ImGui::IsWindowHovered();

        if (ImGui::Button("-") && numSegments > 1) {
            numSegments -= 1;
        }

        ImGui::SameLine();
        if (ImGui::Button("+") && numSegments < 6){
            numSegments += 1;
        }
        ImGui::End();
    });

    // Creating a ball that follows the target
    Ball ball(Color::green);
    scene->add(ball.getBall());

    // Creating the robot arm
    auto robotArm = std::make_shared<RobotArm>();
    scene->add(robotArm);

    // Adding everything to canvas
    canvas.animate([&] {
        renderer.render(*scene, scene->camera());
        ui.render();

        robotArm->updateNumSegments(numSegments);
        robotArm->CCDSolverQ(target);

        ball.getBall()->position = target;
    });
}