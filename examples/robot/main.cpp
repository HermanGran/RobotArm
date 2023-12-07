#include "geometry/Ball.hpp"
#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"
#include "scene/RobotScene.hpp"
#include "geometry/RobotArm.hpp"

using namespace threepp;

int main () {

    // Setting up Canvas
    Canvas canvas("Kinematics", {{"aa", 4}, {"vsync", true}});
    canvas.setSize({1000, 1000});
    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::aliceblue);

    // Creating scene and init
    auto scene = std::make_shared<RobotScene>(40);

    // Sliders for controlling target point and number of segments
    int numSegments = 1;
    Vector3 target{0, 0, 0};
    ImguiFunctionalContext ui(canvas.windowPtr(), [&] {
        ImGui::SetNextWindowPos({0, 0}, 0, {0, 0});
        ImGui::SetNextWindowSize({230, 0}, 0);
        ImGui::Begin("Robot Arm");
        ImGui::SliderFloat("x Position", &target.x, -20, 20.f);
        ImGui::SliderFloat("y Position", &target.y, -20, 20.f);
        ImGui::Text("Segments: %d", numSegments);
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
    auto group = Group::create();
    group->add(ball.getBall());
    scene->add(group);

    auto segmentGeometry = BoxGeometry::create(5, 1, 1);
    segmentGeometry->translate(2, 0, 0);

    // Create material for segment
    auto segmentMaterial = MeshBasicMaterial::create();
    segmentMaterial->color = Color::red;

    auto group1 = std::make_shared<RobotArm>(segmentGeometry, segmentMaterial);

    scene->add(group1);
    // Adding everything to canvas
    canvas.animate([&] {
        renderer.render(*scene, scene->camera());
        ui.render();
        group1->updateNumSegments(numSegments);
        group1->CCDSolver(target);
        group->position = target;
    });
}