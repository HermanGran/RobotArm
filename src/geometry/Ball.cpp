#include "geometry/Ball.hpp"

// Constructor: Initializes the ball with a color
Ball::Ball(const Color &color)
: color_(color) {
    createBall();
}

// Creating the ball
void Ball::createBall() {
    geometry_ = SphereGeometry::create();
    material_ = MeshBasicMaterial::create();
    material_->color.copy(color_);
    ball_ = Mesh::create(geometry_, material_);
}

// Returns the Mesh
std::shared_ptr<Mesh> Ball::getBall() {
    return ball_;
}