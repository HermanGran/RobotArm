
#include "catch2/catch_test_macros.hpp"

#include "kinematics/CCDSolver.hpp"
#include "kinematics/RobotArm.hpp"

/*
 * with this one test it runs through all functions in CCD
 */
TEST_CASE("Check if CCDSolver finds target point") {
    RobotArm robotArm;
    robotArm.updateNumSegments(4);
    CCDSolver ccdSolver(robotArm);

    Vector3 targetPoint(4, 4, 4);
    ccdSolver.solve(targetPoint);
    CHECK((ccdSolver.getEndEffector() - targetPoint).length() <= 0.1f);
}