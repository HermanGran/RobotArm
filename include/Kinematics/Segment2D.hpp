#ifndef MAPPEEKSAMEN_SEGMENT2D_HPP
#define MAPPEEKSAMEN_SEGMENT2D_HPP

#include "threepp/threepp.hpp"

using namespace threepp;

class Segment2D {
public:
    Segment2D(const Vector2& startPos, float angle_, float len_, const Color& color_);
    Segment2D(Segment2D& segment, float angle_, float len_, const Color& color_);

    void createSegment();

    float getAngle() const;
    float getLen() const;
    Vector2 getStartPos();
    Vector2 getEndPos();
    Vector2 getVector();

    std::shared_ptr<Line> getLine();

    void setAngle(float angle);
    void setEndPos(Vector2& target);
    void setStartPos(Vector2& endPos);
    void updateGeometry();

private:
    Vector2 startPos_;
    Vector2 endPos_;

    float len_;
    float angle_;

    Color color_;
    std::shared_ptr<Line> line_;
    std::shared_ptr<BufferGeometry> geometry_;
};

#endif //MAPPEEKSAMEN_SEGMENT2D_HPP
