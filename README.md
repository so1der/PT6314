# PT6314
Arduino library for PT6314 VFD Driver

This library allows Arduino board (or any other board with Arduino framework, like espressif, etc.) to control vacuum fluorescent display (VFD) based on the PTC PT6314 chipset via Serial Protocol.

To control PT6314 via Serial Interface, connection should be as followed:

![alt tag](https://raw.githubcontent.com/so1der/PT6314/main/images/serial_interface_connection.png "Schematic")

PT6314 also can be controlled via parallel protocol (i80/M68), in this case You can use [LiquidCrystal](https://github.com/arduino-libraries/LiquidCrystal) library (main features will work, but for some things library should be modificated)