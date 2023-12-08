#include "geometry/RobotArm.hpp"
#include <eigen3/Eigen/Dense>
#include <iostream>

// Constructor: Initializing the arm
RobotArm::RobotArm() {

    // Creating geometry for each segment
    segmentGeometry_ = BoxGeometry::create(1, 1, 5);
    segmentGeometry_->translate(0, 0, 2);

    // Creating material for each segment
    segmentMaterial_ = MeshBasicMaterial::create();
    segmentMaterial_->color = Color::red;
}

// Updates the angles of each segment
void RobotArm::setAngle(int segment, float angle) {
    angles_[segment] = angle;
    segments_[segment]->rotation.z = angles_[segment];
}

// Updates the number of segments
void RobotArm::updateNumSegments(int numSegments) {

    // Adds segments
    while (numSegments > segments_.size()) {
        auto newSegment = Mesh::create(segmentGeometry_, segmentMaterial_);
        segments_.push_back(newSegment);
        angles_.push_back(0);
        add(newSegment);
    }

    // Removes segments
    while (numSegments < segments_.size()) {
        remove(*segments_.back());
        segments_.pop_back();
        angles_.pop_back();
    }
}

// Calculates the endpoint for the segment given the current position and returns the position
Vector3 RobotArm::calculateEndPoint(int segment) {
    // Segment length
    float length = 5;

    Vector3 endPoint = {
            segments_[segment]->position.x + cos(angles_[segment]) * length,
            segments_[segment]->position.y + sin(angles_[segment]) * length,
            segments_[segment]->position.z
    };
    return endPoint;
}

Vector3 RobotArm::calculateEndPointQ(int segment) {
    float length = 5;

    // The direction forward: Z coordinates
    Vector3 forward(0, 0, 1);
    Vector3 endPos;
    Quaternion world;

    // Get the world position of the segment
    segments_[segment]->getWorldQuaternion(world);

    // Applies the orientation of the segment to the forward vector
    forward.applyQuaternion(world);

    endPos = (forward * length) + segments_[segment]->position;
    return endPos;
}

// Updates the positions for each segment when CCD iterates over
void RobotArm::updateSegmentPositions(int segment) {
    if (segment > 0) {
        segments_[segment]->position = calculateEndPoint(segment - 1);
    }
}

void RobotArm::updateWithQ(int segment) {
    for (int i = segment + 1; i < segments_.size(); ++i) {
        segments_[i]->position = calculateEndPointQ(i - 1);
    }
}

// Cyclic Coordinates Descent for calculating desired angle to target position and iterates over each segment to update
void RobotArm::CCDSolver(const Vector3 &target, float maxAngleChange) {

    // CCD Algorithm: with max iterations
    for (int iter = 0; iter < 10; ++iter) {
        for (int i = segments_.size() - 1; i >= 0; --i) {
            // Calculate the current direction vector from the segment to the end effector
            Vector3 endEffector = calculateEndPoint(segments_.size() - 1);

            Vector3 currentPos = segments_[i]->position;
            Vector3 toEndEffector = endEffector - currentPos;

            // Calculate the desired direction vector from the segment to the target
            Vector3 toTarget = target - currentPos;

            float desiredAngleDiff = atan2(toTarget.y, toTarget.x) - atan2(toEndEffector.y, toEndEffector.x);

            // Dampening effect for moving smooth created with big help from chatGPT
            float angleChange = std::clamp(desiredAngleDiff, -maxAngleChange, maxAngleChange) * 0.1;
            angles_[i] += angleChange;

            setAngle(i, angles_[i]);
            updateSegmentPositions(i);
        }

        // Calculates the endEffector position again after the changes have been made
        Vector3 endEffectorPos = calculateEndPoint(segments_.size() - 1);

        // Checks to see if endEffector is close enough to the target point
        if ((endEffectorPos - target).length() < 0.1f) {
            break;
        }
    }
}

// CCD Solver using quaternions for rotation in 3D space
// inspiration from: https://codepen.io/zalo/pen/MLBKBv?editors=0010
// Similar way of the 2D CCD
void RobotArm::CCDSolverQ(const Vector3 &target) {

    // CCD Algorithm with max iterations
    for (int iter = 0; iter < 10; ++iter) {
        for (int i = segments_.size() - 1; i >= 0; --i) {
            // Calculate the current direction vector from the segment to the end effector
            Vector3 endEffector = calculateEndPointQ(segments_.size() - 1);

            Vector3 currentPos = segments_[i]->position;
            Vector3 toEndEffector = endEffector - currentPos;

            // Calculate the desired direction vector from the segment to the target
            Vector3 toTarget = target - currentPos;

            // Create a quaternion representing the rotation needed to align the current direction with the desired direction
            Quaternion rotation;
            rotation.setFromUnitVectors(toEndEffector, toTarget);

            // Apply this rotation to the segment's current orientation
            segments_[i]->quaternion = rotation.multiply(segments_[i]->quaternion);
            segments_[i]->quaternion.normalize();

            // Update the positions of the segments
            updateWithQ(i);
        }

        // Calculate the endEffector position again after changes
        Vector3 endEffector = calculateEndPointQ(segments_.size() - 1);

        // Checks to see if endEffector is close enough to the target point
        if ((endEffector - target).length() < 0.1f) {
            break;
        }
    }
}
