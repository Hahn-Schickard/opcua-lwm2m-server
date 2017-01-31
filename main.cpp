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
 * --- Includes ------------------------------------------------------------- *
 */
#include "LWM2MServer.h"
#include "LWM2MDevice.h"
#include "LWM2MObject.h"
#include "LWM2MResource.h"
#include "LWM2MResourceObserver.h"


class TestObserver
		: public LWM2MResourceObserver
{
public:

	TestObserver(){};
	virtual ~TestObserver(){};

	virtual int8_t notify( const LWM2MServer* p_srv,  const LWM2MResource* p_res,
			const s_lwm2m_resobsparams_t* p_params ) const {

		std::string dataStr = "";

		std::cout << "**** Notification start **** " << std::endl;
		std::cout << "Resource:  " << (int)p_res->getResId() << std::endl;
		std::cout << "Client-ID: " << (int)p_params->clientID << std::endl;
		std::cout << "Status:    " << (int)p_params->status << std::endl;
		std::cout << "Data-Len:  " << (int)p_params->dataLength << std::endl;

		if( p_params->data != NULL )
		{
			dataStr.append( (char*)p_params->data, p_params->dataLength );
			std::cout << "Data:      " << dataStr << std::endl;
		}
		std::cout << "**** Notification end   **** " << std::endl;

		return 0;
	}
};


int main(int argc, char **argv)
{
	TestObserver observer;
	LWM2MServer::s_cbparams_t p_obsParams;
	/* create the LWM2M server */
	LWM2MServer* p_srv = new LWM2MServer();
	/* create the LWM2M device */
	LWM2MDevice* p_dev = new LWM2MDevice( "TestDevice", p_srv );

	LWM2MObject* p_obj;
	LWM2MObject* p_testObj;

	LWM2MResource* p_res;
	LWM2MResource* p_testRes;
	LWM2MResource* p_testRes2;

	p_obj = new LWM2MObject( 1, 0 );
	p_res = new LWM2MResource( 0, true, true );
	p_obj->addResource( p_res );
	p_res = new LWM2MResource( 1, true, true );
	p_obj->addResource( p_res );
	p_testRes = p_res;
	p_testRes->registerObserver( &observer );


	p_dev->addObject( p_obj );
	p_testObj = p_obj;

	p_obj = new LWM2MObject( 2, 0 );
	p_res = new LWM2MResource( 0, true, true );
	p_obj->addResource( p_res );
	p_dev->addObject( p_obj );

	p_obj = new LWM2MObject( 6, 0 );
	p_res = new LWM2MResource( 9, true, true );
	p_obj->addResource( p_res );
	p_dev->addObject( p_obj );
	p_testRes2 = p_res;
	p_testRes2->registerObserver( &observer );


	p_obj = new LWM2MObject( 1024, 10 );
	p_res = new LWM2MResource( 0, true, true );
	p_obj->addResource( p_res );
	p_res = new LWM2MResource( 2, false, false, true);
	p_obj->addResource( p_res );
	p_res = new LWM2MResource( 3, true, true );
	p_obj->addResource( p_res );
	p_dev->addObject( p_obj );


	/* start the server */
	p_srv->startServer();

	uint32_t i = lwm2m_gettime();
	int j = 12;
	while( 1 )
	{
		/* run the server instance */
		p_srv->runServer();

		//std::cout << "Has Device:            " << p_srv->hasDevice( std::string("TestDevice") ) << std::endl;
		//std::cout << "TestClient Lifetime:   " << p_dev->getLifetime() << std::endl;
		//std::cout << "TestClient End ofLife: " << p_dev->getEndOfLife() << std::endl;

		if( p_srv->hasDevice(std::string("TestDevice")))
		{
			if(i < lwm2m_gettime())
			{
				if(j > 10)
				{
					std::string val;
					int8_t ret;

					val = "500";
					ret = p_srv->write( p_testRes, val, NULL );
					ret = p_srv->read( p_testRes, val, NULL );
					std::cout << "Read returned: " << (int)ret << " (" << val << ")" << std::endl;
				}
				else if( j > 9 )
				{
					int8_t ret;
					ret = p_srv->observe( p_testRes2, true, &p_obsParams );
					std::cout << "Observe returned: " << (int)ret << std::endl;
				}
				//else if( j == 0 )
				else if( 1 == 0 )
				{
					int8_t ret;
					ret = p_srv->observe( p_testRes2, false, NULL );
					std::cout << "Observe Cancel returned: " << (int)ret << std::endl;
				}

				i = lwm2m_gettime() + 5;
				j--;
			}
		}
	}

	/* stop the server and delete objects */
	p_srv->stopServer();

	delete p_dev;
	delete p_srv;

	return 0;
}
