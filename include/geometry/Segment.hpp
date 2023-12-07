
#ifndef MAPPEEKSAMEN_SEGMENT_HPP
#define MAPPEEKSAMEN_SEGMENT_HPP

#include "threepp/threepp.hpp"

using namespace threepp;

class Segment {
public:



private:
    std::shared_ptr<BoxGeometry> segmentGeometry_;
    std::shared_ptr<MeshBasicMaterial> segmentMaterial_;

};

#endif //MAPPEEKSAMEN_SEGMENT_HPP
