#include "PT6314.h"
#include <inttypes.h>
#include "Arduino.h"

PT6314::PT6314(uint8_t sck, uint8_t stb, uint8_t si)
{
    init(sck, stb, si);
}

void PT6314::init(uint8_t sck, uint8_t stb, uint8_t si)
{
    _sck_pin = sck;
    _stb_pin = stb;
    _si_pin = si;

    pinMode(_sck_pin, OUTPUT);
    pinMode(_stb_pin, OUTPUT);
    pinMode(_si_pin, OUTPUT);

    _displayfunction = VFD_FUNCTIONSET | VFD_8BITMODE | VFD_1LINE | VFD_BRT_100;
}

void PT6314::begin(uint8_t cols, uint8_t rows)
{
    _numlines = rows;
    if (_numlines > 1)
    {
        _displayfunction |= VFD_2LINE;
    }

    _displaycontrol = VFD_DISPLAYCONTROL | VFD_DISPLAYON | VFD_CURSOROFF | VFD_BLINKOFF;

    _displaymode = VFD_ENTRYMODESET | VFD_INCREMENT | VFD_CURSORSHIFTENABLED;

    delayMicroseconds(50000);

    send(COMMAND, VFD_CLEARDISPLAY);
    delayMicroseconds(2000);
    send(COMMAND, _displaycontrol);
    delayMicroseconds(4500);
    send(COMMAND, _displaymode);
    delayMicroseconds(4500);
    send(COMMAND, _displayfunction);
    delayMicroseconds(4500);
}

void PT6314::send(uint8_t mode, uint8_t value)
{
    int full_payload = value | (mode << 8);
    digitalWrite(_stb_pin, 0);
    delayMicroseconds(1);
    digitalWrite(_sck_pin, 0);
    for (int i = 15; i > -1; i--)
    {
        digitalWrite(_si_pin, bitRead(full_payload, i));
        clockPulse();
    }
    digitalWrite(_sck_pin, 1);
    digitalWrite(_stb_pin, 1);
    delayMicroseconds(1);
}

void PT6314::clockPulse()
{
    delayMicroseconds(2);
    digitalWrite(_sck_pin, 1);
    delayMicroseconds(2);
    digitalWrite(_sck_pin, 0);
}

void PT6314::clear()
{
    send(COMMAND, VFD_CLEARDISPLAY);
    delayMicroseconds(2000);
}

void PT6314::home()
{
    send(COMMAND, VFD_RETURNHOME);
}

void PT6314::noDisplay()
{
    _displaycontrol &= ~VFD_DISPLAYON;
    send(COMMAND, _displaycontrol);
}
void PT6314::display()
{
    _displaycontrol |= VFD_DISPLAYON;
    send(COMMAND, _displaycontrol);
}

// Turns the underline cursor on/off
void PT6314::noCursor()
{
    _displaycontrol &= ~VFD_CURSORON;
    send(COMMAND, _displaycontrol);
}
void PT6314::cursor()
{
    _displaycontrol |= VFD_CURSORON;
    send(COMMAND, _displaycontrol);
}

// Turn on and off the blinking cursor
void PT6314::noBlink()
{
    _displaycontrol &= ~VFD_BLINKON;
    send(COMMAND, _displaycontrol);
}
void PT6314::blink()
{
    _displaycontrol |= VFD_BLINKON;
    send(COMMAND, _displaycontrol);
}

void PT6314::setCursor(uint8_t col, uint8_t row)
{
    uint8_t position = col;
    if (row > 0)
    {
        position += 0x40;
    }
    send(COMMAND, VFD_SETDDRAMADDR | position);
}

void PT6314::setBrightness(uint8_t brt)
{
    switch (brt)
    {
    case 100:
        _displayfunction |= VFD_BRT_100;
        break;
    case 75:
        _displayfunction |= VFD_BRT_75;
        break;
    case 50:
        _displayfunction |= VFD_BRT_50;
        break;
    case 25:
        _displayfunction |= VFD_BRT_25;
        break;
    }
    send(COMMAND, _displayfunction);
}

inline size_t PT6314::write(uint8_t value)
{
    send(DATA, value);
    return 1; // assume sucess
}

void PT6314::createChar(uint8_t location, uint8_t charmap[])
{
    location &= 0x7; // we only have 8 locations 0-7
    send(COMMAND, VFD_SETCGRAMADDR | (location << 3));
    for (int i = 0; i < 8; i++)
    {
        send(DATA, charmap[i]);
    }
    home();
}