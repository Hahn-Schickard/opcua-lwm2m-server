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
* LWM2MResource::getDevice()
*/
const LWM2MDevice* LWM2MResource::getDevice( void ) const
{
    if( mp_parent != NULL )
        return mp_parent->getDevice();
    else
        return NULL;

} /* LWM2MResource::getDevice() */


/*---------------------------------------------------------------------------*/
/*
* LWM2MResource::getServer()
*/
LWM2MServer* LWM2MResource::getServer( void ) const
{
    if( mp_parent != NULL )
        return mp_parent->getServer();
    else
        return NULL;

} /* LWM2MResource::getServer() */


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

