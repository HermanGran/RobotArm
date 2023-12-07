#ifndef MAPPEEKSAMEN_BOX_HPP
#define MAPPEEKSAMEN_BOX_HPP

#include "threepp/threepp.hpp"

using namespace threepp;

// Class for creating a sphere/ball
// In this case it is used to visually see the target point
class Ball {
public:

    // Constructor: Initializes the ball with a color
    Ball(const Color& color);

    // For creating the ball
    void createBall();

    // Returns the Mesh
    std::shared_ptr<Mesh> getBall();

private:
    Color color_;
    std::shared_ptr<Mesh> ball_;
    std::shared_ptr<SphereGeometry> geometry_;
    std::shared_ptr<MeshBasicMaterial> material_;
};

#endif //MAPPEEKSAMEN_BOX_HPP
