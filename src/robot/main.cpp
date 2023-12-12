#include "scene/TargetPoint.hpp"
#include "scene/RobotScene.hpp"
#include "scene/Controls.hpp"
#include "kinematics/RobotArm.hpp"
#include "kinematics/CCDSolver.hpp"

using namespace threepp;

int main () {

    // Setting up Canvas
    Canvas canvas("Kinematics", {{"aa", 4}, {"vsync", true}});
    canvas.setSize({1000, 1000});
    GLRenderer renderer(canvas.size());
    //renderer.shadowMap().enabled = true; // Does not render properly on built in screen on mac. Comment out if problems arise

    // Creating scene
    auto scene = std::make_shared<RobotScene>(40);
    auto robotArm = std::make_shared<RobotArm>();

    canvas.onWindowResize([&](WindowSize size) {
        scene->camera().aspect = size.aspect();
        scene->camera().updateProjectionMatrix();
        renderer.setSize(size);
    });

    // Controls
    OrbitControls orbitControls(scene->camera(), canvas);
    Controls controls(canvas, orbitControls, 10);
    CCDSolver ccdSolver(*robotArm);
    TargetPoint targetPoint(1);

    scene->add(robotArm);
    scene->add(targetPoint.get());
    // Adding everything to canvas
    canvas.animate([&] {
        targetPoint.move(controls.getTarget());

        robotArm->updateNumSegments(controls.numSegments());
        robotArm->updateSize(controls.getSize(), controls.getLength());

        ccdSolver.solve(controls.getTarget());

        renderer.render(*scene, scene->camera());
        controls.ui()->render();
    });
}