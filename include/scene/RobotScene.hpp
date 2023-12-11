#ifndef MAPPEEKSAMEN_ROBOTSCENE_HPP
#define MAPPEEKSAMEN_ROBOTSCENE_HPP

#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

/**
 * RobotScene class responsible for setting up camera and scene for robotArm
 */
class RobotScene: public Scene {
public:
    /**
     * Constructor for RobotScene
     * Initializes scene with camera, shadow rendering, lights and platform for robotArm
     * @param size Platform size
     */
    explicit RobotScene(int size);

    /**
     * Gets PerspectiveCamera
     * @return Const reference to PerspectiveCamera
     */
    [[nodiscard]] PerspectiveCamera& camera() const;

private:
    std::shared_ptr<PerspectiveCamera> camera_;
};

#endif //MAPPEEKSAMEN_ROBOTSCENE_HPP