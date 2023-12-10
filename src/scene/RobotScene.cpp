#include "scene/RobotScene.hpp"
#include "threepp/materials/ShaderMaterial.hpp"
#include "threepp/objects/Sky.hpp"
#include "threepp/lights/LightShadow.hpp"


// Constructor
RobotScene::RobotScene(int size) {

    // Creating a box around center
    auto grid = GridHelper::create(size, 6, 0x444444, 0x444444);
    grid->position.set(0, 0, 0);
    add(grid);

    // Creating the camera and setting up angle of perspective
    camera_ = PerspectiveCamera::create();
    camera_->position.set(-40, 10, 40);
    camera_->lookAt(0, 0, 0);
    add(camera_);

    // For shadow
    auto light = SpotLight::create(0xbbbbbb);
    light->position.set(0, 200/5, 100/5);
    light->shadow->mapSize = Vector2(2048, 4096);
    light->castShadow = true;
    add(light);

    // Copied from threepp/examples/lights//directional.cpp line: 16-23
    auto sky = Sky::create();
    sky->scale.setScalar(1000);
    auto& skyUniforms = sky->material()->as<ShaderMaterial>()->uniforms;
    skyUniforms->at("turbidity").value<float>() = 10;
    skyUniforms->at("rayleigh").value<float>() = 1;
    skyUniforms->at("mieCoefficient").value<float>() = 0.005f;
    skyUniforms->at("mieDirectionalG").value<float>() = 0.8f;
    skyUniforms->at("sunPosition").value<Vector3>().set(0, 200, 100);
    add(sky);

    auto planeGeom = BoxGeometry::create(size, size, 1);
    auto planeMat = MeshLambertMaterial::create();
    planeMat->color = Color::lightgreen;
    auto plane = Mesh::create(planeGeom, planeMat);
    plane->rotateX(math::degToRad(-90));
    // To offset it below the grid to prevent clipping effect between the objects
    plane->position.y = -0.55;
    plane->receiveShadow = true;
    add(plane);

}
// Returns a pointer to the camera
PerspectiveCamera& RobotScene::camera() const  {
    return *camera_;
}

