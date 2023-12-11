
#ifndef ROBOTARM_IROBOTARM_HPP
#define ROBOTARM_IROBOTARM_HPP

#include "threepp/threepp.hpp"
#include <vector>

using namespace threepp;

/**
 * IRobotArm is an abstract class that defines the interface for robotic arm CCDSolving.
 * It specifies the basic functionalities that any robotic arm implementation must provide. *
 */
class IRobotArm {
public:

    /**
     * Virtual destructor for the IRobotArm interface
     */
    virtual ~IRobotArm() = default;

    /**
     * Retrieves a list of segments (Mesh objects) that make up the robotic arm.
     * @return A constant reference to a vector of shared pointers to Mesh objects.
     */
    virtual const std::vector<std::shared_ptr<Mesh>>& getSegments() = 0;

    /**
     * Retrieves a list of joints (Mesh objects) that make up the joints for the robotic arm.
     * @return A constant reference to a vector of shared pointers to Mesh objects.
     */
    virtual const std::vector<std::shared_ptr<Mesh>>& getJoints() = 0;

    /**
     * Retrieves the lengths of the segments of the robotic arm.
     * @return A constant reference to a vector of floats representing the lengths of each arm segment.
     */
    virtual const std::vector<float>& getLengths() = 0;

};

#endif //ROBOTARM_IROBOTARM_HPP
