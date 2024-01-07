#ifndef PT6314_H
#define PT6314_H
#include <inttypes.h>
#include "Print.h"

// modes
#define COMMAND 0xF8
#define DATA 0xFA
#define CHAR_DATA 0x7D

// commands
#define VFD_CLEARDISPLAY 0x01
#define VFD_RETURNHOME 0x02
#define VFD_ENTRYMODESET 0x04
#define VFD_DISPLAYCONTROL 0x08
#define VFD_CURSORSHIFT 0x10
#define VFD_FUNCTIONSET 0x20
#define VFD_SETCGRAMADDR 0x40
#define VFD_SETDDRAMADDR 0x80

// flags for display entry mode
#define VFD_DECREMENT 0x00
#define VFD_INCREMENT 0x02
#define VFD_DISPLAYSHIFTENABLED 0x01
#define VFD_CURSORSHIFTENABLED 0x00

// flags for display on/off control
#define VFD_DISPLAYON 0x04
#define VFD_DISPLAYOFF 0x00
#define VFD_CURSORON 0x02
#define VFD_CURSOROFF 0x00
#define VFD_BLINKON 0x01
#define VFD_BLINKOFF 0x00

// flags for display/cursor shift
#define VFD_DISPLAYMOVE 0x08
#define VFD_CURSORMOVE 0x00
#define VFD_MOVERIGHT 0x04
#define VFD_MOVELEFT 0x00

// flags for function set
#define VFD_8BITMODE 0x10 // Irrelevant for serial data transfer
#define VFD_4BITMODE 0x00 // Irrelevant for serial data transfer
#define VFD_2LINE 0x08
#define VFD_1LINE 0x00
#define VFD_BRT_100 0x00
#define VFD_BRT_75 0x01
#define VFD_BRT_50 0x02
#define VFD_BRT_25 0x03

class PT6314 : public Print
{
public:
    PT6314(uint8_t sck, uint8_t stb, uint8_t si);
    void init(uint8_t sck, uint8_t stb, uint8_t si);
    void begin(uint8_t cols, uint8_t rows);

    void clear();
    void home();

    void noDisplay();
    void display();
    void noBlink();
    void blink();
    void noCursor();
    void cursor();
    void setCursor(uint8_t, uint8_t);
    void setBrightness(uint8_t brt);
    void createChar(uint8_t, uint8_t[]);

    virtual size_t write(uint8_t);

    using Print::write;

private:
    void send(uint8_t, uint8_t);
    void clockPulse();

    uint8_t _sck_pin; // Clock pin
    uint8_t _stb_pin; // Strobe pin
    uint8_t _si_pin;  // Serial Input pin

    uint8_t _displayfunction;
    uint8_t _displaycontrol;
    uint8_t _displaymode;
    uint8_t _numlines;
};

#endif