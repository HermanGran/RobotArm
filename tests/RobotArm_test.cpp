
#include <catch2/catch_test_macros.hpp>

#include "kinematics/RobotArm.hpp"

using namespace threepp;

TEST_CASE("test numSegments") {
    RobotArm robotArm(2, 4);

    int numSegments4 = 4;
    int numSegments2 = 2;

    robotArm.updateNumSegments(numSegments4, 2, 4);
    CHECK(numSegments4 == robotArm.getSegments().size());

    robotArm.updateNumSegments(numSegments2, 2, 4);
    CHECK(numSegments2 == robotArm.getSegments().size());
}

TEST_CASE("Update with negative numbers throws exception") {
    RobotArm robotArm(2, 4);
    int negNumSegments = -1;

    REQUIRE_THROWS_AS(robotArm.updateNumSegments(negNumSegments, 2, 4), std::invalid_argument);
}

TEST_CASE("Correct corresponding sizes for lists") {
    RobotArm robotArm(2, 4);
    robotArm.updateNumSegments(6, 2, 4);

    CHECK(robotArm.getSegments().size() == robotArm.getLengths().size());
    CHECK(robotArm.getSegments().size() == robotArm.getJoints().size());
}