#include <iostream>
#include "Boids.hpp"

using namespace threepp;

// Started looking a little into boids for fun
int main() {
    // Setting up scene
    Canvas canvas("Boids", {{"aa", 4}, {"vsync", true}});
    canvas.setSize({1000, 1000});
    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::aliceblue);

    auto scene = std::make_shared<Boids>(10);

    OrbitControls controls(scene->camera(), canvas);

    Clock clock;
    canvas.animate([&] {
        float dt = clock.getDelta();

        scene->initBoids();
        scene->move(dt);
        renderer.render(*scene, scene->camera());
    });
}
