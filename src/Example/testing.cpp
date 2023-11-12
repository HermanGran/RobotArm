#include "Kinematics/Segment2D.hpp"
#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"
#include <vector>
#include <iostream>

std::vector<float> getAngles (std::vector<Segment2D>& segments);
std::vector<float> getLengths (std::vector<Segment2D>& segments);

void CCDSolver2(std::vector<Segment2D>& segments, Vector2& target);
void setEndPos(Segment2D& segment, Vector2& target);
void setAngles(std::vector<Segment2D>& segments, float angle);
void CCDSolver(std::vector<Segment2D>& segments, Vector2 target, float threshold, int maxIterations);
int main () {

    Canvas canvas("Kinematics", {{"aa", 4}});
    GLRenderer renderer(canvas.size());

    auto camera = PerspectiveCamera::create();
    camera->position.z = 10;

    auto scene = Scene::create();
    OrbitControls controls{*camera, canvas};

    Vector2 target{};
    ImguiFunctionalContext ui(canvas.windowPtr(), [&] {
        ImGui::SetNextWindowPos({0, 0}, 0, {0, 0});
        ImGui::SetNextWindowSize({230, 0}, 0);
        ImGui::Begin("Demo");
        ImGui::SliderFloat2("position", &target.x, -10.f, 10.f);
        controls.enabled = !ImGui::IsWindowHovered();
        ImGui::End();
    });


    std::vector<Segment2D> segments;

    Segment2D segment1({0, 0}, 0, 3, Color::red);
    Segment2D segment2(segment1, 45, 3, Color::blue);
    Segment2D segment3(segment2, 0, 3, Color::green);

    segments.push_back(segment3);
    segments.push_back(segment2);
    segments.push_back(segment1);


    for (auto & segment : segments) {
        scene->add(segment.getLine());
    }

    std::vector<float> angles = getAngles(segments);
    std::vector<float> lengths = getLengths(segments);


    canvas.animate([&] {
        //CCDSolver2(segments, target);

        //for (auto & segment : segments) {
        //    segment.updateGeometry();
        //}


        setEndPos(segment2, target);
        std::cout << target << "endPos: " << segment2.getEndPos() <<std::endl;

        renderer.render(*scene, *camera);
        ui.render();
    });
}

void CCDSolver (std::vector<Segment2D>& segments) {

}

void CCDSolver2(std::vector<Segment2D>& segments, Vector2& target) {
    int maxIter = 10;
    float threshold = 1e-2f;
    bool solved = false;

    for (int i = 0; i < maxIter && !solved; ++i) {
        for (int j = 0; j < segments.size(); ++j) {
            Vector2 endPoint = segments.front().getEndPos();

            Vector2 VectorToEndPoint{0, 0};

            Vector2 VectorToTarget = target - segments[i].getStartPos();
            if (!(segments[i].getStartPos() == segments.front().getStartPos())) {
                VectorToEndPoint = segments[i].getVector() + segments[i + 1].getVector();

            }

            float angleToTarget = atan2(VectorToTarget.y, VectorToTarget.x) - atan2(VectorToEndPoint.x, VectorToEndPoint.y);

            segments[i].setAngle(angleToTarget);

            for (int k = 0; k < segments.size(); ++k) {
                for (int j = 0; j < segments.size(); j++) {
                    if (segments[i].getStartPos() == segments.back().getStartPos()) {
                        break;
                    }
                    Vector2 startPos = segments[j + 1].getEndPos();
                    segments[j].setStartPos(startPos);
                }
            }


            if ((endPoint - target).length() < threshold) {
                solved = true;
                break;
            }
        }
    }
}

std::vector<float> getAngles(std::vector<Segment2D>& segments) {
    std::vector<float> angles;
    for (const auto & segment : segments) {
        angles.push_back(segment.getAngle());
    }
    return angles;
}

std::vector<float> getLengths(std::vector<Segment2D>& segments) {
    std::vector<float> lengths;
    for (const auto & segment : segments) {
        lengths.push_back(segment.getLen());
    }
    return lengths;
}

void setAngles(std::vector<Segment2D>& segments ,float angle) {
    for (int i = 0; i < segments.size(); i++) {
        segments[i].setAngle(angle);
    }
}

void CCDSolver(std::vector<Segment2D>& segments, Vector2 target, float threshold = 1e-2f, int maxIterations = 10) {
    bool endEffectorCloseEnough = false;

    for (int iter = 0; iter < maxIterations && !endEffectorCloseEnough; ++iter) {
        for (int i = static_cast<int>(segments.size()) - 1; i >= 0; --i) {
            // Calculate vector from the current joint to the end effector
            Vector2 currentJointToEndEffector = segments.back().getEndPos() - segments[i].getEndPos();
            // Calculate vector from the current joint to the target
            Vector2 currentJointToTarget = target - segments[i].getEndPos();

            // Calculate the required rotation angle to align the end effector with the target
            float angle = std::atan2(currentJointToTarget.y, currentJointToTarget.x) - std::atan2(currentJointToEndEffector.y, currentJointToEndEffector.x);

            // Update the segment's angle and apply the rotation
            segments[i].setAngle(segments[i].getAngle() + angle);

            // Check if end effector is close enough to the target
            Vector2 endEffectorPos = segments.back().getEndPos();
            if ((endEffectorPos - target).length() < threshold) {
                endEffectorCloseEnough = true;
                break;
            }
        }
    }
}

void setEndPos(Segment2D& segment, Vector2& target) {
    segment.setEndPos(target);
    segment.updateGeometry();
}