#ifndef MAPPEEKSAMEN_ROBOTSCENE_HPP
#define MAPPEEKSAMEN_ROBOTSCENE_HPP

#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"
#include "geometry/RobotArm.hpp"

using namespace threepp;

class RobotScene: public Scene {
public:
    explicit RobotScene(int size);

    [[nodiscard]] PerspectiveCamera& camera() const;


private:
    std::shared_ptr<PerspectiveCamera> camera_;
};

#endif //MAPPEEKSAMEN_ROBOTSCENE_HPP