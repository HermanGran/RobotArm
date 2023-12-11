#include "kinematics/RobotArm.hpp"

// Constructor: Initializing the arm
RobotArm::RobotArm(float size, float length) {
    // Creating geometry for each segment
    length_ = length;

    segmentGeometry_ = BoxGeometry::create(size, size, length_);
    segmentGeometry_->translate(0, 0, length_/2);

    // Creating material for each segment
    segmentMaterial_ = MeshLambertMaterial::create();
    segmentMaterial_->color = Color::red;

    // Creating spheres for joints
    jointGeometry_ = SphereGeometry::create(size);
    jointMaterial_ = MeshLambertMaterial::create();
    jointMaterial_->color = Color::red;
}

// Updates the number of segments
void RobotArm::updateNumSegments(int numSegments) {

    // Adds segments and joints
    if (numSegments < 0 ){
        throw std::invalid_argument("Number of segments cannot be negative.");
    }


    while (numSegments > segments_.size()) {
        auto newSegment = Mesh::create(segmentGeometry_, segmentMaterial_);
        auto newJoint = Mesh::create(jointGeometry_, jointMaterial_);

        newSegment->castShadow = true;
        newSegment->receiveShadow = true;
        newJoint->castShadow = true;
        newJoint->receiveShadow = true;

        segments_.push_back(newSegment);
        joints_.push_back(newJoint);

        add(newJoint);
        add(newSegment);
    }


    // Removes segments
    while (numSegments < segments_.size()) {
        remove(*segments_.back());
        remove(*joints_.back());

        segments_.pop_back();
        joints_.pop_back();
    }

}

// Updates the positions for each segment when CCD iterates over
void RobotArm::updateSegmentPositions(int segment) {
    for (int i = segment + 1; i < segments_.size(); ++i) {
        segments_[i]->position = calculateEndPoint(i - 1);
    }
    // Updates joint positions
    joints_[segment]->position = segments_[segment]->position;
}

const std::vector<std::shared_ptr<Mesh>> &RobotArm::getSegments() {
    return segments_;
}

// Calculates the endpoint for the segment given the current position and returns the position
Vector3 RobotArm::calculateEndPoint(int segment) {

    // The direction forward: Z coordinates
    Vector3 forward(0, 0, 1);
    Vector3 endPos;
    Quaternion world;

    // Get the world position of the segment
    segments_[segment]->getWorldQuaternion(world);

    // Applies the orientation of the segment to the forward vector
    forward.applyQuaternion(world);

    endPos = (forward * length_) + segments_[segment]->position;
    return endPos;
}

Vector3 RobotArm::getEndEffector() {
    return calculateEndPoint(segments_.size() - 1);
}


// Cyclic Coordinates Descent for calculating desired angle to target position and iterates over each segment to update
// CCD Solver using cross product for finding the axis of rotation in 3D space.
// And dot product for finding the angle of rotation
// Applying rotation using quaternions
// I tried implementing this CCD solver: https://codepen.io/zalo/pen/MLBKBv?editors=0010
// Tried solving using only quaternions but could not wrap my head around how to do so
// Will try getting it to work using only quaternions saving a few videos here for later
// Quaternions: https://www.youtube.com/watch?v=3BR8tK-LuB0
//              https://www.youtube.com/watch?v=-m3tRNy1dzI&t=975s
// Not optimal algorithm, will update
void RobotArm::CCDSolver(const Vector3 &target) {
    const float maxAngleChange = 0.05f; // Control the rotation amount per iteration
    const float dampeningFactor = 0.12f; // Reduce the impact of each rotation

    for (int iter = 0; iter < 10; ++iter) {
        for (int i = segments_.size() - 1; i >= 0; --i) {
            // Calculate the current direction vector from the segment to the end effector
            Vector3 endEffector = getEndEffector();
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
            updateSegmentPositions(i);
        }

        // Check if end effector is close enough to the target
        if ((getEndEffector() - target).length() < 0.1f) {
            break;
        }
    }
}



