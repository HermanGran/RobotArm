#include "scene/RobotScene.hpp"
#include "scene/Controls.hpp"
#include "kinematics/RobotArm.hpp"
#include "kinematics/CCDSolver.hpp"
#include <iostream>

using namespace threepp;

int main () {

    // Setting up Canvas
    Canvas canvas("Kinematics", {{"aa", 4}, {"vsync", true}});
    canvas.setSize({1000, 1000});
    GLRenderer renderer(canvas.size());

    // Does not render properly on built in screen on mac. Comment out if so
    renderer.shadowMap().enabled = true;

    // Creating scene
    auto scene = std::make_shared<RobotScene>(20);
    auto robotArm = std::make_shared<RobotArm>(0.5, 4);

    canvas.onWindowResize([&](WindowSize size) {
        scene->camera().aspect = size.aspect();
        scene->camera().updateProjectionMatrix();
        renderer.setSize(size);
    });

    // Controls
    OrbitControls orbitControls(scene->camera(), canvas);
    Controls controls(canvas, orbitControls);
    CCDSolver ccdSolver(*robotArm);

    scene->add(controls.target());
    scene->add(robotArm);

    // Adding everything to canvas
    canvas.animate([&] {
        robotArm->updateNumSegments(controls.numSegments());
        ccdSolver.solve(controls.target()->position);

        renderer.render(*scene, scene->camera());
        controls.ui()->render();
    });
}