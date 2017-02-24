/*
 * --- License -------------------------------------------------------------- *
 */

/*
 * Copyright (c) 2015
 *
 * Hochschule Offenburg, University of Applied Sciences
 * Institute for reliable Embedded Systems
 * and Communications Electronic (ivESK)
 *
 * All rights reserved
*/

/*
 * --- Module Description --------------------------------------------------- *
 */

/**
 * \file    LWM2MServer.h
 * \author  Institute of reliable Embedded Systems
 *          and Communication Electronics
 * \date    $Date$
 * \version $Version$
 *
 * \brief   Description of a LWM2M Server.
 *
 */


#ifndef __LWM2MSERVER_H__
#define __LWM2MSERVER_H__
#ifndef __DECL_LWM2MSERVER_H__
#define __DECL_LWM2MSERVER_H__ extern
#endif /* #ifndef __DECL_LWM2MSERVER_H__ */


/*
 * --- Includes ------------------------------------------------------------- *
 */
#include <stdint.h>
#include <iostream>
#include <string>
#include <map>
#include "liblwm2m.h"
#include "connection.h"
#include "LWM2MResourceObserver.h"

#ifdef OPCUA_LWM2M_SERVER_USE_THREAD
#include <pthread.h>
#endif /* #ifdef OPCUA_LWM2M_SERVER_USE_THREAD */

/*
 * --- Forward Declaration ----------------------------------------------------- *
 */

/* Forward declaration of the LWM2MDevice class. */
class LWM2MDevice;
/* Forward declaration of the LWM2MObject class. */
class LWM2MObject;
/* Forward declaration of the LWM2MResource class. */
class LWM2MResource;

/*
 * --- Class Definition ----------------------------------------------------- *
 */

/**
 * \brief   LWM2MServer Class.
 *
 *          A LWM2M Server class represents an object of a wakaama LWM2M
 *          server. It provides an according class interface that allows
 *          to control the LWM2M functionality.
 */
class LWM2MServer
{
    friend class LWM2MDevice;

public:

    /**
     * User data used for callbacks.
     */
    struct s_cbparams_t
    {
        /* pinter to the resource instance */
        const LWM2MResource* p_res;
        /* LWM2M parameters */
        s_lwm2m_resobsparams_t lwm2mParams;
    };

public:

    /**
     * \brief   Default Constructor to create a LWM2M Server.
     */
    LWM2MServer( void )
        : m_sock( -1 )
        , m_port( LWM2M_STANDARD_PORT_STR )
        , m_addrFam( AF_INET6 )
        , mp_connList( NULL )
        , mp_lwm2mH( NULL )
        , mp_cbUserData( NULL ) {

#ifdef OPCUA_LWM2M_SERVER_USE_THREAD
        pthread_mutexattr_t attr;
        pthread_mutexattr_init( &attr );
        pthread_mutexattr_settype( &attr, PTHREAD_MUTEX_RECURSIVE );

        /* initialize the mutex */
        pthread_mutex_init( &m_mutex, &attr );

        m_thread = 0;
        m_threadRun = false;

#endif /* #ifdef OPCUA_LWM2M_SERVER_USE_THREAD */
    };


    /**
     * \brief   Extended Constructor to create a LWM2M Server.
     *
     * \param    port        Port to use for the connection.
     * \param    addrFam        Address family to use (IPv4/IPv6)
     */
    LWM2MServer( uint16_t port, int addrFam )
        : m_sock( -1 )
        , m_port( LWM2M_STANDARD_PORT_STR )
        , m_addrFam( AF_INET6 )
        , mp_connList( NULL )
        , mp_lwm2mH( NULL )
        , mp_cbUserData( NULL ) {

#ifdef OPCUA_LWM2M_SERVER_USE_THREAD
        pthread_mutexattr_t attr;
        pthread_mutexattr_init( &attr );
        pthread_mutexattr_settype( &attr, PTHREAD_MUTEX_RECURSIVE );

        /* initialize the mutex */
        pthread_mutex_init( &m_mutex, &attr );

        m_thread = 0;
        m_threadRun = false;

#endif /* #ifdef OPCUA_LWM2M_SERVER_USE_THREAD */
    };


    /**
     * \brief   Default Destructor of the LWM2M Server.
     */
    virtual ~LWM2MServer( void );


    /**
     * \brief   Start the LWM2M Server.
     *
     *          Must be called in order to start the LWM2M Server. It creates
     *          the according socket connections and starts the LWM2M context.
     *          Existing connections will be closed.
     *
     * \return  0 on success.
     */
    int16_t startServer( void );


    /**
     * \brief   Stop the LWM2M Server.
     *
     *          Closes existing socket connections and deletes active LWM2M
     *          contexts.
     *
     * \return  0 on success.
     */
    int16_t stopServer( void );


    /**
     * \brief   Run the LWM2M Server.
     *
     *          This function must be called periodically. It checks the open
     *          connection for data and handles LWM2M specific parts.
     *
     * \return  0 on success.
     */
    int16_t runServer( void );


    /**
     * \brief   Checks if the server has a client with a specific name.
     *
     *          Any client that registers at the server is known as long
     *          as its lifetime is not expired. Therefore, this function
     *          returns true as long as a client is valid.
     *
     * \return  true if the client is know.
     */
    bool hasDevice( std::string client );


