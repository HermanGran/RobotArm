#ifndef MAPPEEKSAMEN_BOX_HPP
#define MAPPEEKSAMEN_BOX_HPP

#include "threepp/threepp.hpp"

using namespace threepp;

class Ball {
public:
    Ball(const Color& color);

    void createSphere();

    std::shared_ptr<Mesh> getBall();


private:
    Vector3 pos_{0, 0, 0};
    Color color_;
    std::shared_ptr<Mesh> ball_;
    std::shared_ptr<CircleGeometry> geometry_;
    std::shared_ptr<MeshBasicMaterial> material_;
};

#endif //MAPPEEKSAMEN_BOX_HPP
