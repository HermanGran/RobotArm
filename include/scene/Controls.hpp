
#ifndef ROBOTARM_CONTROLS_HPP
#define ROBOTARM_CONTROLS_HPP

#include "threepp/threepp.hpp"
#include "threepp/extras/imgui/ImguiContext.hpp"
#include "kinematics/RobotArm.hpp"

using namespace threepp;

// Setting up controls for the robotArm and targetPoint
class Controls {
public:

    // Constructor: Initializes given the canvas and OrbitControls for ImGui
    explicit Controls(Canvas& canvas, OrbitControls& controls);

    // Returns numSegments
    [[nodiscard]] int numSegments() const;

    // Returns target point
    std::shared_ptr<Mesh>& target();

    // Returns the ImGui controls for rendering
    std::shared_ptr<ImguiFunctionalContext> ui();

private:
    int numSegments_ = 2;
    Vector3 target_;
    std::shared_ptr<ImguiFunctionalContext> ui_;

    std::shared_ptr<SphereGeometry> targetGeometry_;
    std::shared_ptr<MeshLambertMaterial> targetMaterial_;
    std::shared_ptr<Mesh> targetPoint_;
};

#endif //ROBOTARM_CONTROLS_HPP