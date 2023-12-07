#include "geometry/Ball.hpp"

Ball::Ball(const Color &color)
: color_(color) {
    createSphere();
}

void Ball::createSphere() {
    geometry_ = CircleGeometry::create();
    material_ = MeshBasicMaterial::create();
    material_->color.copy(color_);
    ball_ = Mesh::create(geometry_, material_);
    ball_->position.copy(pos_);
}

std::shared_ptr<Mesh> Ball::getBall() {
    return ball_;
}