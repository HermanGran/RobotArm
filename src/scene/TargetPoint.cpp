#include "scene/TargetPoint.hpp"

// Constructor: Initializes and creates a sphere given a size
TargetPoint::TargetPoint(float size) {
    auto geometry = SphereGeometry::create(size);
    auto material = MeshLambertMaterial::create();
    material->color = Color::green;
    targetPoint_ = Mesh::create(geometry, material);
    targetPoint_->receiveShadow = true;
    targetPoint_->castShadow = true;
}

// Moves the ball to the target
void TargetPoint::move(threepp::Vector3 &target) {
    targetPoint_->position = target;
}

// Returns the sphere
std::shared_ptr<Mesh>& TargetPoint::get() {
    return targetPoint_;
}