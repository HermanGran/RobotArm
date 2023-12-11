
#ifndef ROBOTARM_IROBOTARM_HPP
#define ROBOTARM_IROBOTARM_HPP

#include "threepp/threepp.hpp"
#include <vector>

using namespace threepp;

// Abstract class for achieving high cohesion and low coupling
class IRobotArm {
public:
    virtual ~IRobotArm() = default;

    virtual const std::vector<std::shared_ptr<Mesh>>& getSegments() = 0;
    virtual const std::vector<std::shared_ptr<Mesh>>& getJoints() = 0;
    virtual const std::vector<float>& getLengths() = 0;
    virtual const std::vector<float>& getSizes() = 0;
};

#endif //ROBOTARM_IROBOTARM_HPP
