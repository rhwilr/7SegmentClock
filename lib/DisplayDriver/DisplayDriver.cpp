#include <SPI.h>

#include "DisplayDriver.h"

int SPI_CS = 10;

byte display_data[][3] =
{
  //   row 0         row 1         row 2        
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  //   row 0         row 1         row 2         
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  //   row 0         row 1         row 2          
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  //   row 0         row 1         row 2         
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  //   row 0         row 1         row 2         
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  //   row 0         row 1         row 2                
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
  { 0b00000000,   0b00000000,   0b00000000,},
};

void initDisplayDriver()
{
  pinMode(SPI_CS, OUTPUT);
  SPI.begin(); 
  
  setDriverRegisters(0x09, 0x00); // Decode-Mode
  setDriverRegisters(0x0A, 0x01); // Intensity
  setDriverRegisters(0x0B, 0x07); // Scan-Limit
  setDriverRegisters(0x0C, 0x01); // Shutdown Register
  setDriverRegisters(0x0F, 0x00); // Display-Test

  for (int y=0; y<=8; y++) {
    setDriverRegisters(y, 0x00);  // Init all registers to 0
  }
}

/*
** Write to a specific XY coordinate
*/
void putPixel(byte x, byte y, byte thebyte)
{
  byte bx = x * 8;
  byte by = y;
  int row = 1;
  if (by >= 8 && by <= 15)
  {
    by = by - 8;
    row = 2;
  }
  if (by >= 16 && by <= 24)
  {
    by = by - 16;
    row = 3;
  }
  display_data[bx + by][row] = thebyte;
}

/*
** Update to a specific XY coordinate
*/
void addPixel(byte x, byte y, byte thebyte)
{
  byte bx = x * 8;
  byte by = y;
  int row = 1;
  if (by >= 8 && by <= 15)
  {
    by = by - 8;
    row = 2;
  }
  if (by >= 16 && by <= 24)
  {
    by = by - 16;
    row = 3;
  }
  display_data[bx + by][row] |= thebyte;
}

/*
** Write a value to all displays inside a square area
*/
void fillPixel(byte x1, byte y1, byte x2, byte y2, byte thebyte)
{
  for (int i = x1; i <= (x2); i++)
  {
    for (int j = y1; j <= (y2); j++)
    {
      putPixel(i, j, thebyte);
    }
  }
}

/*
** Clears the display and triggers a refresh.
*/
void clear ()
{
  fillPixel(0, 0, 5, 23, 0x00);
  refreshDisplays();
}

