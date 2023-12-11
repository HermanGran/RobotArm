
#ifndef MAPPEEKSAMEN_ROBOTARM_HPP
#define MAPPEEKSAMEN_ROBOTARM_HPP

#include "threepp/threepp.hpp"
#include "kinematics/IRobotArm.hpp"
#include <vector>

using namespace threepp;

// RobotArm manages the segments of the robotic arm, including the CCDSolver
class RobotArm: public IRobotArm, public Group {
public:
    // Constructor: Initializes the arm
    explicit RobotArm(float size, float length);

    // Updates the number of segments in the RobotArm
    void updateNumSegments(int numSegments);

    // Getter functions override IRobotArm abstract class
    const std::vector<std::shared_ptr<Mesh>>& getSegments() override;
    const std::vector<std::shared_ptr<Mesh>>& getJoints() override;
    const std::vector<float>& getLengths() override;
    const std::vector<float>& getSizes() override;

private:

    std::vector<std::shared_ptr<Mesh>> segments_;
    std::shared_ptr<BoxGeometry> segmentGeometry_;
    std::shared_ptr<MeshLambertMaterial> segmentMaterial_;

    std::vector<std::shared_ptr<Mesh>> joints_;
    std::shared_ptr<SphereGeometry> jointGeometry_;
    std::shared_ptr<MeshLambertMaterial> jointMaterial_;

    std::vector<float> lengths_;
    std::vector<float> sizes_;
};

#endif //MAPPEEKSAMEN_ROBOTARM_HPP
