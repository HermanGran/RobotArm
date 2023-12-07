#ifndef MAPPEEKSAMEN_ROBOTSCENE_HPP
#define MAPPEEKSAMEN_ROBOTSCENE_HPP

#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"
#include "geometry/RobotArm.hpp"
#include "geometry/Ball.hpp"

using namespace threepp;

// RobotScene is responsible for setting up the 3D scene for the robot simulation
class RobotScene: public Scene {
public:
    // Constructor: Initializes the scene with a specific size
    explicit RobotScene(int size);

    // Provides access to the scenes camera
    [[nodiscard]] PerspectiveCamera& camera() const;

private:
    std::shared_ptr<PerspectiveCamera> camera_;
};

#endif //MAPPEEKSAMEN_ROBOTSCENE_HPP