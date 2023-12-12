#include "kinematics/RobotArm.hpp"

// Constructor: Initializing the arm
RobotArm::RobotArm(float size, float length) {

    // Creating geometry for each segment
    segmentGeometry_ = BoxGeometry::create(size, size, length);
    segmentGeometry_->translate(0, 0, length/2);

    // Creating material for each segment
    segmentMaterial_ = MeshLambertMaterial::create();
    segmentMaterial_->color = Color::red;

    // Creating spheres for joints
    jointGeometry_ = SphereGeometry::create(size);
    jointMaterial_ = MeshLambertMaterial::create();
    jointMaterial_->color = Color::red;
}

// Updates the number of segments
void RobotArm::updateNumSegments(int numSegments, float size, float length) {

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
        // temp solution
        lengths_.push_back(length);
        sizes_.push_back(size);

        add(newJoint);
        add(newSegment);
    }

    // Removes segments
    while (numSegments < segments_.size()) {
        remove(*segments_.back());
        remove(*joints_.back());

        segments_.pop_back();
        joints_.pop_back();
        lengths_.pop_back();
        sizes_.pop_back();
    }

}

// Gets list of segments
const std::vector<std::shared_ptr<Mesh>> &RobotArm::getSegments() {
    return segments_;
}

// Gets list of joints
const std::vector<std::shared_ptr<Mesh>>& RobotArm::getJoints() {
    return joints_;
}

// Gets list of segment lengths
const std::vector<float>& RobotArm::getLengths() {
    return lengths_;
}