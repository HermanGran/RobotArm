#include "Segment.hpp"
#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"
#include <cmath>

 using namespace threepp;

 Segment::Segment(const Vector3 &startPoint_, float len_, float angle_, const Color &color_) {
    startPoint = startPoint_;

    len = len_;
    angle = degreesToRadians(angle_);

    segmentColor = color_;

    createSegment();
}

 void Segment::createSegment() {
    auto material = LineBasicMaterial::create();
    material->color = segmentColor;

    float dx = len * cos(angle);
    float dy = len * sin(angle);

    endPoint = Vector3(startPoint.x + dx, startPoint.y + dy, startPoint.z);

    auto geometry = BufferGeometry::create();
    geometry->setFromPoints({startPoint, endPoint});

    line = Line::create(geometry, material);
}

Vector3 Segment::getEndpoint() const {
     return endPoint;
 }

 float Segment::degreesToRadians(float angle_) {
     return angle_ * (M_PI / 180);
 }