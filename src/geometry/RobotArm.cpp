#include "geometry/RobotArm.hpp"

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

    Vector3 forward(0, 0, segment + 1);
    Vector3 endPos;

    forward.applyQuaternion(segments_[segment]->quaternion);
    endPos = forward * length;
    return endPos;
}

// Updates the positions for each segment when CCD iterates over
void RobotArm::updateSegmentPositions(int segment) {
    for (int i = segment + 1; i < segments_.size(); ++i) {
        segments_[i]->position = calculateEndPoint(i - 1);
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

            // The position of the endpoint in the robot arm
            Vector3 endEffector = calculateEndPoint(segments_.size() - 1);

            Vector3 currentPos = segments_[i]->position;
            Vector3 toEndEffector = endEffector - currentPos;
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

// Suppose to be a CCD solver using quaternions, but I found this look at function in the threepp library
// that works well for one segment at least. So i´ll try to implement that in this CCD solver
// Still want to try it using quaternions but that will be for later.
void RobotArm::CCDSolverQ(const Vector3 &target) {
    for (int i = segments_.size() - 1; i >= 0; --i) {
        segments_[i]->lookAt(target);
        updateWithQ(i);
    }
}
