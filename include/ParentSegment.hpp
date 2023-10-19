#ifndef MAPPEEKSAMEN_PARENTSEGMENT_HPP
#define MAPPEEKSAMEN_PARENTSEGMENT_HPP

#include "Segment.hpp"
#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"

class ParentSegment {
public:

    ParentSegment(Segment& segment, float len_, float angle_, const Color& color);

    void createParentSegment();

    float degreesToRadians(float angle_);

    std::shared_ptr<Line> getLine() const {
        return line;
    }

private:
    Vector3 startPoint;
    Vector3 endPoint;
    Color segmentColor;
    std::shared_ptr<Line> line;
    float len;
    float angle;
};

#endif //MAPPEEKSAMEN_PARENTSEGMENT_HPP