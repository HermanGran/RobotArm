
#ifndef ROBOTARM_CCDSOLVER_HPP
#define ROBOTARM_CCDSOLVER_HPP

#include "threepp/threepp.hpp"
#include "kinematics/IRobotArm.hpp"
#include <vector>

using namespace threepp;

class CCDSolver {
public:
    // Constructor: Initializes with an abstract class to make it usable for other multiple classes
    //              that has the same functions
    CCDSolver(IRobotArm& robotArm);

    // The CCDSolver
    void solve(Vector3& target);

    // Update function for keeping it aligned
    void updateSegments(int segment);

    // Functions for finding positions, returns Vector3
    Vector3 calculateEndPos(int segment);
    Vector3 getEndEffector();

private:
    IRobotArm& robotArm;
};


#endif //ROBOTARM_CCDSOLVER_HPP
