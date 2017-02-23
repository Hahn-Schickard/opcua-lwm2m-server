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
 * \file    LWM2MDevice.cpp
 * \author  Institute of reliable Embedded Systems
 *          and Communication Electronics
 * \date    $Date$
 * \version $Version$
 *
 * \brief   Implementation of a LWM2M Device.
 *
 */


/*
 * --- Includes ------------------------------------------------------------- *
 */
#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>
#include "LWM2MDevice.h"
#include "LWM2MObject.h"
#include "LWM2MServer.h"

/*
 * --- Methods Definition ----------------------------------------------------- *
 */

/*---------------------------------------------------------------------------*/
/*
* LWM2MDevice::getLifetime()
*/
int32_t LWM2MDevice::getLifetime( void )
{
    lwm2m_client_t* p_dev;

    if( mp_srv == NULL )
        return -1;

    /* try to get the structure of the device from server */
    p_dev = mp_srv->getDevice( m_name );

    if( p_dev == NULL)
        return -1;

    /* return the lifetime */
    return p_dev->lifetime;

} /* LWM2MObject::getLifetime() */


/*---------------------------------------------------------------------------*/
/*
* LWM2MDevice::getEndOfLife()
*/
int32_t LWM2MDevice::getEndOfLife( void )
{
    lwm2m_client_t* p_dev;

    if( mp_srv == NULL )
        return -1;

    /* try to get the structure of the device from server */
    p_dev = mp_srv->getDevice( m_name );

    if( p_dev == NULL)
        return -1;

    /* return the lifetime */
    return p_dev->endOfLife;

} /* LWM2MObject::getEndOfLife() */


/*---------------------------------------------------------------------------*/
/*
* LWM2MDevice::addObject()
*/
LWM2MObject* LWM2MDevice::getObject( uint16_t objID, uint8_t instID )
{
  LWM2MObject* ret = NULL;

  std::vector< LWM2MObject* >::iterator it = objectStart();
  while( it != objectEnd() )
  {
    if( ((*it)->getObjId() == objID) && ((*it)->getInstId() == instID) )
    {
      ret = (*it);
      break;
    }

    it++;
  }

  return ret;

} /* LWM2MObject::getObject() */



/*---------------------------------------------------------------------------*/
/*
* LWM2MDevice::addObject()
*/
int16_t LWM2MDevice::addObject( LWM2MObject* p_obj )
{
    /* Set this as the parent of the resource */
    p_obj->setParent( this );

    /* add the resource to the list */
    m_objVect.push_back( p_obj );

    return 0;

} /* LWM2MObject::addObject() */

