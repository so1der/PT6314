# PT6314
Arduino library for PT6314 VFD Driver

This library allows Arduino board (or any other board with Arduino framework, like espressif, etc.) to control vacuum fluorescent display (VFD) based on the PTC PT6314 chipset via Serial Protocol.

To control PT6314 via Serial Interface, connection should be as followed:

![alt tag](https://raw.githubusercontent.com/so1der/PT6314/main/images/serial_interface_connection.png "Schematic")

PT6314 also can be controlled via parallel protocol (i80/M68), in this case You can use [LiquidCrystal](https://github.com/arduino-libraries/LiquidCrystal) library (main features will work, but for some things library should be modificated)

I wrote this library following the example of the library [LiquidCrystal](https://github.com/arduino-libraries/LiquidCrystal), so usage of it is pretty similar - begin(), print(), etc. You can see more in the "Examples" folder.

# Note about createChar()
![alt tag](https://raw.githubusercontent.com/so1der/PT6314/main/images/7_row_display.jpg "7 row display")
In some displays, like in my, for example, there are only 7 rows for each character. However, display manufacturers in order not to waste PT6314's ability to display 8 rows of information, connect displays cursors and other parts (like commas, dots, etc.) as eighth rows. If you have a display like this, you need to consider that fact when you create custom chars, and if you don't need a cursor/dot/comma to appear with your custom char, you need to fill an eighth row with zeros.