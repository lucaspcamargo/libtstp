#pragma once

class TSTPMedia;

class TSTPEngine 
{
public:
    enum TSTPEngineState
    {
        // initialization states
        ST_INIT,        // engine is initializing, not ready for use
        ST_WAIT_MEDIA,  // engine is waiting on the media to become available
        
        // bootstrap states
        ST_LOCATING,    // initializing location estimation
        ST_CLOCKSYNC,   // synchronizing clock
        ST_SECURITYBOOT,// initializing security measures (msg auth codes)
        ST_REPORTING,   // reporting measurement capabilities to the sink
        
        // runtime states
        ST_READY,       // engine is running correctly
        ST_ERROR        // an error was found, execution compromised
    };
    
    
    TSTPEngine( TSTPMedia &media );
    
private:
    TSTPEngineState *m_state;
    TSTPMedia *m_media;
};
