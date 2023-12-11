
#include <catch2/catch_test_macros.hpp>

#include "threepp/threepp.hpp"
#include "kinematics/RobotArm.hpp"

using namespace threepp;

TEST_CASE("test numSegments") {
    RobotArm robotArm(2, 4);

    int numSegments4 = 4;
    int numSegments2 = 2;

    robotArm.updateNumSegments(numSegments4);
    CHECK(numSegments4 == robotArm.getSegments().size());

    robotArm.updateNumSegments(numSegments2);
    CHECK(numSegments2 == robotArm.getSegments().size());
}

TEST_CASE("Update with negative numbers throws exception") {
    RobotArm robotArm(2, 4);
    int negNumSegments = -1;

    REQUIRE_THROWS_AS(robotArm.updateNumSegments(negNumSegments), std::invalid_argument);
}

TEST_CASE("") {
    RobotArm robotArm(2, 4);
}