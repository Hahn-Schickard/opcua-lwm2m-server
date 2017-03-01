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

