#pragma once

#include "tstptypes.h"

/** 
 * @file tstpstructs.h
 * @brief TSTP Main Structures
 * @authors "Lucas Pires Camargo" <camargo@lisha.ufsc.br>
 */


/** Main reference: see D. Resner and A. A. Fröhlich, "Design rationale of a 
 * cross-layer, Trustful Space-Time Protocol for Wireless Sensor Networks," 
 * 2015 IEEE 20th Conference on Emerging Technologies & Factory Automation 
 * (ETFA), Luxembourg, 2015, pp. 1-8. doi: 10.1109/ETFA.2015.7301413 
 * 
 * HOWEVER, the de-facto implementation in EPOS changed since the publication
 * of the paper, especially the format used for describing numbers and units.
 * 
 * This implementation aims for compatibility with the implementation in EPOS.
 * Therefore, it differs from the paper spec a bit.
 * 
 * See epos2/include/tstp.h
 */ 



// Basic flag definitions

enum TSTPMessageType
{
    TSTP_MT_Interest    = 0b000,    
    TSTP_MT_Data        = 0b001,    
    TSTP_MT_Report      = 0b010,    
    TSTP_MT_Reserved    = 0b011,    
    TSTP_MT_Bootstrap0    = 0b100,  
    TSTP_MT_Bootstrap1    = 0b101,  
    TSTP_MT_Bootstrap2    = 0b110,  
    TSTP_MT_Bootstrap3    = 0b111,
    TSTP_MT_Bootstrap_Bit    = 0b100  
};

enum TSTPSpatialScaleCode
{
    TSTP_SSC_HalfMeter8Bit = 0b00,      // up to 127.5m
    TSTP_SSC_OneCentimeter16Bit = 0b01, // up to 655.3 m
    TSTP_SSC_QuarterMeter16Bit = 0b10,  // up to 16382.5 m
    TSTP_SSC_OneCentimeter32Bit = 0b11  // up to 42949.6 m
};

enum TSTPTemporalScaleCode
{
    TSTP_TSC_OneSecond8Bit = 0b00,        // up to 4.25 minutes
    TSTP_TSC_HalfSecond16Bit = 0b01,      // up to 9.1 hours
    TSTP_TSC_OneMillisecond32Bit = 0b10,  // up to 49 days
    TSTP_TSC_HalfSecond32Bit = 0b11       // up to 69 years
};

enum TSTPResponseMode
{
    TSTP_RM_AllReply = 0b0,     // all nodes (on the region of interest) reply
    TSTP_RM_OneReply = 0b1      // only a single reply is sufficient
};


enum TSTPDimSI
{
    TSTP_DIM_NONE, // no unit value
    TSTP_DIM_sr,   // steradian
    TSTP_DIM_rad,  // radian
    TSTP_DIM_m,    // meter
    TSTP_DIM_kg,   // kilogram
    TSTP_DIM_s,    // second
    TSTP_DIM_A,    // Ampère
    TSTP_DIM_K,    // Kelvin
    TSTP_DIM_mol,  // mole
    TSTP_DIM_cd    // candela
};

enum TSTPNumberType
{
    TSTP_NUM_I32 = 0b00,   // 32-bit integer, big-endian
    TSTP_NUM_I64 = 0b01,   // 64-bit integer, big-endian
    TSTP_NUM_F32 = 0b10,   // 32-bit float, big-endian
    TSTP_NUM_D64 = 0b11    // 64-bit double, big-endian 
};

enum TSTPNumberMode
{
    TSTP_MOD_DIR = 0b00,       // use units as expressed
    TSTP_MOD_DIV = 0b01,       // adimensional number that expreses ratio of U/U
    TSTP_MOD_LOG = 0b10,       // natural logarithm of actual value
    TSTP_MOD_LOG_DIV = 0b11,   // natural logarithm of adimensional U/U ratio
};



// Immutable data structures

// unit exponents, in transport format
class TSTPUnit  
{
    
public:
    