    /**
     * \brief   Read a resources value.
     *
     * \param   p_res The resource to read the value from.
     * \param   val   Value reference to write the value to.
     *
     * \return  0 on success or negative value on error.
     */
    int8_t read( const LWM2MResource* p_res, std::string& val,
            s_cbparams_t* p_cbParams );


    /**
     * \brief   Write a resources value.
     *
     * \param   p_res   The resource to write the value to.
     * \param   val     Value to set for the resource.
     *
     * \return  0 on success or negative value on error.
     */
    int8_t write( const LWM2MResource* p_res, const std::string& val,
            s_cbparams_t* p_cbParams );


    /**
     * \brief   Observe a resources value.
     *
     * \param   p_res     The resource to observe.
     * \param   observe   Defines if the value shall be observed or not.
     *
     * \return  0 on success or negative value on error.
     */
    int8_t observe( const LWM2MResource* p_res, bool observe,
            s_cbparams_t* p_cbParams );


    /**
     * \brief   Execute a resource.
     *
     * \param   p_res   The resource to execute.
     *
     * \return  0 on success or negative value on error.
     */
    int8_t execute( const LWM2MResource* p_res,
            s_cbparams_t* p_cbParams );


    /**
     * \brief   Get the begin of the registered devices.
     *
     * \return  Iterator pointing to the begin of the devices.
     */
    std::map< std::string, LWM2MDevice* >::iterator deviceStart( void ) {
        return m_devMap.begin();
    };


    /**
     * \brief   Get the end of the registered devices.
     *
     * \return  Iterator pointing to the end of the devices.
     */
    std::map< std::string, LWM2MDevice* >::iterator deviceEnd( void ) {
        return m_devMap.end();
    };


protected:

    /**
     * \brief   Get the device structure of a specific device.
     *
     *          The LWM2M server class is a wrapper around the actual
     *          LWM2M implementation. This function returns the original
     *          structure of a LWM2M device from the LWM2M implementation
     *          point f view.
     *
     * \return  Pointer to the device structure on success or NULL on error.
     */
    lwm2m_client_t* getDevice( std::string client );


private:

    /**
     * \brief   Checks if the server is running.
     *
     *          This functions uses the internal variables such as the
     *          socket and LWM2M context to check if the server is alive.
     *
     * \return  true if the server is alive.
     */
    bool isAlive( void ) const {
        return ( (m_sock != -1) && (mp_lwm2mH != NULL) );
    };


    /**
     * \brief   Callback used to indicate if any action happened for a client.
     *
     *          This function indicates several events e.g. if a new
     *          device was registered or deregistered.
     *
     * \param   clientID    The internal device ID of the monitored event.
     * \param   uriP        The URI the event belongs to.
     * \param   status      Status of the event.
     * \param   format      Format of the data included.
     * \param   data        Data that was included in the event.
     * \param   dataLength  Length of the data.
     * \param   userData    User data pointer specified when the function was
     *                      registered.
     */
    static void monitorCb( uint16_t clientID, lwm2m_uri_t * uriP, int status,
            lwm2m_media_type_t format, uint8_t * data, int dataLength,
            void * userData );



    /**
     * \brief   Callback used to indicate e.g result of read write or observe.
     *
     *          This function indicates several events e.g. the result of
     *          a read write or when observing a value.
     *
     * \param   clientID    The internal device ID of the monitored event.
     * \param   uriP        The URI the event belongs to.
     * \param   status      Status of the event.
     * \param   format      Format of the data included.
     * \param   data        Data that was included in the event.
     * \param   dataLength  Length of the data.
     * \param   userData    User data pointer specified when the function was
     *                      registered.
     */
    static void notifyCb( uint16_t clientID, lwm2m_uri_t * uriP, int status,
            lwm2m_media_type_t format, uint8_t * data, int dataLength,
            void * userData );

#ifdef OPCUA_LWM2M_SERVER_USE_THREAD

    /**
     * \brief   Thread Function.
     */
    static void* threadEntryFunc( void* p_arg ) {
        /* run the Server */
        int ret = 0;
        while( (p_arg != NULL) && (ret == 0))
            ret = ((LWM2MServer*)p_arg)->runServer();
        return NULL;
    }
#endif /* #ifdef OPCUA_LWM2M_SERVER_USE_THREAD */


private:

    /** Socket descriptor used for the server connection */
    int m_sock;

    /** port of the server data connection */
    std::string m_port;

    /** address family to use */
    int m_addrFam;

    /** connection list */
    connection_t* mp_connList;

    /** LWM2M context */
    lwm2m_context_t* mp_lwm2mH;

    /** User data for notify call back */
    struct s_cbparams_t* mp_cbUserData;

    /** LWM2M Devices associated to the server */
    std::map< std::string, LWM2MDevice* > m_devMap;

#ifdef OPCUA_LWM2M_SERVER_USE_THREAD
    /** Mutex for Thread safe execution */
    pthread_mutex_t m_mutex;

    /** thread instance */
    pthread_t m_thread;

    /** indicate if to run thread */
    bool m_threadRun;
#endif /* #ifdef OPCUA_LWM2M_SERVER_USE_THREAD */
};

#endif /* #ifndef __LWM2MSERVER_H__ */

