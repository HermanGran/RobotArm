
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
    Vector3 calculateEndPoint2D(int segment);
    Vector3 calculateEndPoint3D(int segment);

    // Updates the positions when iterating through in CCDSolver
    void updateSegmentPositions2D(int segment);
    void updateSegmentPositions3D(int segment);

    // Cyclic Coordinates Descent algorithm for moving the robotArm to a target point
    void CCDSolver2D(const Vector3 &target);
    void CCDSolver3D(const Vector3 &target);

private:

    std::vector<std::shared_ptr<Mesh>> segments_;
    std::shared_ptr<BoxGeometry> segmentGeometry_;
    std::shared_ptr<MeshLambertMaterial> segmentMaterial_;

    std::shared_ptr<SphereGeometry> jointGeometry_;
    std::shared_ptr<MeshLambertMaterial> jointMaterial_;
    std::vector<std::shared_ptr<Mesh>> joints_;

    std::vector<float> angles_;
};

#endif //MAPPEEKSAMEN_ROBOTARM_HPP
