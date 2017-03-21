
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# build
#
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------

if(DTLS)
    message(FATAL_ERROR "DTLS option is not supported.")
endif()

include(${CMAKE_CURRENT_LIST_DIR}/wakaama/core/wakaama.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/wakaama/examples/shared/shared.cmake)

add_definitions(-DLWM2M_SERVER_MODE)
add_definitions(${SHARED_DEFINITIONS} ${WAKAAMA_DEFINITIONS})

include_directories (${WAKAAMA_SOURCES_DIR} ${SHARED_INCLUDE_DIRS})

SET(SOURCES
  ${PROJECT_SOURCE_DIR}/../../niki/opcua-lwm2m-server/LWM2MDevice.cpp
  ${PROJECT_SOURCE_DIR}/../../niki/opcua-lwm2m-server/LWM2MObject.cpp
  ${PROJECT_SOURCE_DIR}/../../niki/opcua-lwm2m-server/LWM2MResource.cpp
  ${PROJECT_SOURCE_DIR}/../../niki/opcua-lwm2m-server/LWM2MServer.cpp
)

add_library(OpcUalwm2m SHARED ${SHARED_SOURCES} ${SOURCES} ${WAKAAMA_SOURCES})

target_link_libraries(
    OpcUalwm2m
    pthread
    ${CMAKE_DL_LIBS}
    ${Boost_LIBRARIES}
)

# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# install
#
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
file(GLOB INC_OpcUalwm2m ${PROJECT_SOURCE_DIR}/OpcUalwm2m/*.h)


install(TARGETS OpcUalwm2m DESTINATION ${LIB_DIR}/OpcUaStack)
install(FILES ${INC_OpcUalwm2m} DESTINATION ${INC_DIR}/OpcUaStack/OpcUalwm2m)



