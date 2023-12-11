#include "scene/RobotScene.hpp"
#include "scene/Controls.hpp"
#include "kinematics/RobotArm.hpp"
#include <iostream>

using namespace threepp;

int main () {

    // Setting up Canvas
    Canvas canvas("Kinematics", {{"aa", 4}, {"vsync", true}});
    canvas.setSize({1000, 1000});
    GLRenderer renderer(canvas.size());
    renderer.shadowMap().enabled = true;

    // Creating scene
    auto scene = std::make_shared<RobotScene>(20);
    auto robotArm = std::make_shared<RobotArm>(0.7, 3);
    scene->add(robotArm);

    canvas.onWindowResize([&](WindowSize size) {
        scene->camera().aspect = size.aspect();
        scene->camera().updateProjectionMatrix();
        renderer.setSize(size);
    });

    // Controls
    OrbitControls orbitControls(scene->camera(), canvas);
    Controls controls(canvas, orbitControls);
    scene->add(controls.target());

    // Adding everything to canvas
    canvas.animate([&] {
        robotArm->updateNumSegments(controls.numSegments());
        robotArm->CCDSolver(controls.target()->position);

        renderer.render(*scene, scene->camera());
        controls.ui()->render();
    });
}