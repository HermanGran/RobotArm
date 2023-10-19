#include "Segment.hpp"
#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"
#include <cmath>

 using namespace threepp;

 Segment::Segment(const Vector3 &startPoint_, float len_, double angle_, const Color &color_) {
    startPoint = startPoint_;

    len = len_;
    angle = (angle_ * (M_PI / 180));

    segmentColor = color_;

    createSegment();
}

 void Segment::createSegment() {
    auto material = LineBasicMaterial::create();
    material->color = segmentColor;

    float dx = len * cos(angle);
    float dy = len * sin(angle);

    Vector3 endPoint(startPoint.x + dx, startPoint.y + dy, startPoint.z);

    auto geometry = BufferGeometry::create();
    geometry->setFromPoints({startPoint, endPoint});

    line = Line::create(geometry, material);
}