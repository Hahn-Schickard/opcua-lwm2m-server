## OPC UA LWM2M Server Implementation ##

This module provides an abstraction of the wakaama LWM2M server for the usage within
the NIKI OPC UA Server.

### Before building the project ###

Before the project can be build several steps need to be performed:

- get the wakaama submodule by running ```git submodule update --init```
- patch the wakaama sources by running ```git apply wakaama.patch```
