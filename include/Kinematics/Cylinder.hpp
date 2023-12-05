#ifndef MAPPEEKSAMEN_CYLINDER_HPP
#define MAPPEEKSAMEN_CYLINDER_HPP

#include "threepp/threepp.hpp"
#include <vector>
#include <algorithm>

using namespace threepp;

class Cylinder {
public:
    Cylinder(Vector3& startPos, int len);

    const std::vector<Vector3> &positions() const {
        return positions_;
    }

private:
    std::vector<Vector3> positions_;
    int len_;
    Vector3 startPos_;
};

#endif //MAPPEEKSAMEN_CYLINDER_HPP
