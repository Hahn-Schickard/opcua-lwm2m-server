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
            delete (*it)++;};


    /**
     * \brief    Get the object ID,
     *
     * \return     Object ID.
     */
    int16_t getObjId( void ) const {return m_objId;}


    /**
     * \brief    Get the instance ID,
     *
     * \return     Instance ID.
     */
    int16_t getInstId( void ) const {return m_instId;}


    /**
     * \brief    Get the parent object.
     *
     * \return     Parent object.
     */
    const LWM2MDevice* getParent( void ) const {return mp_parent;}


    /**
     * \brief    Add a new resource to the list.
     *
     * \param    p_res        Resource to add.
     *
     * \return    0 on success or negative value on error.
     */
    int16_t addResource( LWM2MResource* p_res );


    /**
     * \brief    Get the begin of the registered resources.
     *
     * \return    Iterator pointing to the begin of the resources.
     */
    std::vector< LWM2MResource* >::iterator resourceStart( void ) {
        return m_resVect.begin();
    };


    /**
     * \brief    Get the end of the registered resources.
     *
     * \return    Iterator pointing to the end of the resources.
     */
    std::vector< LWM2MResource* >::iterator resourceEnd( void ) {
        return m_resVect.end();
    };

protected:


    /**
     * \brief    Set the parent object.
     *
     * \param     Parent object.
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

