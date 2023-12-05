#include "Kinematics/Segment2D.hpp"
#include <cmath>

Segment2D::Segment2D(const Vector2& startPos, float len, const Color &color)
: startPos_(startPos), angle_(0), len_(len), color_(color) {
    createSegment();
}

Segment2D::Segment2D(Segment2D& parent, float len,const Color &color)
: startPos_(parent.getEndPos()), angle_(0), len_(len), color_(color) {
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

void Segment2D::setAngle(const float angle) {
    angle_ = angle;
    line_->rotation.z = angle_;
}

void Segment2D::setEndPos(const Vector2& target) {
    endPos_ = target;
}

void Segment2D::setStartPos(const Vector2& endPos) {
    startPos_ = endPos;
    calculateEndPos(angle_);
}

void Segment2D::update(Segment2D &segment) {
    line_->position.set(segment.getEndPos().x - startPos_.x, segment.getEndPos().y - startPos_.y, 0);
    //line_->rotation.z = segment.getAngle() - angle_;
    Vector3 world;
    line_->getWorldPosition(world);
    //startPos_ = {world.x, world.y};
    //rotateAroundStartPoint(segment.getAngle() + angle_);

}

// Fikk hjelp av chatGPT for å rotere linjen rundt sin egen akse
void Segment2D::rotateAroundStartPoint(float angle) {
    Vector3 pivotPoint = {startPos_.x, startPos_.y, 0};

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

void Segment2D::setChild(std::shared_ptr<Line> child) {
    hasChild_ = true;
    child_ = child;
}
