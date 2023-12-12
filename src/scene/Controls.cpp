#include "scene/Controls.hpp"

// Constructor
Controls::Controls(Canvas &canvas, OrbitControls& controls, int maxNumSegments)
: maxNumSegments_(maxNumSegments) {

    target_.set(10, 10, 10);

    // Help from chatGPT for initializing ui_ : std::make_shared
    ui_ = std::make_shared<ImguiFunctionalContext>(canvas.windowPtr(), [&] {
        ImGui::SetNextWindowPos({0, 0}, 0, {0, 0});
        ImGui::SetNextWindowSize({230, 0}, 0);
        ImGui::Begin("Robot Arm");

        // Creates sliders for controlling the target point
        // Will upgrade du draggable object and also boids if I have the time
        ImGui::Text("Target Position");
        ImGui::SliderFloat("X ", &target_.x, -20, 20.f);
        ImGui::SliderFloat("Y ", &target_.y, 1, 25.f);
        ImGui::SliderFloat("Z ", &target_.z, -20, 20.f);

        ImGui::Text("Segment size");
        ImGui::SliderFloat("Size", &size_, 0.1, 3.f);
        ImGui::SliderFloat("Length ", &length_, 0.2, 10.f);

        ImGui::Text("Segments: %d", numSegments_);
        controls.enabled = !ImGui::IsWindowHovered();
        if (ImGui::Button("-") && numSegments_ > 1) {
            numSegments_ -= 1;
        }

        ImGui::SameLine();
        if (ImGui::Button("+") && numSegments_ < maxNumSegments_){
            numSegments_ += 1;
        }
        ImGui::End();
    });
}

// Returns numSegments
int Controls::numSegments() const {
    return numSegments_;
}

// Gets wanted size for segments
float Controls::getSize() const {
    return size_;
}

// Gets wanted length for segments
float Controls::getLength() const {
    return length_;
}

// Returns target point
Vector3& Controls::getTarget() {
    return target_;
}

// Returns ImGui controls
std::shared_ptr<ImguiFunctionalContext> Controls::ui() {
    return ui_;
}