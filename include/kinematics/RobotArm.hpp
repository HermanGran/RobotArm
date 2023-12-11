
#ifndef MAPPEEKSAMEN_ROBOTARM_HPP
#define MAPPEEKSAMEN_ROBOTARM_HPP

#include "threepp/threepp.hpp"
#include <vector>

using namespace threepp;

// RobotArm manages the segments of the robotic arm, including the CCDSolver
class RobotArm: public Group {
public:
    // Constructor: Initializes the arm
    explicit RobotArm(float size, float length);

    // Updates the number of segments in the RobotArm
    void updateNumSegments(int numSegments);

    // Updates the positions when iterating through in CCDSolver
    void updateSegmentPositions(int segment);

    // Returns list of segments
    const std::vector<std::shared_ptr<Mesh>>& getSegments();

    // Calculates end points given the position
    Vector3 calculateEndPoint(int segment);
    Vector3 getEndEffector();

    // Cyclic Coordinates Descent algorithm for moving the robotArm to a target point
    void CCDSolver(const Vector3 &target);

private:

    std::vector<std::shared_ptr<Mesh>> segments_;
    std::shared_ptr<BoxGeometry> segmentGeometry_;
    std::shared_ptr<MeshLambertMaterial> segmentMaterial_;

    std::vector<std::shared_ptr<Mesh>> joints_;
    std::shared_ptr<SphereGeometry> jointGeometry_;
    std::shared_ptr<MeshLambertMaterial> jointMaterial_;

    float length_;
};

#endif //MAPPEEKSAMEN_ROBOTARM_HPP
