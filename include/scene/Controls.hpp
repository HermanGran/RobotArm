
#ifndef ROBOTARM_CONTROLS_HPP
#define ROBOTARM_CONTROLS_HPP

#include "threepp/threepp.hpp"
#include "threepp/extras/imgui/ImguiContext.hpp"

using namespace threepp;

/**
 * Controls class for handling ImGui interface for target point and number of segments
 */
class Controls {
public:

    /**
     * Constructor for Controls
     * Initializes ImGui interface
     * @param canvas Reference for Canvas for adding UI
     * @param controls Reference for OrbitControls for disabling while hovering UI interface
     * @param maxNumSegments Max number of segments allowed
     */
    explicit Controls(Canvas& canvas, OrbitControls& controls, int maxNumSegments);

    /**
     * Gets number of segments wanted
     * @return Number of segments
     */
    [[nodiscard]] int numSegments() const;

    /**
     * Gets target point
     * @return Reference for target point in form of Vector3
     */
    Vector3& getTarget();

    /**
     * Gets pointer for UI interface
     * @return Pointer to ImGui UI
     */
    std::shared_ptr<ImguiFunctionalContext> ui();

private:
    int numSegments_ = 2;
    int maxNumSegments_;
    Vector3 target_;
    std::shared_ptr<ImguiFunctionalContext> ui_;
};

#endif //ROBOTARM_CONTROLS_HPP