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
 * \file    LWM2MResource.cpp
 * \author  Institute of reliable Embedded Systems
 *          and Communication Electronics
 * \date    $Date$
 * \version $Version$
 *
 * \brief   Implementation of a LWM2M Resource.
 *
 */

/*
 * --- Includes ------------------------------------------------------------- *
 */
#include <stdint.h>
#include <iostream>
#include <string>
#include "LWM2MResource.h"
#include "LWM2MObject.h"

/*
 * --- Methods Definition ----------------------------------------------------- *
 */


/*---------------------------------------------------------------------------*/
/*
* LWM2MResource::startServer()
*/
int8_t LWM2MResource::registerObserver( LWM2MResourceObserver* p_observer )
{
    if( p_observer == NULL )
        return -1;

    /* find the observer in the list */
    std::vector< LWM2MResourceObserver*>::iterator it =
            m_vectObs.begin();

    while( it != m_vectObs.end() )
    {
        if( *it == p_observer )
            /* found observer */
            break;
        it++;
    }


    if( it == m_vectObs.end() )
    {
        /* The observer was not found so it has to be added. */
        m_vectObs.push_back( p_observer );
    }

    return 0;

} /* LWM2MResource::registerObserver() */



/*---------------------------------------------------------------------------*/
/*
* LWM2MResource::deregisterObserver()
*/
int8_t LWM2MResource::deregisterObserver( const LWM2MResourceObserver* p_observer )
{
    if( p_observer == NULL )
        return -1;

    /* find the observer in the list */
    std::vector< LWM2MResourceObserver*>::iterator it =
            m_vectObs.begin();

    while( it != m_vectObs.end() )
    {
        if( *it == p_observer )
            /* found observer */
            break;
        it++;
    }


    if( it != m_vectObs.end() )
    {
        /* The observer was not found so it has to be added. */
        m_vectObs.erase( it );
    }

    return 0;

} /* LWM2MResource::deregisterObserver() */


/*---------------------------------------------------------------------------*/
/*
* LWM2MResource::notifyObservers()
*/
int8_t LWM2MResource::notifyObservers( const s_lwm2m_resobsparams_t* p_params ) const
{
    /* Iterate through the observers in the list */
    std::vector< LWM2MResourceObserver*>::const_iterator it =
             m_vectObs.begin();

    while( it != m_vectObs.end() )
    {
        /* notify the current observer */
        (*it)->notify( NULL, this, p_params );
        it++;
    }

    return 0;
}