/*
** Displays a digit at the defined location
*/
void digits(byte place, byte value) 
{
  switch (value) {
        case 0:
          putPixel(0, place+2, 0b00011000);
          putPixel(0, place+3, 0b00111101);
          putPixel(0, place+4, 0b01111111);
          putPixel(0, place+5, 0b00011111);
          putPixel(1, place+1, 0b00010000);
          fillPixel(1, place+2, 1, place+5, 0b01111111);
          putPixel(1, place+3, 0b01100111);
          putPixel(1, place+4, 0b01111011);
          putPixel(2, place+2, 0b01101111);
          putPixel(2, place+5, 0b01001111);
          putPixel(2, place+1, 0b01111101);
          putPixel(2, place+4, 0b00110000);
          fillPixel(3, place+1, 3, place+4, 0b01111111);
          putPixel(3, place+3, 0b00010000);
          putPixel(3, place+2, 0b00000110);
          addPixel(3, place+5, 0b00000110);
          fillPixel(4, place+1, 4, place+3, 0b01111111);
          putPixel(4, place+2, 0b00011111);
          putPixel(4, place+4, 0b01000111);
          putPixel(5, place+1, 0b01110011);
          putPixel(5, place+2, 0b01111111);
          putPixel(5, place+3, 0b01100111);
          break;
        case 1:
          putPixel(0, place+3, 0b00010000);
          putPixel(0, place+4, 0b01111111);
          putPixel(0, place+5, 0b00011111);
          fillPixel(1, place+3, 1, place+4, 0b01111111);
          putPixel(1, place+5, 0b00000110);
          putPixel(2, place+2, 0b00111101);
          putPixel(2, place+3, 0b01111111);
          putPixel(2, place+4, 0b01001111);
          fillPixel(3, place+2, 3, place+3, 0b01111111);
          putPixel(3, place+1, 0b00110000);
          putPixel(3, place+4, 0b00000110);
          fillPixel(4, place+1, 4, place+2, 0b01111111);
          putPixel(4, place+3, 0b01000110);
          putPixel(5, place, 0b00100000);
          putPixel(5, place+1, 0b01111111);
          putPixel(5, place+2, 0b01111111);
          putPixel(5, place+3, 0b00000000);
          break;
        case 2:
          putPixel(0, place+2, 0b00011000);
          putPixel(0, place+3, 0b00111101);
          putPixel(0, place+4, 0b01111111);
          putPixel(0, place+5, 0b00011111);
          putPixel(1, place+1, 0b00110000);
          putPixel(1, place+2, 0b01111111);
          putPixel(1, place+3, 0b01100010);
          putPixel(1, place+4, 0b01111011);
          putPixel(1, place+5, 0b01111111);
          putPixel(2, place+3, 0b00111000);
          putPixel(2, place+4, 0b01111111);
          putPixel(2, place+5, 0b01000110);
          putPixel(3, place+2, 0b00111101);
          putPixel(3, place+3, 0b01111111);
          putPixel(3, place+4, 0b01000110);
          addPixel(4, place, 0b00010000);
          fillPixel(4, place+1, 4, place+2, 0b01111111);
          putPixel(4, place+3, 0b01000110);
          putPixel(5, place, 0b00100000);
          putPixel(5, place+1, 0b01110011);
          fillPixel(5, place+2, 5, place+3, 0b01111111);
          putPixel(5, place+4, 0b01100111);
          break;
        case 3:
          putPixel(0, place+2, 0b00011000);
          fillPixel(0, place+3, 0, place+4, 0b01111111);
          putPixel(0, place+5, 0b00011111);
          putPixel(1, place+1, 0b00100000);
          putPixel(1, place+2, 0b01111111);
          putPixel(1, place+3, 0b01100010);
          putPixel(1, place+4, 0b01111011);
          putPixel(1, place+5, 0b01111111);
          putPixel(2, place+2, 0b00011000);
          fillPixel(2, place+3, 4, place+4, 0b01111111);
          putPixel(2, place+3, 0b00111101);
          putPixel(2, place+5, 0b01000110);
          putPixel(3, place+2, 0b01100000);
          putPixel(3, place+3, 0b01110011);
          putPixel(3, place+5, 0b00000100);
          putPixel(4, place+2, 0b00011101);
          putPixel(4, place+1, 0b00011000);
          putPixel(4, place+3, 0b00111101);
          addPixel(4, place+5, 0b00000110);
          putPixel(5, place, 0b00100000);
          putPixel(5, place+1, 0b01110011);
          fillPixel(5, place+2, 5, place+3, 0b01111111);
          putPixel(5, place+4, 0b01000010);
          break;
        case 4:
          putPixel(0, place+2, 0b00111000);
          putPixel(0, place+3, 0b01111111);
          putPixel(0, place+4, 0b00010000);
          putPixel(0, place+5, 0b01111111);
          putPixel(1, place+1, 0b00010000);
          fillPixel(1, place+2, 2, place+2, 0b01111111);
          putPixel(1, place+3, 0b01000110);
          putPixel(1, place+4, 0b01111101);
          putPixel(1, place+5, 0b01001111);
          putPixel(2, place+1, 0b01111101);
          putPixel(2, place+3, 0b00111000);
          putPixel(2, place+4, 0b01111111);
          putPixel(2, place+5, 0b00000110);
          fillPixel(3, place+1, 3, place+4, 0b01111111);
          putPixel(3, place+5, 0b00000000);
          addPixel(3, place, 0b00010000);
          putPixel(4, place+2, 0b00010000);
          putPixel(4, place+3, 0b01111111);
          putPixel(4, place+4, 0b00000110);
          putPixel(5, place+2, 0b01111111);
          putPixel(5, place+3, 0b01100111);
          break;
        case 5:
          putPixel(0,  place+2, 0b00111101);
          fillPixel(0, place+3, 0, place+5, 0b01111111);
          putPixel(1,  place+1, 0b00110000);
          putPixel(1,  place+2, 0b01111111);
          putPixel(1,  place+3, 0b01011111);
          putPixel(1,  place+4, 0b00001100);
          putPixel(2,  place+3, 0b01111111);
          putPixel(2,  place+2, 0b01110011);
          putPixel(2,  place+4, 0b01111111);
          putPixel(2,  place+5, 0b00000110);
          putPixel(3,  place+3, 0b00110000);
          fillPixel(3,  place+4, 4,  place+4, 0b01111111);
          putPixel(3,  place+5, 0b00000110);
          fillPixel(4, place+1, 4, place+2, 0b00011101);
          putPixel(4,  place+3, 0b00111101);
          putPixel(4,  place+5, 0b00000010);
          putPixel(5,  place, 0b00100000);
          fillPixel(5,  place+1, 5,  place+2, 0b01111111);
          putPixel(5,  place+3, 0b01100111);
          putPixel(5,  place+4, 0b01000010);
          break;
        case 6:
          putPixel(0, place+3, 0b00011000);
          putPixel(0, place+4, 0b01111111);
          putPixel(0, place+5, 0b00000110);
          fillPixel(1, place+2, 2, place+4, 0b01111111);
          putPixel(1, place+2, 0b00111101);
          putPixel(1, place+4, 0b01000010);
          putPixel(2, place+1, 0b00111000);
          putPixel(2, place+5, 0b00000100);
          addPixel(3, place, 0b00010000);
          fillPixel(3, place+1, 4, place+4, 0b01111111);
          putPixel(3, place+2, 0b01000110);
          putPixel(3, place+3, 0b01100000);
          putPixel(3, place+5, 0b00000110);
          addPixel(4, place, 0b00110000);
          putPixel(4, place+2, 0b00011111);
          putPixel(4, place+3, 0b00111101);
          putPixel(5, place+1, 0b01110011);
          putPixel(5, place+2, 0b01111111);
          putPixel(5, place+3, 0b01100111);
          break;
        case 7:
          putPixel(0, place+1, 0b00110000);
          fillPixel(0, place+2, 0, place+4, 0b01111111);
          putPixel(0, place+5, 0b00011111);
          putPixel(1, place+1, 0b00100000);
          putPixel(1, place+2, 0b01100011);
          putPixel(1, place+3, 0b01100011);
          putPixel(1, place+4, 0b01111111);
          putPixel(1, place+5, 0b01111111);
          putPixel(2, place+5, 0b01000110);
          putPixel(2, place+4, 0b01111111);
          putPixel(2, place+3, 0b00111101);
          putPixel(3, place+2, 0b00111101);
          putPixel(3, place+3, 0b01111111);
          putPixel(3, place+4, 0b01100111);
          putPixel(4, place+1, 0b00111101);
          putPixel(4, place+2, 0b01111111);
          putPixel(4, place+3, 0b01000110);
          fillPixel(5, place+1, 5, place+2, 0b01111111);
          putPixel(5, place, 0b00100000);
          break;
        case 8:
          putPixel(0, place+2, 0b00011000);
          fillPixel(0, place+3, 0, place+4, 0b01111111);
          putPixel(0, place+5, 0b00011111);
          putPixel(1, place+1, 0b00110000);
          putPixel(1, place+2, 0b01111111);
          putPixel(1, place+3, 0b01100010);
          putPixel(1, place+4, 0b01111011);
          putPixel(1, place+5, 0b01111111);
          putPixel(2, place+1, 0b00100000);
          putPixel(2, place+2, 0b01111111);
          fillPixel(2, place+3, 4, place+4, 0b01111111);
          putPixel(2, place+3, 0b00111101);
          putPixel(2, place+5, 0b01000110);
          putPixel(3, place+1, 0b00111101);
          putPixel(3, place+2, 0b01100111);
          putPixel(3, place+3, 0b01110011);
          putPixel(3, place+5, 0b00000100);
          putPixel(4, place+2, 0b00011101);
          putPixel(4, place+1, 0b01111111);
          putPixel(4, place+3, 0b00111101);
          addPixel(4, place+5, 0b00000110);
          addPixel(4, place, 0b00110000);
          putPixel(5, place+1, 0b01110011);
          fillPixel(5, place+2, 5, place+3, 0b01111111);
          putPixel(5, place+4, 0b01000010);
          break;
        case 9:
          putPixel(0, place+2, 0b00011101);
          putPixel(0, place+3, 0b01111111);
          putPixel(0, place+4, 0b00011111);
          putPixel(0, place+5, 0b00001100);
          fillPixel(1, place+1, 3, place+4, 0b01111111);
          putPixel(1, place+1, 0b00111000);
          putPixel(1, place+3, 0b01100011);
          putPixel(1, place+4, 0b01111011);
          putPixel(1, place+5, 0b01111111);
          putPixel(2, place+2, 0b01011111);
          putPixel(2, place+3, 0b00011100);
          putPixel(2, place+5, 0b01001111);
          putPixel(3, place+1, 0b01100000);
          putPixel(3, place+2, 0b01111011);
          putPixel(3, place+5, 0b00000010);
          putPixel(4, place+1, 0b00011000);
          putPixel(4, place+2, 0b01111111);
          putPixel(4, place+3, 0b01100111);
          putPixel(5, place, 0b00100000);
          putPixel(5, place+1, 0b01111111);
          putPixel(5, place+2, 0b01000110);
          break;
      }
}

