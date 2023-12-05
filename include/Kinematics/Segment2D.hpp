#ifndef MAPPEEKSAMEN_SEGMENT2D_HPP
#define MAPPEEKSAMEN_SEGMENT2D_HPP

#include "threepp/threepp.hpp"

using namespace threepp;

class Segment2D {
public:
    Segment2D(const Vector2& startPos, float len_, const Color& color_);
    Segment2D(Segment2D& parent, float len_, const Color& color_);

    void createSegment();
    void calculateEndPos(float angle);

    [[nodiscard]] float getAngle() const;
    [[nodiscard]] float getLen() const;
    [[nodiscard]] const Vector2& getStartPos() const;
    [[nodiscard]] const Vector2& getEndPos();

    std::shared_ptr<Line> getLine();

    void setAngle(float angle);
    void setEndPos(const Vector2& target);
    void setStartPos(const Vector2& endPos);
    void update(Segment2D &segment);
    void rotateAroundStartPoint(float angle);
    void setChild(std::shared_ptr<Line> child);

private:
    Vector2 startPos_;
    Vector2 endPos_;

    float len_;
    float angle_;

    Color color_;
    std::shared_ptr<Line> line_;
    std::shared_ptr<BufferGeometry> geometry_;
    std::shared_ptr<Line> child_;

    bool hasChild_;
};

#endif //MAPPEEKSAMEN_SEGMENT2D_HPP
