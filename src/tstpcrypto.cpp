#include "tstpcrypto.h"
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/random.h>
#include <stdio.h>

#include <poly1305aes-20050218/poly1305aes.h>
#include <string.h>

TSTPPoly1305Engine::TSTPPoly1305Engine()
{
    TSTPData256 material;
    
    if(syscall(SYS_getrandom, material, sizeof(material), 0) != sizeof(material))
    {
        perror("TSTPPoly1305Engine::TSTPPoly1305Engine(): getrandom syscall\n");
    }
}

TSTPPoly1305Engine::TSTPPoly1305Engine(const TSTPData256& material)
{
    init( material );
}


TSTPPoly1305Engine::~TSTPPoly1305Engine()
{    
}

void TSTPPoly1305Engine::init(const TSTPData256& material)
{
    
    // static_assert(sizeof(material) == sizeof(m_key));
    
    // fill key with material
    memcpy(&m_key, &material, sizeof(m_key));
    
    poly1305aes_clamp(m_key); // key was generated
    
}

void TSTPPoly1305Engine::authenticate( const void *msg, size_t len, TSTPData128 &auth, const TSTPData128 &nonce )
{
    poly1305aes_authenticate(auth, m_key, nonce, static_cast<const unsigned char*>(msg), len);
}

bool TSTPPoly1305Engine::verify(const void* msg, size_t len, TSTPData128& auth, const TSTPData128& nonce)
{
    return poly1305aes_verify(auth, m_key, nonce, static_cast<const unsigned char*>(msg), len);
}

