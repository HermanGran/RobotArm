#include "kinematics/CCDSolver.hpp"

// Constructor: initializes CCDSolver with an abstract class to make it usable for multiple classes
CCDSolver::CCDSolver(IRobotArm& robotArm) : robotArm(robotArm) {}

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
void CCDSolver::solve(Vector3 &target) {
    const float maxAngleChange = 0.05f; // Control the rotation amount per iteration
    const float dampeningFactor = 0.12f; // Reduce the impact of each rotation

    for (int iter = 0; iter < 10; ++iter) {
        for (int i = robotArm.getSegments().size() - 1; i >= 0; --i) {
            // Calculate the current direction vector from the segment to the end effector
            Vector3 endEffector = getEndEffector();
            Vector3 currentPosition = robotArm.getSegments()[i]->position;

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
            robotArm.getSegments()[i]->quaternion = rotation.multiply(robotArm.getSegments()[i]->quaternion);
            robotArm.getSegments()[i]->quaternion.normalize();

            // Update positions
            updateSegments(i);
        }

        // Check if end effector is close enough to the target
        if ((getEndEffector() - target).length() < 0.1f) {
            break;
        }
    }
}

// Updates positions and orientation for each segment
void CCDSolver::updateSegments(int segment) {
    for (int i = segment + 1; i < robotArm.getSegments().size(); ++i) {
        robotArm.getSegments()[i]->position = calculateEndPos(i - 1);
    }
    // Updates joint positions
    robotArm.getJoints()[segment]->position = robotArm.getSegments()[segment]->position;
}

// Calculates the endpoint for the segment given the current position and returns the position
Vector3 CCDSolver::calculateEndPos(int segment) {

    // The direction forward: Z coordinates
    Vector3 forward(0, 0, 1);
    Vector3 endPos;
    Quaternion world;

    // Get the world position of the segment
    robotArm.getSegments()[segment]->getWorldQuaternion(world);

    // Applies the orientation of the segment to the forward vector
    forward.applyQuaternion(world);

    endPos = (forward * robotArm.getLengths()[segment]) + robotArm.getSegments()[segment]->position;
    return endPos;
}

// Returns endEffector
Vector3 CCDSolver::getEndEffector() {
    return calculateEndPos(robotArm.getSegments().size() - 1);
}