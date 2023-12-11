
#ifndef ROBOTARM_CCDSOLVER_HPP
#define ROBOTARM_CCDSOLVER_HPP

#include "threepp/threepp.hpp"
#include "kinematics/IRobotArm.hpp"
#include <vector>

using namespace threepp;

/**
 * CCDSolver class for kinematics chains
 */

class CCDSolver {
public:
    /**
     * Constructor: Initializes CCDSolver
     * @Param robotArm Abstract class kinematics chain
     */
    explicit CCDSolver(IRobotArm& robotArm);

    /**
     * CCD Solver using cross product for finding the axis of rotation in 3D space.
     *  @Param target TargetPoint for CCD algorithm
    */
    void solve(Vector3& target);

    /**
     * Updates the position and orientation for each segment
     * Typically called within a loop
     * @Param segment Index from loop iteration
     */
    void updateSegments(int segment);

    /**
     * Calculate endpoint for the segment given current position and orientation
     * Typically called within a loop
     * @Param segment Index from loop iteration
     * @return The calculated end position as a Vector3
     */
    Vector3 calculateEndPos(int segment);

    /**
     * Gets end effector position
     * @return The position of the end effector
     */
    Vector3 getEndEffector();

private:
    IRobotArm& robotArm;
};

#endif //ROBOTARM_CCDSOLVER_HPP
