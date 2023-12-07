
#ifndef MAPPEEKSAMEN_ROBOTARM_HPP
#define MAPPEEKSAMEN_ROBOTARM_HPP

#include "scene/RobotScene.hpp"
#include <vector>

using namespace threepp;

// RobotArm manages the segments of the robotic arm, including the CCDSolver
class RobotArm: public Group {
public:
    // Constructor: Initializes the arm
    explicit RobotArm();

    // Updates the angles of each segment
    void setAngle(int segment, float angle);

    // Updates the number of segments in the RobotArm
    void updateNumSegments(int numSegments);

    // Calculates end points given the position
    Vector3 calculateEndPoint(int segment);

    // Updates the positions when iterating through in CCDSolver
    void updateSegmentPositions(int segment);

    // Cyclic Coordinates Descent algorithm for moving the robotArm to a target point
    void CCDSolver(const Vector3 &target, float maxAngleChange = 0.05f);

private:
    std::shared_ptr<BoxGeometry> segmentGeometry_;
    std::shared_ptr<MeshBasicMaterial> segmentMaterial_;

    std::vector<float> angles_;
    std::vector<std::shared_ptr<Mesh>> segments_;
};

#endif //MAPPEEKSAMEN_ROBOTARM_HPP
