#pragma once

#include "tstptypes.h"
#include "tstpstructs.h"
#include <string.h>


typedef double geom_f_t;

namespace TSTPGeomUtils
{
    geom_f_t loadSpaceVar(TSTPSpatialScaleCode spatialScale, uint32_t spaceValue);
    geom_f_t loadTimeVar(TSTPTemporalScaleCode temporalScale, uint32_t timeValue);
};


/*
 * A location in space-time (x,y,z,t) used in calculations
 */
class TSTPLocationF 
{
public:
    TSTPLocationF()
    {
        bzero(this, sizeof(*this));
    }
    
    template <int SB_BITS, int TB_BITS>
    void load( TSTPSpatialScaleCode spatialScale, TSTPTemporalScaleCode temporalScale, const TSTPLocation<SB_BITS, TB_BITS> &location )
    {
        m_x = TSTPGeomUtils::loadSpaceVar(spatialScale, location.x);
        m_y = TSTPGeomUtils::loadSpaceVar(spatialScale, location.y);
        m_z = TSTPGeomUtils::loadSpaceVar(spatialScale, location.z);
        
        m_t = TSTPGeomUtils::loadTimeVar(temporalScale, location.t);
    }
    
    geom_f_t m_x;
    geom_f_t m_y;
    geom_f_t m_z;
    geom_f_t m_t;
};


/*
 * A region in space-time (x,y,z,r,t,Δt) used in calculations
 */
class TSTPRegionF 
{
public:
    TSTPRegionF()
    {
        bzero(this, sizeof(*this));
    }
    
    template <int SB_BITS, int TB_BITS>
    void load( TSTPSpatialScaleCode spatialScale, TSTPTemporalScaleCode temporalScale, const TSTPRegion<SB_BITS, TB_BITS> &region )
    {
        m_x = TSTPGeomUtils::loadSpaceVar(spatialScale, region.x);
        m_y = TSTPGeomUtils::loadSpaceVar(spatialScale, region.y);
        m_z = TSTPGeomUtils::loadSpaceVar(spatialScale, region.z);
        m_r = TSTPGeomUtils::loadSpaceVar(spatialScale, region.r);
        
        m_t = TSTPGeomUtils::loadTimeVar(temporalScale, region.t);
        m_delta_t = TSTPGeomUtils::loadTimeVar(temporalScale, region.delta_t);
    }
    
    bool collides(const TSTPRegionF &other)
    {
        // check time overlap
        geom_f_t thisEnd = m_t + m_delta_t;
        geom_f_t otherEnd = other.m_t + other.m_delta_t;
        if( this->m_t < otherEnd && thisEnd > other.m_t )
        {
            // there is a time overlap
            // now check for spatial overlap
            geom_f_t dx = m_x - other.m_x;
            geom_f_t dy = m_y - other.m_y;
            geom_f_t dz = m_z - other.m_z;
            geom_f_t dist_sq = dx*dx + dy*dy + dz*dz;
            
            geom_f_t rr = m_r + other.m_r;
            return dist_sq < (rr*rr);
        }
        else return false;
    }
    
    bool contains(const TSTPLocationF &loc)
    {
        if(this->m_t <= loc.m_t && (this->m_t + this->m_delta_t) > loc.m_t)
        {
            // inside alloted time
            geom_f_t dx = m_x - loc.m_x;
            geom_f_t dy = m_y - loc.m_y;
            geom_f_t dz = m_z - loc.m_z;
            geom_f_t dist_sq = dx*dx + dy*dy + dz*dz;
            
            return dist_sq <= (m_r * m_r);
        }
        else return false;
    }
    
    geom_f_t m_x;
    geom_f_t m_y;
    geom_f_t m_z;
    geom_f_t m_r;
    geom_f_t m_t;
    geom_f_t m_delta_t;
};
