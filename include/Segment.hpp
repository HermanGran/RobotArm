#ifndef MAPPEEKSAMEN_SEGMENT_HPP
#define MAPPEEKSAMEN_SEGMENT_HPP

#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

class Segment {
public:

    Segment(const Vector3 &startPoint_, float len_, float angle_, const Color& color_);
    Segment(Segment& segment, float len_, float angle_, const Color& color_);

    void setStartPoint(const Vector3& startPoint_);

    void createSegment();

    //Converts degrees to radians
    float degreesToRadians(float angle_);

    //Returns angle
    float getAngle();

    //Points the segment at the mouse
    void pointAt(Vector3 target);

    //Calculates endpoint given startPoint, angle and length
    Vector3 getEndpoint();

    std::shared_ptr<Line> getline() const {
        return line;
    }

    void setChild(Segment* child);

private:
    Vector3 startPoint;
    Vector3 endPoint;
    Color segmentColor;
    std::shared_ptr<Line> line;
    std::shared_ptr<BufferGeometry> geometry;
    float len;
    float angle;
    Segment* childSegment = nullptr;
};
#endif //MAPPEEKSAMEN_SEGMENT_HPP
