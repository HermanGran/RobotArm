#include "Segment.hpp"
#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"
#include <cmath>
#include <iostream>

 using namespace threepp;

 Segment::Segment(const Vector3 &startPoint_, float len_, float angle_, const Color &color_) {
    startPoint = startPoint_;
    len = len_;
    angle = degreesToRadians(angle_);
    segmentColor = color_;

    createSegment();
}

Segment::Segment(Segment &segment, float len_, float angle_, const Color &color_) {
    startPoint = segment.getEndpoint();
    len = len_;
    angle = segment.getAngle() + degreesToRadians(angle_);
    segmentColor = color_;

    //setChild(&segment);
    createSegment();
 }

 void Segment::createSegment() {
    auto material = LineBasicMaterial::create();
    material->linewidth = 10;
    material->color = segmentColor;

    getEndpoint();
    geometry = BufferGeometry::create();
    geometry->setFromPoints({startPoint, endPoint});

    line = Line::create(geometry, material);
}

 void Segment::setStartPoint(const Vector3& startPoint_) {
     this->startPoint = startPoint_;
 }

void Segment::pointAt(Vector3 target) {
     Vector3 dir = target - startPoint;
     float targetAngle = atan2(dir.y, dir.x);

     //LERP calculations. For smoothing the movement of the lines.
     this->angle = this->angle + (targetAngle - this->angle) * 0.01;
     float dx = len * cos(this->angle);
     float dy = len * sin(this->angle);
     endPoint.set(startPoint.x + dx, startPoint.y + dy, startPoint.z);

     geometry->setFromPoints({startPoint, endPoint});

     if (childSegment) {
         childSegment->setStartPoint(this->getEndpoint());
         childSegment->pointAt(target);
     }
}

float Segment::getAngle() {
     return angle;
 }

Vector3 Segment::getEndpoint()  {
    float dx = len * cos(angle);
    float dy = len * sin(angle);

    endPoint = Vector3(startPoint.x + dx, startPoint.y + dy, startPoint.z);
    return endPoint;
}

 float Segment::degreesToRadians(float angle_) {
     return angle_ * (M_PI / 180);
 }

void Segment::setChild(Segment *child) {
     this->childSegment = child;
 }