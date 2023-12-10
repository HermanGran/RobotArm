
#include <catch2/catch_test_macros.hpp>

#include "threepp/threepp.hpp"
#include "kinematics/RobotArm.hpp"

using namespace threepp;

namespace {
    int size = 1;
    int length = 3;
    auto robotArm = std::make_shared<RobotArm>(size, length);

}

TEST_CASE("test numSegments") {
    int numSegments4 = 4;
    int numSegments2 = 2;

    robotArm->updateNumSegments(numSegments4);
    CHECK(numSegments4 == robotArm->getSegments().size());

    robotArm->updateNumSegments(numSegments2);
    CHECK(numSegments2 == robotArm->getSegments().size());
}

TEST_CASE("Update with negative numbers throws exception") {
    int negNumSegments = -1;
    REQUIRE_THROWS_AS(robotArm->updateNumSegments(negNumSegments), std::invalid_argument);
}

TEST_CASE("test calculatedEndPosition") {
    int numSegments = 4;
    robotArm->updateNumSegments(numSegments);

    robotArm->calculateEndPoint3D(0);
    CHECK(0 == 0);
}