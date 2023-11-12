#ifndef MAPPEEKSAMEN_CCDSOLVER_HPP
#define MAPPEEKSAMEN_CCDSOLVER_HPP

#include <vector>
#include "Segment3D.hpp"

class CCDSolver {
public:
    CCDSolver();
    unsigned int size();
    void resize(unsigned int newSize);

    Segment3D& operator[](unsigned int index);
    Segment3D getGLobalTransform(unsigned int index);

    unsigned int getNumStep();
    void setNumSteps(unsigned int numSteps);

    float getthreshold();
    void setThreshold(float value);
    bool Solve(const Segment3D& target);

private:
    float threshold_;
    unsigned int numSteps_;
    std::vector<Segment3D>& segments_;
    Vector3 target_;
};

#endif //MAPPEEKSAMEN_CCDSOLVER_HPP
