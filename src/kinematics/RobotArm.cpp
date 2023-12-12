#include "kinematics/RobotArm.hpp"

// Constructor: Initializing the arm
RobotArm::RobotArm() {

    // Creating geometry for each segment
    segmentGeometry_ = BoxGeometry::create();
    //segmentGeometry_->translate(0, 0, length/2);

    // Creating material for each segment
    segmentMaterial_ = MeshLambertMaterial::create();
    segmentMaterial_->color = Color::red;

    // Creating spheres for joints
    jointGeometry_ = SphereGeometry::create(0.5);
    jointMaterial_ = MeshLambertMaterial::create();
    jointMaterial_->color = Color::red;
}

// Updates the number of segments
void RobotArm::updateNumSegments(int numSegments) {

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
        lengths_.push_back(0);
        sizes_.push_back(0);

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

// Updates size of segments in size list
void RobotArm::setSize(int segment, float size)  {
    sizes_[segment] = size;
}

// Updates length of segments in length list
void RobotArm::setLength(int segment, float length) {
    lengths_[segment] = length;
}

// Updates size and length of segments in RobotArm
void RobotArm::updateSize(float size, float length) {
    for (int i = 0; i <= segments_.size() - 1; i++) {
        setSize(i, size);
        setLength(i, length);

        // Updates geometry with new size and length
        segmentGeometry_ = BoxGeometry::create(size, size, length);
        segmentGeometry_->translate(0, 0, length/2);

        // Also updates joint size
        segments_[i]->setGeometry(segmentGeometry_);
        jointGeometry_ = SphereGeometry::create(size);
        joints_[i]->setGeometry(jointGeometry_);
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