#include <iostream>
#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"
#include "Segment.hpp"

using namespace threepp;

int main () {
    Canvas canvas("ROBOTICS", {{"aa", 4}});
    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::aliceblue);

    auto scene = Scene::create();

    Segment segment1({0, 0, 0}, 10, 10, Color::blue);
    Segment segment2({0, 0, 0}, 5, 0, Color::red);
    scene->add(segment1.getline());
    scene->add(segment2.getline());

    auto camera = PerspectiveCamera::create();
    camera->position.z = 5;

    OrbitControls controls{*camera, canvas};
    controls.enableRotate = false;
    controls.enableZoom = true;

    canvas.animate([&] {
        renderer.render(*scene, *camera);
    });
}