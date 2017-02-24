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
 * \file    LWM2MResourceObserver.h
 * \author  Institute of reliable Embedded Systems
 *          and Communication Electronics
 * \date    $Date$
 * \version $Version$
 *
 * \brief   Definition of a LWM2M Resource Observer.
 *
 */


#ifndef __LWM2MRESOURCEOBSERVER_H__
#define __LWM2MRESOURCEOBSERVER_H__
#ifndef __DECL_LWM2MRESOURCEOBSERVER_H__
#define __DECL_LWM2MRESOURCEOBSERVER_H__ extern
#endif /* #ifndef __LWM2MRESOURCE_H__ */


/*
 * --- Includes ------------------------------------------------------------- *
 */
#include <stdint.h>
#include <iostream>
#include <string>
#include "liblwm2m.h"

/*
 * --- Forward Declaration ----------------------------------------------------- *
 */

/* Forward declaration of the LWM2MResource class. */
class LWM2MResource;
/* Forward declaration of the LWM2MServer class. */
class LWM2MServer;



/*
 * --- Type Definitions ----------------------------------------------------- *
 */

/**
 * \brief    Parameters used for resource notifications.
 */
typedef struct
{
    /** The Client UI the notification came from */
    uint16_t clientID;
    /** URI of the resource */
    lwm2m_uri_t * uriP;
    /** Status and type of the change */
    int status;
    /** Format of the included data */
    lwm2m_media_type_t format;
    /** Additional data (e.g. for a read) */
    uint8_t * data;
    /** Length of the data included */
    int dataLength;
    /** Initial observe */
    bool obsInit;

} s_lwm2m_resobsparams_t;


/*
 * --- Class Definition ----------------------------------------------------- *
 */

/**
 * \brief   LWM2MResourceObserver Class.
 *
 *          A LWM2M Resource can be observed so that every change in the
 *          resource will be reported.
 */
class LWM2MResourceObserver
{

public:

    /**
     * \brief   Default constructor to create a LWM2M Object.
     */
    LWM2MResourceObserver( void ) {};


    /**
     * \brief   Default destructor of the LWM2M Server.
     */
    virtual ~LWM2MResourceObserver( void ) {};


    /**
     * \brief   Get the resource ID.
     *
     * \param   p_srv     The server the notification is from.
     * \param   p_res     The resource the notification is for.
     * \param   p_params  Parameters of the notification.
     *
     * \return  0 on success or negative value on error.
     */
    virtual int8_t notify( const LWM2MServer* p_srv, const LWM2MResource* p_res,
            const s_lwm2m_resobsparams_t* p_params ) = 0;

};

#endif /* #ifndef __LWM2MRESOURCEOBSERVER_H__ */