/*
**
*/
void letters(byte place, char letter)
{
  switch (letter) {
        case 'A':
          putPixel(0, place+4, 0b00011101);
          putPixel(0, place+5, 0b00001100);
          putPixel(1, place+3, 0b01111101);
          fillPixel(1, place+4, 1, place+5, 0b01111111);
          putPixel(2, place+2, 0b01111101);
          putPixel(2, place+3, 0b01100111);
          putPixel(2, place+4, 0b01110011);
          putPixel(2, place+5, 0b01111111);
          putPixel(3, place+1, 0b00110000);
          putPixel(3, place+2, 0b01111111);
          putPixel(3, place+3, 0b00011100);
          putPixel(3, place+4, 0b01111101);
          putPixel(3, place+5, 0b01111111);
          putPixel(4, place+1, 0b01111101);
          putPixel(4, place+2, 0b01111111);
          putPixel(4, place+3, 0b01100011);
          putPixel(4, place+4, 0b01111011);
          putPixel(4, place+5, 0b01111111);
          putPixel(5, place,   0b00111100);
          putPixel(5, place+1, 0b01100111);
          putPixel(5, place+4, 0b01110011);
          putPixel(5, place+5, 0b01100111);
          break;

        case 'L':
          putPixel(0, place+4, 0b00011101);
          putPixel(0, place+5, 0b00001100);
          putPixel(1, place+3, 0b01111101);
          fillPixel(1, place+4, 1, place+5, 0b01111111);
          putPixel(2, place+2, 0b01111101);
          putPixel(2, place+3, 0b01100111);
          putPixel(2, place+4, 0b01110011);
          putPixel(2, place+5, 0b01111111);
          putPixel(3, place+1, 0b00110000);
          putPixel(3, place+2, 0b01111111);
          putPixel(3, place+3, 0b00011100);
          putPixel(3, place+4, 0b01111101);
          putPixel(3, place+5, 0b01111111);
          putPixel(4, place+1, 0b01111101);
          putPixel(4, place+2, 0b01111111);
          putPixel(4, place+3, 0b01100011);
          putPixel(4, place+4, 0b01111011);
          putPixel(4, place+5, 0b01111111);
          putPixel(5, place,   0b00111100);
          putPixel(5, place+1, 0b01100111);
          putPixel(5, place+4, 0b01110011);
          putPixel(5, place+5, 0b01100111);
          break;

         case 'S':
          putPixel(0, place+2, 0b00011000);
          fillPixel(0, place+3, 0, place+4, 0b000011101);
          putPixel(0, place+5, 0b00001100);

          putPixel(1, place+1, 0b01111101);
          putPixel(1, place+2, 0b01101111);
          putPixel(1, place+3, 0b01100011);
          putPixel(1, place+4, 0b01110011);
          putPixel(1, place+5, 0b01100111);

          putPixel(2, place+1, 0b01110011);
          putPixel(2, place+2, 0b00011111);
          putPixel(2, place+3, 0b00001100);

          putPixel(3, place+2, 0b01110000);
          putPixel(3, place+3, 0b01111111);
          putPixel(3, place+4, 0b00001110);

          putPixel(4, place+1, 0b00001000);
          putPixel(4, place+2, 0b00001000);
          putPixel(4, place+3, 0b01111001);
          putPixel(4, place+4, 0b01101111);

          putPixel(5, place,   0b01100000);
          putPixel(5, place+1, 0b01111111);
          putPixel(5, place+2, 0b01111111);
          putPixel(5, place+3, 0b01100111);
          putPixel(5, place+4, 0b00000010);
          break;

       case 'T':
          putPixel(0, place,   0b00011000);
          fillPixel(0, place+1, 0, place+4, 0b000011101);
          putPixel(0, place+5,   0b00001100);
          putPixel(1, place,   0b01100011);
          fillPixel(1, place+1, 1, place+5, 0b01100011);
          addPixel(1, place+2, 0b00010000);
          addPixel(1, place+3, 0b00011100);
          addPixel(1, place+4, 0b00000100);
          putPixel(2, place+2, 0b01111101);
          putPixel(2, place+3, 0b01111111);
          putPixel(3, place+2, 0b01111111);
          putPixel(3, place+3, 0b01001111);
          putPixel(4, place+1, 0b00110000);
          putPixel(4, place+2, 0b01111111);
          putPixel(4, place+3, 0b00000110);
          putPixel(5, place+1, 0b01110011);
          putPixel(5, place+2, 0b01100111);
          break;
  }
}

