#include "scene/Controls.hpp"

// Constructor
Controls::Controls(Canvas &canvas, OrbitControls& controls) {

    // Creates target
    targetGeometry_ = SphereGeometry::create();
    targetMaterial_ = MeshLambertMaterial::create();
    targetMaterial_->color = Color::green;
    targetPoint_ = Mesh::create(targetGeometry_, targetMaterial_);
    targetPoint_->castShadow = true;
    targetPoint_->receiveShadow = true;
    target_.set(10, 10, 0);

    // Help from chatGPT for initializing ui_ : std::make_shared
    ui_ = std::make_shared<ImguiFunctionalContext>(canvas.windowPtr(), [&] {
        ImGui::SetNextWindowPos({0, 0}, 0, {0, 0});
        ImGui::SetNextWindowSize({230, 0}, 0);
        ImGui::Begin("Robot Arm");

        // Creates sliders for controlling the target point
        // Will upgrade du draggable object and also boids if I have the time
        ImGui::SliderFloat("x Position", &target_.x, -20, 20.f);
        ImGui::SliderFloat("y Position", &target_.y, 1, 25.f);
        ImGui::SliderFloat("z position", &target_.z, -20, 20.f);
        ImGui::Text("Segments: %d", numSegments_);
        controls.enabled = !ImGui::IsWindowHovered();

        if (ImGui::Button("-") && numSegments_ > 1) {
            numSegments_ -= 1;
        }

        ImGui::SameLine();
        if (ImGui::Button("+") && numSegments_ < 6){
            numSegments_ += 1;
        }
        ImGui::End();
    });
}

// Returns numSegments
int Controls::numSegments() const {
    return numSegments_;
}

// Returns target point
std::shared_ptr<Mesh>& Controls::target() {
    targetPoint_->position = target_;
    return targetPoint_;
}

// Returns ImGui controls
std::shared_ptr<ImguiFunctionalContext> Controls::ui() {
    return ui_;
}