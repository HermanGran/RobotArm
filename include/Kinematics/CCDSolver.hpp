#ifndef MAPPEEKSAMEN_CCDSOLVER_HPP
#define MAPPEEKSAMEN_CCDSOLVER_HPP

#include "threepp/threepp.hpp"
#include "Kinematics/Segment2D.hpp"
#include "Kinematics/Segments.hpp"
#include <vector>

class CCDSolver {
public:
    CCDSolver(int maxIter, float threshold);

    void solve(std::vector<Segment2D>& segments, const Vector2& target);
    void solve(std::vector<Group> &segments, const Vector3 &target);

private:
    int maxIter_;
    float threshold_;

};

#endif //MAPPEEKSAMEN_CCDSOLVER_HPP
