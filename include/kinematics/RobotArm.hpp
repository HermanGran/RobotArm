
#ifndef MAPPEEKSAMEN_ROBOTARM_HPP
#define MAPPEEKSAMEN_ROBOTARM_HPP

#include "threepp/threepp.hpp"
#include "kinematics/IRobotArm.hpp"
#include <vector>

using namespace threepp;

/**
 * RobotArm class manages the segments and joints of a robotic arm
 * It inherits from IRobotArm for CCD functionality and Group for graphic representation
 */
class RobotArm: public IRobotArm, public Group {
public:
    /**
     * Constructor for RobotArm
     * Initializes the arm with size and length
     * @param size Initial size of segment
     * @param length Initial length of segment
     */
    explicit RobotArm();

    /**
     * Updates number and of segments and size of each segment in RobotArm
     * @param numSegments Number of segments for the arm
     */
    void updateNumSegments(int numSegments);

    /**
     * Updates size list with current size (width and height) of each segment
     * Typically used in loops
     * @param segment Index for segment list
     * @param size Current size of segment
     */

    void setSize(int segment, float size);
    /**
     * Updates length list with current size of segments
     * Future plans involve implementing individual size adjustments, therefore using vectors
     * Typically used in loops
     * @param segment Index for segment list
     * @param length Current length of segment
     */
    void setLength(int segment, float length);

    /**
     * Updates size and length of each segment in RobotArm
     * @param size Wanted size of segment
     * @param length Wanted length of segment
     */
    void updateSize(float size, float length);

    // Override methods from IrobotArm
    const std::vector<std::shared_ptr<Mesh>>& getSegments() override;
    const std::vector<std::shared_ptr<Mesh>>& getJoints() override;
    const std::vector<float>& getLengths() override;

private:
    std::vector<std::shared_ptr<Mesh>> segments_;
    std::shared_ptr<BoxGeometry> segmentGeometry_;
    std::shared_ptr<MeshLambertMaterial> segmentMaterial_;

    std::vector<std::shared_ptr<Mesh>> joints_;
    std::shared_ptr<SphereGeometry> jointGeometry_;
    std::shared_ptr<MeshLambertMaterial> jointMaterial_;

    // Future plans for implementing individual size adjustments
    std::vector<float> lengths_;
    std::vector<float> sizes_;
};

#endif //MAPPEEKSAMEN_ROBOTARM_HPP
