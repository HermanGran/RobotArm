
#ifndef ROBOTARM_TARGETPOINT_HPP
#define ROBOTARM_TARGETPOINT_HPP

#include "threepp/threepp.hpp"

using namespace threepp;

/**
 * TargetPoint class for creating a 3D object to visibly see target point
 */
class TargetPoint {
public:
    /**
     * Constructor for TargetPoint
     * @param size The size of target point
     */
    TargetPoint(float size = 1);

    /**
     * Updates the position of target point
     * @param target The position wanted
     */
    void move(Vector3& target);

    /**
     * Gets the Mesh of 3D ball for rendering
     * @return Reference pointer of type Mesh
     */
    std::shared_ptr<Mesh>& get();
private:
    std::shared_ptr<Mesh> targetPoint_;
};

#endif //ROBOTARM_TARGETPOINT_HPP