/*
** Refresh display data
*/
void refreshDisplays()
{
  for (int i = 1; i < 9; i++)
  {
    MAX7219Send(
        i, display_data[i - 1 + 40][3], i, display_data[i - 1 + 40][2], i, display_data[i - 1 + 40][1],
        i, display_data[i - 1 + 32][3], i, display_data[i - 1 + 32][2], i, display_data[i - 1 + 32][1],
        i, display_data[i - 1 + 24][3], i, display_data[i - 1 + 24][2], i, display_data[i - 1 + 24][1],
        i, display_data[i - 1 + 16][3], i, display_data[i - 1 + 16][2], i, display_data[i - 1 + 16][1],
        i, display_data[i - 1 + 8][3], i, display_data[i - 1 + 8][2], i, display_data[i - 1 + 8][1],
        i, display_data[i - 1][3], i, display_data[i - 1][2], i, display_data[i - 1][1]);
  }
}

/*
** Writes a value to all MAX7219 drivers
*/
void setDriverRegisters(uint8_t address, uint8_t value)
{
  MAX7219Send(
      address, value, address, value, address, value, address, value, address, value, address, value,
      address, value, address, value, address, value, address, value, address, value, address, value,
      address, value, address, value, address, value, address, value, address, value, address, value);
}

/*
** Sends values data for all display drivers
*/
void MAX7219Send(
    uint8_t address, uint8_t value,
    uint8_t addressb, uint8_t valueb,
    uint8_t addressc, uint8_t valuec,
    uint8_t addressd, uint8_t valued,
    uint8_t addresse, uint8_t valuee,
    uint8_t addressf, uint8_t valuef,
    uint8_t addressg, uint8_t valueg,
    uint8_t addressh, uint8_t valueh,
    uint8_t addressi, uint8_t valuei,
    uint8_t addressj, uint8_t valuej,
    uint8_t addressk, uint8_t valuek,
    uint8_t addressl, uint8_t valuel,
    uint8_t addressm, uint8_t valuem,
    uint8_t addressn, uint8_t valuen,
    uint8_t addresso, uint8_t valueo,
    uint8_t addressp, uint8_t valuep,
    uint8_t addressq, uint8_t valueq,
    uint8_t addressr, uint8_t valuer)
{

  digitalWrite(SPI_CS, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  SPI.transfer(addressb);
  SPI.transfer(valueb);
  SPI.transfer(addressc);
  SPI.transfer(valuec);
  SPI.transfer(addressd);
  SPI.transfer(valued);
  SPI.transfer(addresse);
  SPI.transfer(valuee);
  SPI.transfer(addressf);
  SPI.transfer(valuef);
  SPI.transfer(addressg);
  SPI.transfer(valueg);
  SPI.transfer(addressh);
  SPI.transfer(valueh);
  SPI.transfer(addressi);
  SPI.transfer(valuei);
  SPI.transfer(addressj);
  SPI.transfer(valuej);
  SPI.transfer(addressk);
  SPI.transfer(valuek);
  SPI.transfer(addressl);
  SPI.transfer(valuel);
  SPI.transfer(addressm);
  SPI.transfer(valuem);
  SPI.transfer(addressn);
  SPI.transfer(valuen);
  SPI.transfer(addresso);
  SPI.transfer(valueo);
  SPI.transfer(addressp);
  SPI.transfer(valuep);
  SPI.transfer(addressq);
  SPI.transfer(valueq);
  SPI.transfer(addressr);
  SPI.transfer(valuer);
  digitalWrite(SPI_CS, HIGH);
}
