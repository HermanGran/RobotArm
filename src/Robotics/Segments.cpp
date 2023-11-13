#include "Kinematics/Segments.hpp"
#include "threepp/threepp.hpp"

Segments::Segments() {}

void Segments::add(Segment2D &segment) {
    segments2D_.push_back(segment);
}

void Segments::add(Segment3D &segment) {
    segments3D_.push_back(segment);
}

std::vector<Segment2D>  Segments::getSegments() {
    return segments2D_;
}

void Segments::updateSegments() {
    for (auto & segment : segments2D_) {
        segment.update();
    }
}

void Segments::CCDSolver(Vector2 &target) {
    int maxIter = 10;
    float threshold = 1e-2f;
    bool solved = false;

    for (int iter = 0; iter < maxIter && !solved; ++ iter) {
        for (int i = segments2D_.size() - 1; i >= 0; --i) {
            Vector2 currentJointPos = segments2D_[i].getStartPos();
            Vector2 endEffectorPos = segments2D_.back().getEndPos();
            Vector2 currentToEndEffector = endEffectorPos - currentJointPos;
            Vector2 currentToTarget = target - currentJointPos;

            float angleToTarget = atan2(currentToTarget.y, currentToTarget.x) - atan2(currentToEndEffector.y, currentToEndEffector.x);

            segments2D_[i].setAngle(angleToTarget);

            for (int j = i; j < segments2D_.size(); ++j) {
                if (j > 0) {
                    segments2D_[j].setStartPos(segments2D_[j - 1].getEndPos());
                }
            }

            if ((segments2D_.back().getEndPos() - target).length() < threshold) {
                solved = true;
                break;
            }
        }
    }
}