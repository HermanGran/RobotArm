#ifndef MAPPEEKSAMEN_SEGMENT_HPP
#define MAPPEEKSAMEN_SEGMENT_HPP

#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

class Segment {
public:

    Segment(const Vector3 &startPoint_, float len_, float angle_, const Color& color_);

    void createSegment();

    float degreesToRadians(float angle_);

    std::shared_ptr<Line> getline() const {
        return line;
    }

    Vector3 getEndpoint() const;
private:
    Vector3 startPoint;
    Vector3 endPoint;
    Color segmentColor;
    std::shared_ptr<Line> line;
    float len;
    float angle;
};
#endif //MAPPEEKSAMEN_SEGMENT_HPP
