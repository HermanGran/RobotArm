#include "kinematics/RobotArm.hpp"

// Constructor: Initializing the arm
RobotArm::RobotArm() {

    // Creating geometry for each segment
    segmentGeometry_ = BoxGeometry::create(1, 1, 5);
    segmentGeometry_->translate(0, 0, 2);

    // Creating material for each segment
    segmentMaterial_ = MeshLambertMaterial::create();
    segmentMaterial_->color = Color::red;

    // Creating spheres for joints
    jointGeometry_ = SphereGeometry::create();
    jointMaterial_ = MeshLambertMaterial::create();
    jointMaterial_->color = Color::red;
}

// Updates the angles of each segment
void RobotArm::setAngle(int segment, float angle) {
    angles_[segment] = angle;
    segments_[segment]->rotation.z = angles_[segment];
}

// Updates the number of segments
void RobotArm::updateNumSegments(int numSegments) {

    // Adds segments and joints
    while (numSegments > segments_.size()) {
        auto newSegment = Mesh::create(segmentGeometry_, segmentMaterial_);
        auto newJoint = Mesh::create(jointGeometry_, jointMaterial_);

        newSegment->castShadow = true;
        newSegment->receiveShadow = true;
        newJoint->castShadow = true;
        newJoint->receiveShadow = true;

        segments_.push_back(newSegment);
        joints_.push_back(newJoint);
        angles_.push_back(0);

        add(newJoint);
        add(newSegment);
    }

    // Removes segments
    while (numSegments < segments_.size()) {
        remove(*segments_.back());
        remove(*joints_.back());

        segments_.pop_back();
        joints_.pop_back();
        angles_.pop_back();
    }
}

// Calculates the endpoint for the segment given the current position and returns the position
Vector3 RobotArm::calculateEndPoint2D(int segment) {
    // Segment length
    float length = 5;

    Vector3 endPoint = {
            segments_[segment]->position.x + cos(angles_[segment]) * length,
            segments_[segment]->position.y + sin(angles_[segment]) * length,
            segments_[segment]->position.z
    };
    return endPoint;
}

Vector3 RobotArm::calculateEndPoint3D(int segment) {
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
void RobotArm::updateSegmentPositions2D(int segment) {
    for (int i = segment + 1; i < segments_.size(); ++i) {
        segments_[i]->position = calculateEndPoint2D(segment - 1);
    }
}

void RobotArm::updateSegmentPositions3D(int segment) {
    for (int i = segment + 1; i < segments_.size(); ++i) {
        segments_[i]->position = calculateEndPoint3D(i - 1);
    }
    // Updates joint positions
    joints_[segment]->position = segments_[segment]->position;
}

// Cyclic Coordinates Descent for calculating desired angle to target position and iterates over each segment to update
void RobotArm::CCDSolver2D(const Vector3 &target) {
    const float maxAngleChange = 0.05f; // Control the rotation amount per iteration
    const float dampeningFactor = 0.12f;

    // CCD Algorithm: with max iterations
    for (int iter = 0; iter < 10; ++iter) {
        for (int i = segments_.size() - 1; i >= 0; --i) {
            // Calculate the current direction vector from the segment to the end effector
            Vector3 endEffector = calculateEndPoint2D(segments_.size() - 1);
            Vector3 currentPosition = segments_[i]->position;

            // Calculate vectors from current segment to end effector and target
            Vector3 toEndEffector = endEffector - currentPosition;
            Vector3 toTarget = target - currentPosition;

            float desiredAngleDiff = atan2(toTarget.y, toTarget.x) - atan2(toEndEffector.y, toEndEffector.x);

            // Dampening effect for moving smooth created with help from chatGPT
            float angleChange = std::clamp(desiredAngleDiff, -maxAngleChange, maxAngleChange) * dampeningFactor;
            angles_[i] += angleChange;

            setAngle(i, angles_[i]);
            updateSegmentPositions2D(i);
        }

        // Checks to see if endEffector is close enough to the target
        if ((calculateEndPoint2D(segments_.size() - 1) - target).length() < 0.1f) {
            break;
        }
    }
}

// CCD Solver using cross product for finding the axis of rotation in 3D space.
// And dot product for finding the angle of rotation
// Applying rotation using quaternions
// I tried implementing this CCD solver: https://codepen.io/zalo/pen/MLBKBv?editors=0010
// Tried solving using only quaternions but could not wrap my head around how to do so
// Will try getting it to work using only quaternions saving a few videos here for later
// Quaternions: https://www.youtube.com/watch?v=3BR8tK-LuB0
//              https://www.youtube.com/watch?v=-m3tRNy1dzI&t=975s
// Not optimal algorithm, will update
void RobotArm::CCDSolver3D(const Vector3 &target) {
    const float maxAngleChange = 0.05f; // Control the rotation amount per iteration
    const float dampeningFactor = 0.12f; // Reduce the impact of each rotation

    for (int iter = 0; iter < 10; ++iter) {
        for (int i = segments_.size() - 1; i >= 0; --i) {
            // Calculate the current direction vector from the segment to the end effector
            Vector3 endEffector = calculateEndPoint3D(segments_.size() - 1);
            Vector3 currentPosition = segments_[i]->position;

            // Calculate vectors from current segment to end effector and target
            Vector3 toEndEffector = endEffector - currentPosition;
            Vector3 toTarget = target - currentPosition;

            // Calculate the rotation axis (cross product) and angle (dot product)
            Vector3 axisOfRotation = toEndEffector.cross(toTarget);

            // Help from chatGPT for a more smooth movement
            float angle = acos(std::clamp(toEndEffector.dot(toTarget), -maxAngleChange, maxAngleChange));
            angle = std::min(angle, maxAngleChange) * dampeningFactor;

            // Create the quaternion for rotation
            Quaternion rotation;
            rotation.setFromAxisAngle(axisOfRotation, angle);

            // Apply the rotation to the segment
            segments_[i]->quaternion = rotation.multiply(segments_[i]->quaternion);
            segments_[i]->quaternion.normalize();

            // Update positions
            updateSegmentPositions3D(i);
        }

        // Check if end effector is close enough to the target
        if ((calculateEndPoint3D(segments_.size() - 1) - target).length() < 0.1f) {
            break;
        }
    }
}



