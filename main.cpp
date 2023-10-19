#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"
#include "Segment.hpp"
#include "ParentSegment.hpp"

using namespace threepp;

int main () {
    Canvas canvas("ROBOTICS", {{"aa", 4}});
    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::aliceblue);

    auto scene = Scene::create();

    Segment segment1({0, 0, 0}, 10, 45, Color::blue);
    ParentSegment segment2(segment1, 10, -45, Color::red);
    scene->add(segment1.getline());
    scene->add(segment2.getLine());

    auto camera = PerspectiveCamera::create();
    camera->position.z = 5;

    OrbitControls controls{*camera, canvas};
    controls.enableRotate = false;
    controls.enableZoom = true;


    Clock clock;
    float rotationSpeed = 1;
    canvas.animate([&] {
        auto dt = clock.getDelta();

        segment1.getline()->rotation.z += rotationSpeed * dt;

        renderer.render(*scene, *camera);
    });
}
