//==============================================================================
//
//  CRYSTALFONTZ
//
//  This code drives the CFAG160128E family of displays
//    https://www.crystalfontz.com/product/cfag160128etmitz
//    https://www.crystalfontz.com/product/cfag160128e1tmitz
//    https://www.crystalfontz.com/product/cfag160128eyyhtz
//
//  The controller is a Solomon Systech RA6963
//    https://www.crystalfontz.com/controllers/Raio%20Technology/RA6963/
//
//  Seeeduino v4.2, an open-source 3.3v capable Arduino clone.
//    https://www.seeedstudio.com/Seeeduino-V4.2-p-2517.html
//    https://github.com/SeeedDocument/SeeeduinoV4/raw/master/resources/Seeeduino_v4.2_sch.pdf
//
//==============================================================================
//This is free and unencumbered software released into the public domain.
//
//Anyone is free to copy, modify, publish, use, compile, sell, or
//distribute this software, either in source code form or as a compiled
//binary, for any purpose, commercial or non-commercial, and by any
//means.
//
//In jurisdictions that recognize copyright laws, the author or authors
//of this software dedicate any and all copyright interest in the
//software to the public domain. We make this dedication for the benefit
//of the public at large and to the detriment of our heirs and
//successors. We intend this dedication to be an overt act of
//relinquishment in perpetuity of all present and future rights to this
//software under copyright law.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
//OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
//ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//OTHER DEALINGS IN THE SOFTWARE.
//
//For more information, please refer to <http://unlicense.org/>
//==============================================================================
// LCD & USD control lines
//   ARD      | Port  |            |  Function - 8080 Parallel   |
//------------+-------+------------+-----------------------------+
//  3.3V      |       | 3          |  POWER 3.3V                 |
//  GND	      |       | 2          |  GROUND                     |
// -----------+-------+------------+-----------------------------+
//  D8        | PORTC | 6          |  Write               (WR)   |
//  D9        | PORTC | 7          |  Read                (RD)   |
//  D10       | PORTB | 8          |  Chip Enable Signal  (CS)   |
//  D11       | PORTC | 9          |  Data/Command        (DC)   |
//  D12       | PORTB | 11         |  Reset            (RESET)   |
// -----------+-------+------------+-----------------------------+
//  D0        | PORTD | 12         |  (DB0)                      |
//  D1        | PORTD | 13         |  (DB1)                      |
//  D2        | PORTD | 14         |  (DB2)                      |
//  D3        | PORTD | 15         |  (DB3)                      |
//  D4        | PORTD | 16         |  (DB4)                      |
//  D5        | PORTD | 17         |  (DB5)                      |
//  D6        | PORTD | 18         |  (DB6)                      |
//  D7        | PORTD | 19         |  (DB7)                      |
//
//==============================================================================
//
//  This code is demonstrated using 8080 Parallel
//
//==============================================================================
#define __AVR_ATmega32U4__ 
#include <avr/io.h> 

//  Select the interface
#define PAR_8080
//------------------------------------------------------------------------------
//Allow the serial debugging monitor, but only if SPI (pin conflict with parallel)
#define SER_DEBUG
#ifdef PAR_8080
#undef SER_DEBUG
#endif // PAR_8080
//==============================================================================
#define CLR_WR (PORTB &= ~(0x01))  //pin #8  -
#define SET_WR (PORTB |= (0x01))   //pin #8  -
#define CLR_RD (PORTB &= ~(0x02))  //pin #9  -
#define SET_RD (PORTB |= (0x02))   //pin #9  -
#define CLR_CS (PORTB &= ~(0x04))  //pin #10 -
#define SET_CS (PORTB |= (0x04))   //pin #10 -
#define CLR_DC (PORTB &= ~(0x08))  //pin #11 -
#define SET_DC (PORTB |= (0x08))   //pin #11 -
#define CLR_RES (PORTB &= ~(0x10)) //pin #12 -
#define SET_RES (PORTB |= (0x10))  //pin #12 -

