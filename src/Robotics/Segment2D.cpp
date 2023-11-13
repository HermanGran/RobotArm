#include "Kinematics/Segment2D.hpp"
#include "math/Math.hpp"
#include <cmath>

Segment2D::Segment2D(const Vector2& startPos, float len, const Color &color)
: startPos_(startPos), angle_(0), len_(len), color_(color) {
    createSegment();
}

Segment2D::Segment2D(Segment2D& segment, float len,const Color &color)
: startPos_(segment.getEndPos()), angle_(0), len_(len), color_(color) {
    createSegment();
}

void Segment2D::createSegment() {
    auto material = LineBasicMaterial::create();
    geometry_ = BufferGeometry::create();

    calculateEndPos(angle_);

    material->color = color_;
    geometry_->setFromPoints({startPos_, endPos_});

    line_ = Line::create(geometry_, material);
}

void Segment2D::calculateEndPos(float angle) {
    float dx = len_ * cos(angle);
    float dy = len_ * sin(angle);

    endPos_ = Vector2(startPos_.x + dx, startPos_.y + dy);
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

const Vector2& Segment2D::getStartPos() const {
    return startPos_;
}

const Vector2& Segment2D::getEndPos()  {
    calculateEndPos(angle_);
    return endPos_;
}

const Vector2& Segment2D::getVector() const {
    return endPos_ - startPos_;
}

void Segment2D::setAngle(const float angle) {
    line_->rotation.z = angle;
}

void Segment2D::setEndPos(const Vector2& target) {
    endPos_ = target;
}

void Segment2D::setStartPos(const Vector2& endPos) {
    startPos_ = endPos;
}

void Segment2D::updateWithRotation(float angle) {
    angle_ = angle;
    line_->rotation.z = angle;
}

void Segment2D::update() {
    line_->rotation.z = angle_;
};