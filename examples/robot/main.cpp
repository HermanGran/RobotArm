#include "geometry/Ball.hpp"
#include "threepp/extras/imgui/ImguiContext.hpp"
#include "scene/RobotScene.hpp"
#include "scene/Controls.hpp"

using namespace threepp;

int main () {

    // Setting up Canvas
    Canvas canvas("Kinematics", {{"aa", 4}, {"vsync", true}});
    canvas.setSize({1000, 1000});
    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::aliceblue);

    // Creating scene
    auto scene = std::make_shared<RobotScene>(40);
    auto robotArm = std::make_shared<RobotArm>();
    scene->add(robotArm);

    //Controls
    OrbitControls orbitControls(scene->camera(), canvas);
    Controls controls(canvas, orbitControls);

    // Creating a ball that follows the target
    Ball ball(Color::green);
    scene->add(ball.getBall());

    // Adding everything to canvas
    canvas.animate([&] {
        renderer.render(*scene, scene->camera());
        controls.ui()->render();

        robotArm->updateNumSegments(controls.numSegments());
        robotArm->CCDSolverQ(controls.target());

        ball.getBall()->position = controls.target();
    });
}