
#ifndef ROBOTARM_CONTROLS_HPP
#define ROBOTARM_CONTROLS_HPP

#include "threepp/threepp.hpp"
#include "threepp/extras/imgui/ImguiContext.hpp"

using namespace threepp;

// Setting up controls for the robotArm and targetPoint
class Controls {
public:

    // Constructor: Initializes given the canvas and OrbitControls for ImGui
    explicit Controls(Canvas& canvas, OrbitControls& controls);

    // Returns numSegments
    [[nodiscard]] int numSegments() const;

    // Returns target point
    Vector3& getTarget();

    // Returns the ImGui controls for rendering
    std::shared_ptr<ImguiFunctionalContext> ui();

private:
    int numSegments_ = 2;
    Vector3 target_;
    std::shared_ptr<ImguiFunctionalContext> ui_;
};

#endif //ROBOTARM_CONTROLS_HPP