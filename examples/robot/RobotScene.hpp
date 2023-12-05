#ifndef MAPPEEKSAMEN_ROBOTSCENE_HPP
#define MAPPEEKSAMEN_ROBOTSCENE_HPP

#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"
#include "Kinematics/Segment2D.hpp"
#include "Kinematics/Segments.hpp"
#include "Kinematics/Cylinder.hpp"

using namespace threepp;

class RobotScene: public Scene {
public:
    explicit RobotScene(int size, Vector3 pos) {
        numCylinders_ = 1;

        auto grid = GridHelper::create(size, 1, 0x444444, 0x444444);
        grid->position.set(pos.x, pos.y, pos.z);
        grid->rotation.x = math::PI / 2;
        add(grid);

        camera_ = PerspectiveCamera::create();
        camera_->position.z = size;
        add(camera_);
        /*
        cylinderGeometry_ = CylinderGeometry::create(1, 1, 5);
        cylinderMaterial_ = MeshBasicMaterial::create();
        */
        cylinders_.emplace_back(Mesh::create(cylinderGeometry_, cylinderMaterial_));
        add(cylinders_.back());
    }

    [[nodiscard]] PerspectiveCamera& camera() const {
        return *camera_;
    }

    void updateNumCylinders(int numCylinders) {
        while(numCylinders != cylinders_.size()) {
            if(numCylinders < numCylinders_) {

            } else {

            }
        }
    }



private:

    std::shared_ptr<PerspectiveCamera> camera_;

    std::shared_ptr<CylinderGeometry> cylinderGeometry_;
    std::shared_ptr<MeshBasicMaterial> cylinderMaterial_;
    std::vector<std::shared_ptr<Mesh>> cylinders_;

    int numCylinders_;
};

#endif //MAPPEEKSAMEN_ROBOTSCENE_HPP