    union
    {
        struct
        {
            unsigned si_flag: 1; // wether this is SI units, BIT IS CLEARED
            unsigned dig_num_type: 15; // type of number, no documentation found
            unsigned dig_num_selector: 16;  // application-specific
        } digital;
        
        struct
        {
            unsigned si_flag: 1; // wether the number is in SI units, BIT IS SET
            unsigned num_type: 2; // type of number, see TSTP_NUM_*
            unsigned num_mod: 2;  // unit encoding, see TSTP_MOD_*
            unsigned exp_sr: 3;   
            unsigned exp_rad: 3;   
            unsigned exp_m: 3;    
            unsigned exp_kg: 3;  // ! The exp_* fields are exponents for units,
            unsigned exp_s: 3;   //   plus four, so the value range is -4 to 3,
            unsigned exp_A: 3;   //   stored as [0; 7] (3 unsigned bits)
            unsigned exp_K: 3;
            unsigned exp_mol: 3;
            unsigned exp_cd: 3;
        } si;
    } m_data;
    
    TSTPUnit();
    TSTPUnit( TSTPDimSI dimension, int exponent );
    
    TSTPUnit operator*( TSTPUnit &u );
    TSTPUnit operator/( TSTPUnit &u );
    
    bool isDigital() { return ! m_data.digital.si_flag; }
    bool isSI() { return m_data.si.si_flag; }
   
    
    // provide a means to statically obtain a datatype from a TSTPNumberType    
    template <int NUM_TYPE>
    struct Type {
        typedef void TYPE;
        static const size_t SIZE = 0;
    };    
};

template <> struct TSTPUnit::Type< TSTP_NUM_I32 > {  // specialization
    typedef uint32_t TYPE;
    static const size_t SIZE = sizeof(TYPE);
};    
template <> struct TSTPUnit::Type< TSTP_NUM_I64 > {  // specialization
    typedef uint64_t TYPE;
    static const size_t SIZE = sizeof(TYPE);
};    
template <> struct TSTPUnit::Type< TSTP_NUM_F32 > {  // specialization
    typedef float TYPE;
    static const size_t SIZE = sizeof(TYPE);
};    
template <> struct TSTPUnit::Type< TSTP_NUM_D64 > {  // specialization
    typedef double TYPE;
    static const size_t SIZE = sizeof(TYPE);
};


// Generic location
template <int SB_BITS, int TB_BITS>
struct TSTPLocation
{
    unsigned x: SB_BITS; // cartesian x
    unsigned y: SB_BITS; // cartesian y
    unsigned z: SB_BITS; // cartesian z
    unsigned t: TB_BITS; // timestamp
};

// Generic region
template <int SB_BITS, int TB_BITS>
struct TSTPRegion
{
    unsigned x: SB_BITS; // cartesian x
    unsigned y: SB_BITS; // cartesian y
    unsigned z: SB_BITS; // cartesian z
    unsigned r: SB_BITS; // cartesian radius
    unsigned t: TB_BITS; // timestamp
    unsigned delta_t: TB_BITS; // time delta (like a time radius)
};


template <int SB_BITS, int TB_BITS>
struct TSTPHeader
{
    unsigned msg_type: 3;
    unsigned time_request: 1;
    unsigned spatial_sc: 2;
    unsigned temporal_sc: 2;
    unsigned location_confidence: 8;
    
    TSTPLocation<SB_BITS, TB_BITS> last_hop;
    TSTPLocation<SB_BITS, TB_BITS> origin;
    
    unsigned location_deviation: 32;
};


template <int SB_BITS, int TB_BITS>
struct TSTPMsgInterest
{
    TSTPRegion<SB_BITS, TB_BITS> region;
    unsigned period: TB_BITS;
    TSTPUnit units;
    unsigned precision: 7;
    TSTPResponseMode responseMode: 1;
};


// Default types for simplifying API
typedef TSTPLocation<32, 32> TSTPLocation32;
typedef TSTPLocation<32, 32> TSTPRegion32;
typedef TSTPHeader<32, 32> TSTPHeader32;
typedef TSTPMsgInterest<32, 32> TSTPMsgInterest32;


