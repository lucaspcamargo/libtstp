
#include "tstpgeom.h"

geom_f_t TSTPGeomUtils::loadSpaceVar(TSTPSpatialScaleCode spatialScale, uint32_t spaceValue)
{
    switch( spatialScale )
    {
        case TSTP_SSC_HalfMeter8Bit:
            return (geom_f_t) (((geom_f_t)spaceValue) * 0.5);
            
        case TSTP_SSC_OneCentimeter16Bit:
        case TSTP_SSC_OneCentimeter32Bit:
            return (geom_f_t) (((geom_f_t)spaceValue) * 0.01);
            
        case TSTP_SSC_QuarterMeter16Bit:
            return (geom_f_t) (((geom_f_t)spaceValue) * 0.25);
            
        default:
            return spaceValue;
    }
}

geom_f_t TSTPGeomUtils::loadTimeVar(TSTPTemporalScaleCode temporalScale, uint32_t timeValue)
{
    switch( temporalScale )
    {
        case TSTP_TSC_HalfSecond16Bit:
        case TSTP_TSC_HalfSecond32Bit:
            return (geom_f_t) (((geom_f_t)timeValue) * 0.5);
            
        case TSTP_TSC_OneSecond8Bit:
            return ((geom_f_t)timeValue);
            
        case TSTP_TSC_OneMillisecond32Bit:
            return (geom_f_t) (((geom_f_t)timeValue) * 0.001);
            
        default:
            return timeValue;
    }
}
