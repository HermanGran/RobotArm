#include "math/Math.hpp"
#include <cmath>

float Math::degToRad(float angle) {
    return angle * (PI / 180);
}

// https://github.com/ekorudiawan/CCD-Inverse-Kinematics-2D/blob/master/sources/CCD-Inverse-Kinematics-2D.py
Eigen::Matrix4d rotateZ(float theta) {
    Eigen::Matrix4d rz;
    rz << cos(theta), -sin(theta), 0, 0,
          sin(theta), cos(theta),  0, 0,
          0,          0,           1, 0,
          0,          0,           0, 1;
    return rz;
}

// https://github.com/ekorudiawan/CCD-Inverse-Kinematics-2D/blob/master/sources/CCD-Inverse-Kinematics-2D.py
Eigen::Matrix4d  Math::translate(float dx, float dy, float dz) {
    Eigen::Matrix4d t;
    t << 1, 0, 0, dx,
         0, 1, 0, dy,
         0, 0, 1, dz,
         0, 0, 0, 1;
    return t;
}


