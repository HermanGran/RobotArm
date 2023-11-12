#include "threepp/threepp.hpp"
#include "Kinematics/Segment2D.hpp"
#include <vector>
#include "math/Math.hpp"
#include "MouseListener.hpp"
using namespace threepp;



int main () {
    Canvas canvas("ROBOTICS", {{"aa", 4}});
    canvas.setSize({1000, 1000});
    GLRenderer renderer(canvas.size());

    auto scene = Scene::create();

    auto camera = PerspectiveCamera::create();
    camera->position.z = 30;


    Segment2D segment1({0, 0}, 0, 5, Color::green);
    Segment2D segment2(segment1, 45, 5, Color::red);
    Segment2D segment3(segment2,45 , 5, Color::purple);

    // Segment lengths
    std::vector<float> link;
    link.push_back(segment1.getLen());
    link.push_back(segment2.getLen());
    link.push_back(segment2.getLen());

    // Segment angles
    std::vector<float> angles;
    angles.push_back(segment1.getAngle());
    angles.push_back(segment2.getAngle());

    scene->add(segment1.getLine());
    scene->add(segment2.getLine());


    bool isMouseClicked = false;
    Vector2 mousePos;

    MyMouseListener ml(isMouseClicked, mousePos);
    canvas.addMouseListener(&ml);

    Vector2 mouse{-Infinity<float>, -Infinity<float>};
    MouseMoveListener l([&](auto& pos) {
        auto size = canvas.size();
        mouse.x = (pos.x / static_cast<float>(size.width)) * 2 - 1;
        mouse.y = -(pos.y / static_cast<float>(size.height)) * 2 + 1;
    });
    canvas.addMouseListener(&l);

    Clock clock;
    canvas.animate([&] {
        if (isMouseClicked) {
            auto size = canvas.size();
            mousePos.x = (mouse.x / static_cast<float>(size.width)) * 2 - 1;
            mousePos.y = -(mouse.y / static_cast<float>(size.height)) * 2 + 1;
        }



        renderer.render(*scene, *camera);
    });
}

void CCDSolver (std::vector<Segment2D>& segments) {

}

std::vector<float> getAngles (std::vector<Segment2D>& segments) {
    std::vector<float> angles;
    int segment = 0;
    for (segment = 0; segment <= segments.size(); ++segment) {
        angles.push_back(segments[segment].getAngle());
    }


    return angles;
}



























// https://github.com/ekorudiawan/CCD-Inverse-Kinematics-2D/blob/master/sources/CCD-Inverse-Kinematics-2D.py
std::vector<Eigen::Matrix4d> FK(const std::vector<double>& angle, const std::vector<double>& link) {
    size_t n_links = link.size();
    std::vector<Eigen::Matrix4d> P;
    P.push_back(Eigen::Matrix4d::Identity());

    for (size_t i = 0; i < n_links; ++i) {
        Eigen::Matrix4d R = Math::rotateZ(Math::degToRad(angle[i]));
        Eigen::Matrix4d T = Math::translate(link[i], 0, 0);
        P.push_back(P.back() * R * T);
    }
    return P;
}


// Assuming FK function is already defined and returns std::vector<Eigen::Matrix4d>
std::vector<Eigen::Matrix4d> FK(const std::vector<float>& angle, const std::vector<float>& link);

std::tuple<std::vector<double>, double, bool, int> IK(
        const Eigen::Vector3d& target,
        std::vector<double>& angle,
        const std::vector<double>& link,
        int max_iter = 10000,
        double err_min = 0.1) {

    bool solved = false;
    double err_end_to_target = std::numeric_limits<double>::infinity();

    int loop = 0;
    for (loop = 0; loop < max_iter; ++loop) {
        for (int i = angle.size() - 1; i >= 0; --i) {
            auto P = FK(angle, link);
            Eigen::Vector3d end_to_target = target - P.back().block<3, 1>(0, 3);
            err_end_to_target = end_to_target.norm();
            if (err_end_to_target < err_min) {
                solved = true;
                break;
            } else {
                Eigen::Vector3d cur_to_end = P.back().block<3, 1>(0, 3) - P[i].block<3, 1>(0, 3);
                double cur_to_end_mag = cur_to_end.norm();
                Eigen::Vector3d cur_to_target = target - P[i].block<3, 1>(0, 3);
                double cur_to_target_mag = cur_to_target.norm();

                double end_target_mag = cur_to_end_mag * cur_to_target_mag;

                double cos_rot_ang, sin_rot_ang;
                if (end_target_mag <= 0.0001) {
                    cos_rot_ang = 1;
                    sin_rot_ang = 0;
                } else {
                    cos_rot_ang = cur_to_end.dot(cur_to_target) / end_target_mag;
                    sin_rot_ang = cur_to_end(0) * cur_to_target(1) - cur_to_end(1) * cur_to_target(0) / end_target_mag;
                }

                double rot_ang = acos(std::max(-1.0, std::min(1.0, cos_rot_ang)));

                if (sin_rot_ang < 0.0) {
                    rot_ang = -rot_ang;
                }

                angle[i] += Math::degToRad(rot_ang);

                if (angle[i] >= 360) {
                    angle[i] -= 360;
                }
                if (angle[i] < 0) {
                    angle[i] += 360;
                }
            }
        }

        if (solved) {
            break;
        }
    }

    return std::make_tuple(angle, err_end_to_target, solved, loop);
}