#pragma once

#include "tstptypes.h"

class TSTPMediaListener;


/**
 * TSTPMedia represents the media over which 
 * the TSTP Protocol can communicate.
 * Can be a 802.15.4 implementation, or a
 * layer over raw rf access provided by an OS
 */
class TSTPMedia
{
public:
  
    virtual void poll() = 0;
    
    virtual void register_listener(TSTPMediaListener * listener) = 0;
    virtual void unregister_listener(TSTPMediaListener * listener) = 0;
    
    virtual void send_preamble(void *data, size_t len) = 0;
    virtual void send_message(void *data, size_t len) = 0;
};


/**
 * TSTPMediaListener is a listener class for 
 * communications media. It receives available
 * messages for processing, in order of arrival.
 */
class TSTPMediaListener
{
public:
    virtual void preamble_received(void *data, size_t len) = 0;
    virtual void message_received(void *data, size_t len) = 0;    
};


/**
 * TSTPDummyMedia is a media implementation
 * which doesn't do anything. Used for 
 * testing
 */
class TSTPDummyMedia : public TSTPMedia
{
public:
    void poll() override {}
    
    void register_listener(TSTPMediaListener *) override {}
    void unregister_listener(TSTPMediaListener *) override {}
    
    void send_preamble(void *data, size_t len) override {}
    void send_message(void *data, size_t len) override {}
    
};

