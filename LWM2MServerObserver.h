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
 * \file    LWM2MServerObserver.h
 * \author  Institute of reliable Embedded Systems
 *          and Communication Electronics
 * \date    $Date$
 * \version $Version$
 *
 * \brief   Definition of a LWM2M Server Observer.
 *
 */


#ifndef __LWM2MSERVEROBSERVER_H__
#define __LWM2MSERVEROBSERVER_H__
#ifndef __DECL_LWM2MSERVEROBSERVER_H__
#define __DECL_LWM2MSERVEROBSERVER_H__ extern
#endif /* #ifndef __LWM2MSERVEROBSERVER_H__ */


/*
 * --- Includes ------------------------------------------------------------- *
 */
#include <stdint.h>
#include <iostream>
#include <string>


/*
 * --- Forward Declaration ----------------------------------------------------- *
 */

/* Forward declaration of the LWM2M device class. */
class LWM2MDevice;


/*
 * --- Type Definitions ----------------------------------------------------- *
 */

/**
 * \brief    Parameters used for resource notifications.
 */
typedef enum
{
    /** A new device registered */
    e_lwm2m_serverobserver_event_register,

    /** A new device was updated */
    e_lwm2m_serverobserver_event_update,

    /** A new device de-registered */
    e_lwm2m_serverobserver_event_deregister,

} e_lwm2m_serverobserver_event_t;


/*
 * --- Class Definition ----------------------------------------------------- *
 */

/**
 * \brief   LWM2MServerObserver Class.
 *
 *          A LWM2M Server can be observed so that every change of a
 *          device will be reported. This can be e.g. the registration
 *          of a new device or the update or de-registration of an
 *          existing device.
 */
class LWM2MServerObserver
{

public:

    /**
     * \brief   Default constructor.
     */
    LWM2MServerObserver( void ) {};


    /**
     * \brief   Default destructor.
     */
    virtual ~LWM2MServerObserver( void ) {};


    /**
     * \brief   Notification.
     *
     * \param   p_dev   Device the notification comes from.
     * \param   ev      Type of notification.
     *
     * \return  0 on success or negative value on error.
     */
    virtual int8_t notify( const LWM2MDevice* p_dev,
          const e_lwm2m_serverobserver_event_t ev ) = 0;

};

#endif /* #ifndef __LWM2MSERVEROBSERVER_H__ */

