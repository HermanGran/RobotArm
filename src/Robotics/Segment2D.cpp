#include "Kinematics/Segment2D.hpp"
#include "math/Math.hpp"
#include <cmath>

Segment2D::Segment2D(const Vector2& startPos, float angle, float len, const Color &color)
: startPos_(startPos), angle_(Math::degToRad(angle)), len_(len), color_(color) {
    createSegment();
}

Segment2D::Segment2D(Segment2D& segment, float angle, float len,const Color &color)
: startPos_(segment.getEndPos()), angle_(segment.getAngle() + Math::degToRad(angle)), len_(len), color_(color) {
    createSegment();
}

void Segment2D::createSegment() {
    auto material = LineBasicMaterial::create();
    geometry_ = BufferGeometry::create();

    getEndPos();

    material->color = color_;
    geometry_->setFromPoints({startPos_, endPos_});

    line_ = Line::create(geometry_, material);
}

std::shared_ptr<Line> Segment2D::getLine() {
    return line_;
}

float Segment2D::getAngle() const {
    return angle_;
}

float Segment2D::getLen() const {
    return len_;
}

Vector2 Segment2D::getStartPos() {
    return startPos_;
}

Vector2 Segment2D::getEndPos() {
    float dx = len_ * cos(angle_);
    float dy = len_ * sin(angle_);

    endPos_ = Vector2(startPos_.x + dx, startPos_.y + dy);
    return endPos_;
}

Vector2 Segment2D::getVector() {
    return endPos_ - startPos_;
}

void Segment2D::setAngle(float angle) {
    angle_ = angle;
}

void Segment2D::setEndPos(Vector2& target) {
    endPos_ = target;
}

void Segment2D::setStartPos(Vector2& endPos) {
    startPos_ = endPos;
}

void Segment2D::updateGeometry() {
    geometry_->setFromPoints({startPos_, endPos_});
}