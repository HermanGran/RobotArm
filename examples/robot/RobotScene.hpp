#ifndef MAPPEEKSAMEN_ROBOTSCENE_HPP
#define MAPPEEKSAMEN_ROBOTSCENE_HPP

#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

class RobotScene: public Scene {
public:
    explicit RobotScene(int size) {

        // Creating a box around center
        auto grid = GridHelper::create(size, 1, 0x444444, 0x444444);
        grid->position.set(0, 0, 0);
        grid->rotation.x = math::PI / 2;
        add(grid);

        // Creating Camera
        camera_ = PerspectiveCamera::create();
        camera_->position.z = size;
        add(camera_);

        // Create geometry for cylinder
        segmentGeometry_ = BoxGeometry::create(5, 1, 1);
        segmentGeometry_->translate(2, 0, 0);

        // Create material for cylinder
        segmentMaterial_ = MeshBasicMaterial::create();
        segmentMaterial_->color = Color::red;
    }

    [[nodiscard]] PerspectiveCamera& camera() const {
        return *camera_;
    }

    void updateNumSegments(int numCylinders) {
        while (numCylinders > segments_.size()) {
            auto newCylinder = Mesh::create(segmentGeometry_, segmentMaterial_);
            Vector3 worldPos;

            if (!segments_.empty()) {
                segments_.back()->getWorldPosition(worldPos);
                newCylinder->position.set(worldPos.x, worldPos.y + 5, worldPos.z);
            }

            segments_.push_back(newCylinder);
            angles_.push_back(0);
            add(newCylinder);
        }

        while (numCylinders < segments_.size()) {

            remove(*segments_.back());
            segments_.pop_back();
            angles_.pop_back();
        }
    }

    void setAngle(int box, float angle) {
        angles_[box] = angle;
        segments_[box]->rotation.z = angles_[box];
    }

    void CCDSolver(const Vector3 &target, float maxAngleChange = 0.05f) {
        for (int iter = 0; iter < 10; ++iter) {
            for (int i = segments_.size() - 1; i >= 0; --i) {
                Vector3 endEffector = {
                        segments_.back()->position.x + cos(angles_.back()) * 5,
                        segments_.back()->position.y + sin(angles_.back()) * 5,
                        0
                };

                segments_[i]->updateMatrixWorld(true);
                Vector3 currentPos = segments_[i]->position;
                Vector3 toEndEffector = endEffector - currentPos;
                Vector3 toTarget = target - currentPos;

                float desiredAngleDiff = atan2(toTarget.y, toTarget.x) - atan2(toEndEffector.y, toEndEffector.x);

                // Dampening effect created with big help from chatGPT
                float angleChange = std::clamp(desiredAngleDiff, -maxAngleChange, maxAngleChange) * 0.1;
                angles_[i] += angleChange;

                setAngle(i, angles_[i]);
                updateSegmentPositions(i);
            }

            Vector3 endEffectorPos = {
                    segments_.back()->position.x + cos(angles_.back()) * 5,
                    segments_.back()->position.y + sin(angles_.back()) * 5,
                    0
            };
            if ((endEffectorPos - target).length() < 0.1f) {
                break;
            }
        }
    }

    void updateSegmentPositions(int box) {
        for (int i = box + 1; i < segments_.size(); ++i) {
            Vector3 newPos = {
                    segments_[i - 1]->position.x + cos(angles_[i - 1]) * 5,
                    segments_[i - 1]->position.y + sin(angles_[i - 1]) * 5,
                    0
            };
            segments_[i]->position = newPos;
        }
    }


private:
    std::shared_ptr<PerspectiveCamera> camera_;
    std::shared_ptr<BoxGeometry> segmentGeometry_;
    std::shared_ptr<MeshBasicMaterial> segmentMaterial_;

    std::vector<float> angles_;
    std::vector<std::shared_ptr<Mesh>> segments_;
};

#endif //MAPPEEKSAMEN_ROBOTSCENE_HPP