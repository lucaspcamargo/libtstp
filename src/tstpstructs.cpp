#include "tstpstructs.h"

#include <string.h>
#include <assert.h>

TSTPUnit::TSTPUnit()
{
    bzero(&m_data, sizeof(m_data)); // initialize as digital with clear fields
}

TSTPUnit::TSTPUnit(TSTPDimSI dimension, int exponent)
{
    
    bzero(&m_data, sizeof(m_data)); // initialize as digital with clear fields
    m_data.si.si_flag = 1;
    
    int bits = exponent + 4;    
    assert(!(bits & ~7)); // make sure exponent is not out of range
    
    assert(dimension);
    switch(dimension)
    {
        case TSTP_DIM_A:
            m_data.si.exp_A = bits;
            break;
        case TSTP_DIM_cd:
            m_data.si.exp_cd = bits;            
            break;
        case TSTP_DIM_K:
            m_data.si.exp_K = bits;
            break;
        case TSTP_DIM_kg:
            m_data.si.exp_kg = bits;    
            break;
        case TSTP_DIM_m:
            m_data.si.exp_m = bits;    
            break;
        case TSTP_DIM_mol:
            m_data.si.exp_mol = bits;    
            break;
        case TSTP_DIM_rad:
            m_data.si.exp_rad = bits;    
            break;
        case TSTP_DIM_s:
            m_data.si.exp_s = bits;    
            break;
        case TSTP_DIM_sr:
            m_data.si.exp_sr = bits;    
            break;
        default:
            assert(0);
    }
    
}

#define ADD_EXP(UNIT) result.m_data.si.exp_##UNIT = 4 + ((this->m_data.si.exp_##UNIT - 4) + (u.m_data.si.exp_##UNIT - 4))
#define SUB_EXP(UNIT) result.m_data.si.exp_##UNIT = 4 + ((this->m_data.si.exp_##UNIT - 4) - (u.m_data.si.exp_##UNIT - 4))

TSTPUnit TSTPUnit::operator*(TSTPUnit& u)
{
    TSTPUnit result;
    
    assert(! (this->isDigital() || u.isDigital()) );
    
    ADD_EXP(sr);
    ADD_EXP(rad);
    ADD_EXP(m);
    ADD_EXP(kg);
    ADD_EXP(s);
    ADD_EXP(A);
    ADD_EXP(K);
    ADD_EXP(mol);
    ADD_EXP(cd);
    
    return result;
}

TSTPUnit TSTPUnit::operator/(TSTPUnit& u)
{
    TSTPUnit result;
    
    assert(! (this->isDigital() || u.isDigital()) );
    
    SUB_EXP(sr);
    SUB_EXP(rad);
    SUB_EXP(m);
    SUB_EXP(kg);
    SUB_EXP(s);
    SUB_EXP(A);
    SUB_EXP(K);
    SUB_EXP(mol);
    SUB_EXP(cd);
    
    return result;
}

#undef ADD_EXP
#undef SUB_EXP
