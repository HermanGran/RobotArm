#ifndef MAPPEEKSAMEN_ROBOTSCENE_HPP
#define MAPPEEKSAMEN_ROBOTSCENE_HPP

#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"
#include <iostream>

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
        boxGeometry_ = BoxGeometry::create(5, 1, 1);
        boxGeometry_->translate(2, 0, 0);

        // Create material for cylinder
        boxMaterial_ = MeshBasicMaterial::create();
        boxMaterial_->color = Color::red;
    }

    [[nodiscard]] PerspectiveCamera& camera() const {
        return *camera_;
    }

    void updateNumCylinders(int numCylinders) {
        while (numCylinders > boxes_.size()) {
            auto newCylinder = Mesh::create(boxGeometry_, boxMaterial_);
            Vector3 worldPos;

            if (!boxes_.empty()) {
                boxes_.back()->getWorldPosition(worldPos);
                newCylinder->position.set(worldPos.x, worldPos.y + 5, worldPos.z);
            }

            boxes_.push_back(newCylinder);
            angles_.push_back(0);
            add(newCylinder);
        }

        while (numCylinders < boxes_.size()) {

            remove(*boxes_.back());
            boxes_.pop_back();
            angles_.pop_back();
        }
    }

    void setAngle(int box, float angle) {
        angles_[box] = angle;
        boxes_[box]->rotation.z = angles_[box];
    }

    void CCDSolver(const Vector3 &target, float maxAngleChange = 0.05f) {
        for (int iter = 0; iter < 10; ++iter) {
            for (int i = boxes_.size() - 1; i >= 0; --i) {
                Vector3 endEffector = {
                        boxes_.back()->position.x + cos(angles_.back()) * 5,
                        boxes_.back()->position.y + sin(angles_.back()) * 5,
                        0
                };

                boxes_[i]->updateMatrixWorld(true);
                Vector3 currentPos = boxes_[i]->position;
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
                    boxes_.back()->position.x + cos(angles_.back()) * 5,
                    boxes_.back()->position.y + sin(angles_.back()) * 5,
                    0
            };
            if ((endEffectorPos - target).length() < 0.1f) {
                break;
            }
        }
    }

    void updateSegmentPositions(int box) {
        for (int i = box + 1; i < boxes_.size(); ++i) {
            Vector3 newPos = {
                    boxes_[i - 1]->position.x + cos(angles_[i - 1]) * 5,
                    boxes_[i - 1]->position.y + sin(angles_[i - 1]) * 5,
                    0
            };
            boxes_[i]->position = newPos;
        }
    }

    void rotatingQ(const Vector3 &target) {
        Quaternion currentOrientation = boxes_.front()->quaternion;
        Vector3 currentDirection = Vector3(0, 0, 1).applyQuaternion(currentOrientation);

        Vector3 currentPosition = boxes_.front()->position;
        Vector3 targetDirection = (target - currentPosition).normalize();

        Vector3 rotationAxis = currentDirection.cross(targetDirection).normalize();

        float dot = currentDirection.dot(targetDirection);
        float angle = std::acos(std::clamp(dot, -1.0f, 1.0f));

        Quaternion rotation;
        rotation.setFromAxisAngle(rotationAxis, angle);

        boxes_.front()->quaternion = rotation;
    }

private:

    std::shared_ptr<PerspectiveCamera> camera_;

    std::shared_ptr<BoxGeometry> boxGeometry_;
    std::shared_ptr<MeshBasicMaterial> boxMaterial_;
    std::vector<std::shared_ptr<Mesh>> boxes_;

    std::vector<float> angles_;
    std::vector<Vector3> endPositions_;
};

#endif //MAPPEEKSAMEN_ROBOTSCENE_HPP