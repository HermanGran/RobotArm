#ifndef MAPPEEKSAMEN_SEGMENTS_HPP
#define MAPPEEKSAMEN_SEGMENTS_HPP

#include "threepp/threepp.hpp"
#include "Kinematics/Segment2D.hpp"
#include "Kinematics/Segment3D.hpp"
#include <vector>

using namespace threepp;

class Segments {
public:
    Segments();

    void add(Segment2D& segment);


    std::vector<Segment2D>& getSegments();

    void addToScene();


    void addSegment(const Vector2& startPos, float len, const Color& color);
    void updateNumberOfSegments(int numSegments, const Vector2& startPos, float len, const Color& color);
    void removeLastSegment();

private:
    std::vector<Segment2D> segments2D_;
    std::vector<Segment3D> segments3D_;

    std::shared_ptr<CylinderGeometry> cylinderGeometry_;
    std::shared_ptr<MeshBasicMaterial> cylinderMaterial;
    std::vector<Mesh> cylinders_;
};

#endif //MAPPEEKSAMEN_SEGMENTS_HPP
