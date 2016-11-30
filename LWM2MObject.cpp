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
 * \file    LWM2MObject.cpp
 * \author  Institute of reliable Embedded Systems
 *          and Communication Electronics
 * \date    $Date$
 * \version $Version$
 *
 * \brief   Description of a LWM2M Object.
 *
 */


/*
 * --- Includes ------------------------------------------------------------- *
 */
#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>
#include "LWM2MObject.h"
#include "LWM2MDevice.h"

/*
 * --- Methods Definition ----------------------------------------------------- *
 */


/*---------------------------------------------------------------------------*/
/*
* LWM2MObject::addResource()
*/
int16_t LWM2MObject::addResource( LWM2MResource* p_res )
{
	/* Set this as the parent of the resource */
	p_res->setParent( this );

	/* add the resource to the list */
	m_resVect.push_back( p_res );

    return 0;

} /* LWM2MObject::addResource() */


