#include "Kinematics/Segment2D.hpp"
#include "Kinematics/Segments.hpp"
#include "geometry/Ball.hpp"
#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

int main () {

    // Setting up Canvas
    Canvas canvas("Kinematics", {{"aa", 4}, {"vsync", true}});
    GLRenderer renderer(canvas.size());
    canvas.setSize({1500, 1500});

    // Setting up Camera
    auto camera = PerspectiveCamera::create();
    camera->position.z = 40;

    // Setting up scene
    auto scene = Scene::create();

    // Setting up controls, will delete later
    OrbitControls controls{*camera, canvas};
    controls.enableRotate = false;

    // Controls for target
    Vector2 target{};
    ImguiFunctionalContext ui(canvas.windowPtr(), [&] {
        ImGui::SetNextWindowPos({0, 0}, 0, {0, 0});
        ImGui::SetNextWindowSize({230, 0}, 0);
        ImGui::Begin("Demo");
        ImGui::SliderFloat("x Position", &target.x, -20, 20.f);
        ImGui::SliderFloat("y Position", &target.y, -20, 20.f);
        controls.enabled = !ImGui::IsWindowHovered();
        ImGui::End();
    });

    // Creating a ball that follows the target
    Ball ball(Color::green);
    auto group = Group::create();
    group->add(ball.getBall());
    scene->add(group);

    // Creating segments
    Segment2D segment1({0, 0}, 3, Color::red);
    Segment2D segment2(segment1, 3, Color::blue);
    Segment2D segment3(segment2, 3, Color::green);

    // Creating a list of segments
    Segments segments;
    segments.add(segment1);
    segments.add(segment2);
    segments.add(segment3);

    // Adding each segment to scene, will change
    for ( auto & segment : segments.getSegments()) {
        scene->add(segment.getLine());
    }

    // Adding everything to canvas
    canvas.animate([&] {
        // CCDSolver for segments
        segments.CCDSolver(target);

        renderer.render(*scene, *camera);
        ui.render();
        group->position = {target.x, target.y, 0};
    });
}
