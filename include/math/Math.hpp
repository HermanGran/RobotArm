#ifndef MAPPEEKSAMEN_MATH_HPP
#define MAPPEEKSAMEN_MATH_HPP

#include <vector>
#include <Eigen/Dense>

namespace Math {

    const float PI = 3.14159265358979323846f;

    // Turns degrees to radians
    float degToRad(float angle);

    //
    Eigen::Matrix4d rotateZ(float theta);
    //
    Eigen::Matrix4d translate(float dx, float dy, float dz);

}

#endif //MAPPEEKSAMEN_MATH_HPP
