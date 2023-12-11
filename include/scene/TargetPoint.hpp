
#ifndef ROBOTARM_TARGETPOINT_HPP
#define ROBOTARM_TARGETPOINT_HPP

#include "threepp/threepp.hpp"

using namespace threepp;


// For creating a ball that will follow the targetPoint for the robotArm
class TargetPoint {
public:
    // Constructor: Initializes and creates a sphere given a size
    TargetPoint(float size = 1);

    // Updates its position given a Vector3
    void move(Vector3& target);

    // Returns the mesh
    std::shared_ptr<Mesh>& get();
private:
    std::shared_ptr<Mesh> targetPoint_;
};

#endif //ROBOTARM_TARGETPOINT_HPP
