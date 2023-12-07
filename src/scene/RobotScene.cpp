#include "scene/RobotScene.hpp"

// Constructor
RobotScene::RobotScene(int size) {

    // Creating a box around center
    auto grid = GridHelper::create(size, 1, 0x444444, 0x444444);
    grid->position.set(0, 0, 0);
    grid->rotation.x = math::PI / 2;
    add(grid);

    // Creating the camera
    camera_ = PerspectiveCamera::create();
    camera_->position.z = size;
    add(camera_);

}
// Returns a pointer to the camera
PerspectiveCamera& RobotScene::camera() const  {
    return *camera_;
}

