#include "Kinematics/Segment3D.hpp"
#include <cmath>

Segment3D::Segment3D(const Vector3& startPos, float len, const threepp::Color &color)
: startPos_(startPos), angle_(math::degToRad(0)), len_(len), color_(color) {
    createSegment();
}

Segment3D::Segment3D(Segment3D &segment, float len, const threepp::Color &color)
: startPos_(segment.getEndPos()), angle_(0), len_(len), color_(color) {
    createSegment();
}

void Segment3D::createSegment() {
    auto material = LineBasicMaterial::create();
    geometry_ = BufferGeometry::create();

    getEndPos();

    material->color = color_;
    geometry_->setFromPoints({startPos_, endPos_});

    line_ = Line::create(geometry_, material);
}

std::shared_ptr<Line> Segment3D::getLine() {
    return line_;
}

float Segment3D::getAngle() const {
    return angle_;
}

float Segment3D::getLen() const {
    return len_;
}

Vector3 Segment3D::getEndPos() {
    float dx = len_ * cos(angle_);
    float dy = len_ * sin(angle_);

    endPos_ = Vector3(startPos_.x + dx, startPos_.y + dy, startPos_.z);
    return endPos_;
}

void Segment3D::setAngle(float angle) {
    angle_ = angle;
}

void Segment3D::setEndPos(Vector3& target) {
    endPos_ = target;
}

void Segment3D::setStartPos(Vector3& endPos) {
    startPos_ = endPos;
}

void Segment3D::updateGeometry(float angle) {
    Vector3 pivotPoint = startPos_;

    Matrix4 translationMatrixToOrigin;
    translationMatrixToOrigin.makeTranslation(-pivotPoint.x, -pivotPoint.y, -pivotPoint.z);

    Matrix4 rotationMatrix;
    rotationMatrix.makeRotationZ(angle - angle_);

    angle_ = angle;

    Matrix4 translationMatrixBack;
    translationMatrixBack.makeTranslation(pivotPoint.x, pivotPoint.y, pivotPoint.z);

    Matrix4 transformationMatrix = translationMatrixBack.multiply(rotationMatrix).multiply(translationMatrixToOrigin);

    line_->applyMatrix4(transformationMatrix);


}
