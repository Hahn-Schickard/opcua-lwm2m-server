# OPC UA LWM2M Server Implementation #

This module provides an abstraction of the wakaama LWM2M server for the usage within the OPC UA Server. It creates the interconnection between the LWM2M server and the OPC UA Server. Therefore it uses the wakaama server [https://github.com/eclipse/wakaama] as basis. In addition, an onject oriented C++ wrapper allows the integration into the OPC UA server.

This work was originated from the NIKI 4.0 project. NIKI 4.0 was financed by the Baden-Württemberg Stiftung gGmbH (www.bwstiftung.de).  Project partners are FZI Forschungszentrum  Informatik am Karlsruher Institut für Technologie (www.fzi.de), Hahn-Schickard-Gesellschaft für angewandte Forschung e.V. (www.hahn-schickard.de) and Hochschule Offenburg (www.hs-offenburg.de).

### Before building the project ###

Before the project can be build several steps need to be performed:

- get the wakaama submodule by running ```git submodule update --init```
- patch the wakaama sources by running ```git apply wakaama.patch```
