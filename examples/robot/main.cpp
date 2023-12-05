#include "Kinematics/Segment2D.hpp"
#include "Kinematics/Segments.hpp"
#include "geometry/Ball.hpp"
#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"
#include "Kinematics/CCDSolver.hpp"
#include "RobotScene.hpp"
#include <iostream>

using namespace threepp;

std::shared_ptr<Group> addJoint(std::shared_ptr<Object3D> &base, const Vector3 &position, const Vector3 &size, const Vector3 &graphicsOffset);
void ccdSolver (std::vector<Group> &segments, const Vector3 &target);

int main () {

    // Setting up Canvas
    Canvas canvas("Kinematics", {{"aa", 4}, {"vsync", true}});
    canvas.setSize({1200, 1200});
    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::aliceblue);

    int numSegments = 1;
    Vector2 target{};
    ImguiFunctionalContext ui(canvas.windowPtr(), [&] {
        ImGui::SetNextWindowPos({0, 0}, 0, {0, 0});
        ImGui::SetNextWindowSize({230, 0}, 0);
        ImGui::Begin("Demo");
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

    //auto scene = std::make_shared<RobotScene>(40, Vector3{0, 0, 0});

    auto scene = Scene::create();

    auto camera = PerspectiveCamera::create();
    camera->position.z = 40;

    /*
    auto geometry = CylinderGeometry::create(1, 1, 5);
    auto material = MeshBasicMaterial::create();
    auto Mesh = Mesh::create(geometry, material);
    material->color.copy(Color::red);
    scene->add(Mesh);
    */

    Segments segments;

    Segment2D segment1({0, 0}, 3, Color::green);
    Segment2D segment2(segment1, 3, Color::red);
    Segment2D segment3(segment2, 3, Color::blue);
    Segment2D segment4(segment3, 3, Color::yellow);

    segments.add(segment1);
    segments.add(segment2);
    segments.add(segment3);
    segments.add(segment4);

    scene->add(segment1.getLine());
    scene->add(segment2.getLine());
    scene->add(segment3.getLine());
    scene->add(segment4.getLine());

    // Creating a ball that follows the target
    Ball ball(Color::green);
    auto group = Group::create();
    group->add(ball.getBall());
    scene->add(group);

    CCDSolver solver(10, 0.0001);


    Vector3 target3D{target.x, target.y, 0};
    // Adding everything to canvas
    canvas.animate([&] {

        //solver.solve(segments.getSegments(), target);
        Vector3 test;

        float angle = atan2(target.y, target.x);

        segment2.rotateAroundStartPoint(angle);
        segment3.update(segment2);

        float angle1 = segment2.getAngle() + segment3.getAngle();

        //segment3.rotateAroundStartPoint(segment2.getAngle());
        //segment3.rotateAroundStartPoint(angle);


        std::cout << segment3.getStartPos() << std::endl;
        //segment3.setStartPos({target.x, target.y});



        //segment3.getLine()->updateMatrixWorld();
        renderer.render(*scene, *camera);
        ui.render();

        group->position = {target.x, target.y, 0};
    });
}

std::shared_ptr<Group> addJoint(std::shared_ptr<Object3D> &base, const Vector3 &position, const Vector3 &size, const Vector3 &graphicsOffset) {
    auto joint = Group::create();
    base->add(joint);
    joint->position.set(position.x, position.y, position.z);

    auto boxGeometry = BoxGeometry::create(size.x, size.y, size.z);
    auto material = MeshBasicMaterial::create();
    auto box = Mesh::create(boxGeometry, material);
    box->position.set(graphicsOffset.x, graphicsOffset.y, graphicsOffset.z);

    joint->add(box);

    return joint;
}

void ccdSolver (std::vector<Group> &IKJoints, const Vector3 &target) {
    Vector3 toolTipPosition;
    Matrix4 invJointMatrix;


    for (int i = IKJoints.size() - 1; i >= 0; i--) {
        IKJoints[i].updateMatrixWorld(true);
        IKJoints.end()->getWorldPosition(toolTipPosition);


    }
}