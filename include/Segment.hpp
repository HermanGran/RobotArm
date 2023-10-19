#ifndef MAPPEEKSAMEN_SEGMENT_HPP
#define MAPPEEKSAMEN_SEGMENT_HPP

#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

class Segment {
public:

    Segment(const Vector3 &startPoint, float len, double angle, const Color& color);

    void createSegment();

    std::shared_ptr<Line> getline() const {
        return line;
    }

private:
    Vector3 startPoint;
    float len;
    double angle;
    Color segmentColor;
    std::shared_ptr<Line> line;
};
#endif //MAPPEEKSAMEN_SEGMENT_HPP
