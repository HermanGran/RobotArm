
#ifndef ROBOTARM_IROBOTARM_HPP
#define ROBOTARM_IROBOTARM_HPP

#include "threepp/threepp.hpp"
#include <vector>

using namespace threepp;

// abstract class for CCDSolver, avoiding high cohesion with RobotArm
class IRobotArm {
public:
    virtual ~IRobotArm() = default;

    // Getter functions
    virtual const std::vector<std::shared_ptr<Mesh>>& getSegments() = 0;
    virtual const std::vector<std::shared_ptr<Mesh>>& getJoints() = 0;
    virtual const std::vector<float>& getLengths() = 0;

};

#endif //ROBOTARM_IROBOTARM_HPP
