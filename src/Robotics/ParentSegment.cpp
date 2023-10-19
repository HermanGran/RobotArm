#include "ParentSegment.hpp"

ParentSegment::ParentSegment(Segment &segment, float len_, float angle_, const threepp::Color &color_) {
    startPoint = segment.getEndpoint();

    len = len_;
    angle = degreesToRadians(angle_);

    segmentColor = color_;

    createParentSegment();
}

void ParentSegment::createParentSegment() {
    auto material = LineBasicMaterial::create();
    material->color = segmentColor;

    float dx = len * cos(angle);
    float dy = len * sin(angle);

    endPoint = Vector3(startPoint.x + dx, startPoint.y + dy, startPoint.z);

    auto geometry = BufferGeometry::create();
    geometry->setFromPoints({startPoint, endPoint});

    line = Line::create(geometry, material);
}

float ParentSegment::degreesToRadians(float angle_) {
    return angle_ * (M_PI / 180);
}