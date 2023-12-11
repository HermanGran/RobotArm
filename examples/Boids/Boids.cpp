#include "Boids.hpp"

// Will focus on test cases before continuing with boids
Boids::Boids(int numBoids)
: numBoids_(numBoids) {
    boidsGeometry_ = SphereGeometry::create();
    boidsMaterial_= MeshBasicMaterial::create();
    boidsMaterial_->color = Color::black;

    camera_ = PerspectiveCamera::create();
    camera_->position.z = 20;
    add(camera_);

    auto grid = GridHelper::create(20, 6, 0x444444, 0x444444);
    grid->position.set(0, 0, 0);
    add(grid);

}

// Random numbers generator from programming with mosh
// https://www.youtube.com/watch?v=ZzaPdXTrSb8 Timestamp = 1:19:10
float Boids::random() {
    srand(time(0));
    int num = rand() % 10;
    return num;
}

void Boids::move(float dt) {
    Vector3 target(3, 3, 3);
    boids_.front()->position = target;
}

void Boids::initBoids() {
    auto newBoids = Mesh::create(boidsGeometry_, boidsMaterial_);

    for (int i = 0; i < numBoids_; ++i) {
        boids_.push_back(newBoids);
        add(newBoids);
    }
}

PerspectiveCamera& Boids::camera() const {
    return *camera_;
}
