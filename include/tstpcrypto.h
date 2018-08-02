#pragma once

#include "tstptypes.h"

typedef uint8_t TSTPData128[16];
typedef uint8_t TSTPData256[32];

class TSTPPoly1305Engine
{
    
public:
    TSTPPoly1305Engine();
    TSTPPoly1305Engine( const TSTPData256 &material );
    
    ~TSTPPoly1305Engine();

    void authenticate( const void *msg, size_t len, TSTPData128 &auth, const TSTPData128 &nonce );    
    bool verify( const void *msg, size_t len, TSTPData128 &auth, const TSTPData128 &nonce );
    
private:
    void init( const TSTPData256 &material );
    
    TSTPData256 m_key;
};
