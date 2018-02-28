/*
 * --- License -------------------------------------------------------------- *
 */

/*
 * Copyright 2017 NIKI 4.0 project team
 *
 * NIKI 4.0 was financed by the Baden-Württemberg Stiftung gGmbH (www.bwstiftung.de).
 * Project partners are FZI Forschungszentrum Informatik am Karlsruher
 * Institut für Technologie (www.fzi.de), Hahn-Schickard-Gesellschaft
 * für angewandte Forschung e.V. (www.hahn-schickard.de) and
 * Hochschule Offenburg (www.hs-offenburg.de).
 * This file was developed by the Institute of reliable Embedded Systems
 * and Communication Electronics
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
    lwm2m_data_t* data;
    /* number of read data */
    uint8_t dataLen;
    /** Buffer */
    uint8_t * buffer;
    /** Length of the data included */
    int bufferLen;

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

