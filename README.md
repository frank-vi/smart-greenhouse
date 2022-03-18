# Smart Greenhouse

The project was developed for the "Programmazione di Sistemi Embedded" course with the aim of building a smart greenhouse.


The smart greenhouse monitors and controls several parameters to ensure plant growth:
- atmospheric
- of the soil
- and the light absorbed for the chlorophyll synthesis.

To achieve this, it was necessary to create a system that included three sub-systems:
- a fogging system to cool the environment with the aim of ensuring the moisture needs of the plants. This system:
-- reduces the indoor temperature,
-- provides the necessary moisture for the plants, and
-- water the soil by the method of moistening the air.

- an heating system to increase the indoor temperature when it's too cold for the kind of plants.
- an irrigation system used when the temperature is too high and the fogging system isn't enough.

The control of the smart greenhouse can be done in two ways:
- automatic: the default mode, with which the system makes decisions autonomously; 
- manual: the user makes decisions via the mobile app.

The project took place on two dimensions:
- software: design, development and deployment on the devices;
- hardware: design and development of the electronic circuit and the greenhouse.

**Technologies** used: _MQTT protocol_, _Pi4J library_.

**Languages** used: _Java_, _C++_, _UML2_.

**Development Tools** used: _Eclipse_, _VSCode + Platformio_.

**Hardware** used: _Arduino Uno_, _Raspberry Pi 1 B+_, sensors and actuators.