#include <avr/io.h>

#define HRES (160)
#define VRES (128)

//================================================================================

void writeCommand(uint8_t command)
{
  //select the LCD's command register
  SET_DC;
  //select the LCD controller
  CLR_CS;
  //send the data via parallel
  CLR_WR;
  delayMicroseconds(1);
  PORTD = command;
  //clear the write register
  delayMicroseconds(1);
  //set the write register
  SET_WR;
  SET_CS;
  //deselct the LCD controller
}
//================================================================================
void writeData(uint8_t data)
{
  //select the LCD's data register
  CLR_DC;
  //select the LCD controller
  CLR_CS;
  //send the data via parallel
  CLR_WR;
  delayMicroseconds(1);
  PORTD = data;
  //clear the write register

  delayMicroseconds(1);
  //set the write register
  SET_WR;
  SET_CS;
  //deselct the LCD controller
}
//================================================================================

void Fill_RAM(uint8_t Data)
{
  uint8_t
      i;

  writeData(0x00);
  writeData(0x05);
  writeCommand(0x24);

  // writeCommand(0x9c); // display mode - graphic on, text off
  writeCommand(0xB0); // auto write

  for (uint8_t y = 0; y < VRES; y++)
  {

    for (uint8_t x = 0; x < HRES / 8; x++)
    {
      writeData(Data);
      delay(5);
    }
  }
  writeCommand(0xB2); // auto write reset
}

//================================================================================
// showImage() takes an image out of flash and puts it on the screen. In this case,
// the image stored in flash is the splash screen
//================================================================================
void showImage(const uint8_t image[7][128])
{
  writeData(0x00);
  writeData(0x05);
  writeCommand(0x24);

  // writeCommand(0x98);	// display mode - graphic on, text off
  writeCommand(0xB0); // auto write
  for (uint8_t y = 0; y < VRES; y++)
  {

    for (uint8_t x = 0; x < HRES / 8; x++)
    {
      writeData(pgm_read_byte(&image[y][x]));
    }
  }

  writeCommand(0xB2); // auto write reset
}
//================================================================================

void displayInit()
{
  SET_RES;
  delay(10);
  CLR_RES;
  delay(100);
  SET_RES;
  delay(500);

  writeData(0x00);
  writeData(0x00);
  writeCommand(0x40); // set text home address

  writeData(0x00);
  writeData(0x05);    // address 0x0800
  writeCommand(0x42); // set graphic home address

  writeData(0x10); // 240/8
  writeData(0x00);
  writeCommand(0x41); // set text area

  writeData(0x14);
  writeData(0x00);
  writeCommand(0x43); // set graphic area

  writeCommand(0xA0); // 1 line cursor
  writeCommand(0x80); // mode set - exor mode
  writeCommand(0x98); // display mode - graphic on, text off

  // writeData(0x00);
  // writeData(0x00);
  // writeCommand(0x21);	// set cursor position
}
void setup()
{
  //Set up port directions
  DDRD = 0xff;
  DDRC = 0xff;
  DDRB = 0x1f;
  //Idle the lines in a reasonable state
  PORTD = 0xff;
  SET_RD;
  SET_WR;
  SET_CS;

#ifdef SER_DEBUG
  Serial.begin(9600);
  Serial.println();
  Serial.println("Serial Initialized");
#endif // SER_DEBUG

  //OLED_Init takes ~120ms
  displayInit();
#ifdef SER_DEBUG
  Serial.println("Init done");
#endif // SER_DEBUG
}
//================================================================================
void loop()
{
#ifdef SER_DEBUG
  Serial.println("top of loop");
#endif // SER_DEBUG

  Fill_RAM(0xff);
  delay(1000);

  Fill_RAM(0xaa);
  delay(1000);

  Fill_RAM(0x00);
  delay(1000);
}
//================================================================================