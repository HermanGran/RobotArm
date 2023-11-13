#ifndef MAPPEEKSAMEN_SEGMENTS_HPP
#define MAPPEEKSAMEN_SEGMENTS_HPP

#include "threepp/threepp.hpp"
#include "Kinematics/Segment2D.hpp"
#include "Kinematics/Segment3D.hpp"
#include <vector>

using namespace threepp;

class Segments {
public:
    Segments();

    void add(Segment2D& segment);
    void add(Segment3D& segment);

    void addToGroup();
    void updateSegments();
    void CCDSolver(Vector2& target);

    std::vector<Segment2D> getSegments();

private:
    std::vector<Segment2D> segments2D_;
    std::vector<Segment3D> segments3D_;

    Group group;

};

#endif //MAPPEEKSAMEN_SEGMENTS_HPP
