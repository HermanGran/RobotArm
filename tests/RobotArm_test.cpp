
#include <catch2/catch_test_macros.hpp>

#include "kinematics/RobotArm.hpp"

using namespace threepp;

TEST_CASE("Update number of segments") {
    RobotArm robotArm;

    int numSegments4 = 4;
    int numSegments2 = 2;

    robotArm.updateNumSegments(numSegments4);
    CHECK(numSegments4 == robotArm.getSegments().size());

    robotArm.updateNumSegments(numSegments2);
    CHECK(numSegments2 == robotArm.getSegments().size());
}

TEST_CASE("Update with negative numbers throws exception") {
    RobotArm robotArm;
    int negNumSegments = -1;

    REQUIRE_THROWS_AS(robotArm.updateNumSegments(negNumSegments), std::invalid_argument);
}

TEST_CASE("Update corresponding sizes for lists") {
    RobotArm robotArm;
    robotArm.updateNumSegments(6);

    CHECK(robotArm.getSegments().size() == robotArm.getLengths().size());
    CHECK(robotArm.getSegments().size() == robotArm.getJoints().size());
}