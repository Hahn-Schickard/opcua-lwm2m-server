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


/*---------------------------------------------------------------------------*/
/*
* LWM2MObject::getResource()
*/
LWM2MResource* LWM2MObject::getResource( uint16_t resID )
{
  LWM2MResource* ret = NULL;

  std::vector< LWM2MResource* >::const_iterator it = resourceStart();
  while( it != resourceEnd() )
  {
    if( (*it)->getResId() == resID )
    {
      ret = (*it);
      break;
    }

    it++;
  }

  return ret;

} /* LWM2MObject::getResource() */


