
#ifndef ROBOTARM_BOIDS_HPP
#define ROBOTARM_BOIDS_HPP

#include "threepp/threepp.hpp"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace threepp;

class Boids: public Scene {
public:
    explicit Boids(int numBoids);

    void initBoids();
    void move(float dt);

    float random();

    [[nodiscard]] PerspectiveCamera& camera() const;

private:
    int numBoids_;

    std::vector<std::shared_ptr<Mesh>> boids_;
    std::shared_ptr<SphereGeometry> boidsGeometry_;
    std::shared_ptr<MeshBasicMaterial> boidsMaterial_;

    std::shared_ptr<PerspectiveCamera> camera_;
};

#endif //ROBOTARM_BOIDS_HPP
