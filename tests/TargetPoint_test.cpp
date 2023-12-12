
#include <catch2/catch_test_macros.hpp>

#include "scene/TargetPoint.hpp"

TEST_CASE("Move target point") {
    TargetPoint targetPoint(1);

    Vector3 pos1(1, 1, 1);
    targetPoint.move(pos1);
    CHECK(targetPoint.get()->position == pos1);

    Vector3 pos2(50, 23.6, 9.53);
    targetPoint.move(pos2);
    CHECK(targetPoint.get()->position == pos2);
}

