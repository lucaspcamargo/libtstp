#pragma once

#include "tstpstructs.h"

class TSTPApplication 
{
public:
    
    struct ReadingCapability
    {
        TSTPUnits units;
        float resolution;
        uint8_t precision;
    };
    
    virtual void getReadingCapabilityCount() = 0;
    virtual ReadingCapability getReadingCapability() = 0;
    
};
