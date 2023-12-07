
#ifndef MAPPEEKSAMEN_ROBOTARM_HPP
#define MAPPEEKSAMEN_ROBOTARM_HPP

#include "scene/RobotScene.hpp"
#include <vector>

using namespace threepp;

class RobotArm: public Group {
public:

    explicit RobotArm();

    void updateNumSegments(int numSegments);
    void setAngle(int segment, float angle);
    void updateSegmentPositions(int segment);
    void CCDSolver(const Vector3 &target, float maxAngleChange = 0.05f);

private:
    std::shared_ptr<BoxGeometry> segmentGeometry_;
    std::shared_ptr<MeshBasicMaterial> segmentMaterial_;

    std::vector<float> angles_;
    std::vector<std::shared_ptr<Mesh>> segments_;
};

#endif //MAPPEEKSAMEN_ROBOTARM_HPP
