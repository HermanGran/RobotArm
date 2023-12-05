#include "Kinematics/CCDSolver.hpp"

CCDSolver::CCDSolver(int maxIter, float threshold)
: maxIter_(maxIter), threshold_(threshold) {}


void CCDSolver::solve(std::vector<Segment2D>& segments,const Vector2& target) {
    bool solved = false;
    Vector2 endEffectorPos;
    Vector2 targetVector;
    Vector2 endEffectorVector;
    float angleDifference;

    for (int iter = 0; iter < maxIter_ && !solved; ++iter) {
        endEffectorPos = segments.back().getEndPos();

        for(int i = segments.size() - 1; i >= 0; i--) {
            targetVector = target - segments[i].getStartPos();
            endEffectorVector = endEffectorPos - segments[i].getStartPos();

            angleDifference = atan2(targetVector.y, targetVector.x) - atan2(endEffectorVector.y, endEffectorVector.x);

            segments[i].rotateAroundStartPoint(segments[i].getAngle() + angleDifference);

            // Updates the start position of each segment

            for (int j = 0; j < segments.size(); ++j) {
                if (j > 0) {
                    //segments[j].setStartPos(segments[j - 1].getEndPos());
                    segments[j].update(segments[j - 1]);
                }
            }

            // Check if the end effector is close enough to the target
            endEffectorPos = segments.back().getEndPos();
            if ((endEffectorPos - target).length() <= threshold_) {
                solved = true;
                break;
            }
        }
    }
}

void CCDSolver::solve(std::vector<Group> &segments, const Vector3 &target) {

    for (auto i = segments.size() - 1; i >= 0; i--) {
        segments[i].updateMatrixWorld();

    }
}