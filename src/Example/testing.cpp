#include "Kinematics/Segment2D.hpp"
#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"
#include <vector>
#include <iostream>

void CCDSolver2(std::vector<Segment2D>& segments, Vector2& target);

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

        segment1.setEndPos(target);
        segment1.updateGeometry();

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