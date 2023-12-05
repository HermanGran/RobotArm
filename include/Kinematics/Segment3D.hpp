#ifndef MAPPEEKSAMEN_SEGMENT3D_HPP
#define MAPPEEKSAMEN_SEGMENT3D_HPP

#include "threepp/threepp.hpp"

using namespace threepp;

class Segment3D {
public:
    Segment3D(const Vector3& startPos, float len_, const Color& color_);
    Segment3D(Segment3D& segment, float len_, const Color& color_);

    void createSegment();

    float getAngle() const;
    float getLen() const;
    Vector3 getEndPos();

    std::shared_ptr<Line> getLine();

    void setAngle(float angle);
    void setEndPos(Vector3& target);
    void setStartPos(Vector3& endPos);
    void updateGeometry(float angle);

private:
    Vector3 startPos_;
    Vector3 endPos_;

    float len_;
    float angle_;

    Color color_;
    std::shared_ptr<Line> line_;
    std::shared_ptr<BufferGeometry> geometry_;
};
#endif //MAPPEEKSAMEN_SEGMENT3D_HPP
