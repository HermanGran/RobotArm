#include "geometry/RobotArm.hpp"
#include <utility>

RobotArm::RobotArm(std::shared_ptr<BoxGeometry> geometry, std::shared_ptr<MeshBasicMaterial> material)
: segmentGeometry_(std::move(geometry)), segmentMaterial_(std::move(material)) {}

void RobotArm::updateNumSegments(int numSegments) {
    while (numSegments > segments_.size()) {
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

    while (numSegments < segments_.size()) {

        remove(*segments_.back());
        segments_.pop_back();
        angles_.pop_back();
    }
}

void RobotArm::updateSegmentPositions(int segment) {
    for (int i = segment + 1; i < segments_.size(); ++i) {
        Vector3 newPos = {
                segments_[i - 1]->position.x + cos(angles_[i - 1]) * 5,
                segments_[i - 1]->position.y + sin(angles_[i - 1]) * 5,
                0
        };
        segments_[i]->position = newPos;
    }
}

void RobotArm::setAngle(int segment, float angle) {
    angles_[segment] = angle;
    segments_[segment]->rotation.z = angles_[segment];
}

void RobotArm::CCDSolver(const threepp::Vector3 &target, float maxAngleChange) {
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

std::shared_ptr<BoxGeometry>& RobotArm::getGeometry() {
    return segmentGeometry_;
}

std::shared_ptr<MeshBasicMaterial>& RobotArm::getMaterial() {
    return segmentMaterial_;
}