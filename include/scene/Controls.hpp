
#ifndef ROBOTARM_CONTROLS_HPP
#define ROBOTARM_CONTROLS_HPP
#include "scene/RobotScene.hpp"

using namespace threepp;

// Setting up controls for the robotArm and targetPoint
class Controls {
public:

    // Constructor: Initializes given the canvas and OrbitControls for ImGui
    explicit Controls(Canvas& canvas, OrbitControls& controls);

    // Returns numSegments
    int numSegments() const;

    // Returns target point
    Vector3& target();

    // Returns the ImGui controls for rendering
    std::shared_ptr<ImguiFunctionalContext> ui();

private:
    int numSegments_;
    Vector3 target_;
    std::shared_ptr<ImguiFunctionalContext> ui_;
};

#endif //ROBOTARM_CONTROLS_HPP
