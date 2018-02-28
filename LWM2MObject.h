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
 * \file    LWM2MResource.h
 * \author  Institute of reliable Embedded Systems
 *          and Communication Electronics
 * \date    $Date$
 * \version $Version$
 *
 * \brief   Description of a LWM2M Object.
 *
 */


#ifndef __LWM2MOBJECT_H__
#define __LWM2MOBJECT_H__
#ifndef __DECL_LWM2MOBJECT_H__
#define __DECL_LWM2MOBJECT_H__ extern
#endif /* #ifndef __DECL_LWM2MOBJECT_H__ */


/*
 * --- Includes ------------------------------------------------------------- *
 */
#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>
#include "LWM2MResource.h"

/*
 * --- Forward Declaration ----------------------------------------------------- *
 */

/* Forward declaration of the LWM2MDeviceclass used as parent reference. */
class LWM2MDevice;

/*
 * --- Class Definition ----------------------------------------------------- *
 */

/**
 * \brief   LWM2MObject Class.
 *
 *          A LWM2M Object is the base container for accessing resources. Each
 *          object is identified by an object type ID and an according instance
 *          identifier.
 */
class LWM2MObject
{
    friend class LWM2MDevice;
    friend class LWM2MResource;

public:

    /**
     * \brief   Default constructor to create a LWM2M Object.
     */
    LWM2MObject( void )
        : m_objId( 0 )
        , m_instId( 0 )
        , mp_parent(NULL ){

        /* clear resource vector */
        m_resVect.clear();
    };


    /**
     * \brief   Extended constructor to create a LWM2M Object.
     */
    LWM2MObject( uint16_t objId, uint8_t instId )
        : m_objId( objId )
        , m_instId( instId )
        , mp_parent(NULL ){

        /* clear resource vector */
        m_resVect.clear();
    };

    /**
     * \brief   Default destructor of the LWM2M Server.
     */
    virtual ~LWM2MObject( void ) {

        std::vector< LWM2MResource* >::iterator it = m_resVect.begin();

        /*delete all Objects */
        while( it != m_resVect.end() )
        {
            delete (*it);
            it++;
        }
    };


    /**
     * \brief   Get the object ID,
     *
     * \return  Object ID.
     */
    uint16_t getObjId( void ) const {return m_objId;}


    /**
     * \brief   Get the instance ID,
     *
     * \return  Instance ID.
     */
    uint8_t getInstId( void ) const {return m_instId;}


    /**
     * \brief   Get the parent object.
     *
     * \return  Parent object.
     */
    const LWM2MDevice* getDevice( void ) const {return mp_parent;}


    /**
     * \brief   Get server instance.
     *
     * \return  Server object.
     */
    LWM2MServer* getServer( void ) const;


    /**
     * \brief   Add a new resource to the list.
     *
     * \param   p_res   Resource to add.
     *
     * \return  0 on success or negative value on error.
     */
    int16_t addResource( LWM2MResource* p_res );


    /**
     * \brief   Get a specific resource.
     *
     * \param   resID   ID of the resource.
     *
     * \return  Pointer to the resource if it exists or NULL otherwise.
     */
    LWM2MResource* getResource( uint16_t resID );


    /**
     * \brief   Get the begin of the registered resources.
     *
     * \return  Iterator pointing to the begin of the resources.
     */
    std::vector< LWM2MResource* >::const_iterator resourceStart( void ) const {
        return m_resVect.begin();
    };


    /**
     * \brief   Get the end of the registered resources.
     *
     * \return  Iterator pointing to the end of the resources.
     */
    std::vector< LWM2MResource* >::const_iterator resourceEnd( void ) const {
        return m_resVect.end();
    };

protected:


    /**
     * \brief   Set the parent object.
     *
     * \param   Parent object.
     */
    void setParent( const LWM2MDevice* p_parent ) {mp_parent = p_parent;};


private:

    /** Object ID */
    uint16_t m_objId;

    /** Instance ID */
    uint8_t m_instId;

    /** parent object */
    const LWM2MDevice* mp_parent;

    /** Vector of resources */
    std::vector< LWM2MResource* > m_resVect;
};

#endif /* #ifndef __LWM2MOBJECT_H__ */

