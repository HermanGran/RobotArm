#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"
#include "Segment.hpp"
#include <iostream>

using namespace threepp;

int main () {
    Canvas canvas("ROBOTICS", {{"aa", 4}});
    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::aliceblue);

    auto scene = Scene::create();

    Segment segment1({0, 0, 0}, 10, 0, Color::blue);
    Segment segment2(segment1, 5, 45, Color::red);

    segment1.setChild(&segment2);
    scene->add(segment1.getline());
    scene->add(segment2.getline());

    auto camera = PerspectiveCamera::create();
    camera->position.z = 5;

    OrbitControls controls{*camera, canvas};
    controls.enableRotate = false;
    controls.enableZoom = true;

    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.aspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    //Copied from threepp Instancing example
    Vector2 mouse{-Infinity<float>, -Infinity<float>};
    MouseMoveListener l([&](auto& pos) {
        auto size = canvas.size();
        mouse.x = (pos.x / static_cast<float>(size.width)) * 2 - 1;
        mouse.y = -(pos.y / static_cast<float>(size.height)) * 2 + 1;
    });
    canvas.addMouseListener(&l);

    Vector3 mousePos{mouse.x, mouse.y, 0};

    //If else statement to update the position of the lines using rotation



    canvas.animate([&] {

        mousePos.set(mouse.x, mouse.y, 0);
        segment1.pointAt(mousePos);

        renderer.render(*scene, *camera);
    });
}
