/*
 Rainbowduino v3.0 Library examples modefied:

 Print 8x8 RGB Sprites on 2D plane
 Sprites derived from image. and stored in 
 sprites.h a array
 
*/

#include <Rainbowduino.h>
#include "sprites.h"


void drawSpriteRGB(unsigned char x)
{
   int sprite_nr = x;
   int row = sprite_nr / 5;
   int column = sprite_nr * 8;
   byte temp[3];
   for (unsigned char b=0;b<8;b++)
   {
      for(unsigned char d=0;d<8;d++)
          {
               int line = 40 * b + 280 * row;
               int offset = line + column + d;
               int colorOffset = 1600; 
               temp[0] = pgm_read_byte(&sprites[offset]);
               temp[1] = pgm_read_byte(&sprites[colorOffset+offset]);
               temp[2] = pgm_read_byte(&sprites[(colorOffset*2)+offset]);
               Rb.setPixelXY(b,d,temp[0],temp[1],temp[2]);
          }
         
   }
   
}


void setup()
{
  Rb.init();
}

void loop()
{
//   for(unsigned char x=0;x<25;x++)
  //   {
        drawSpriteRGB(random(26)-1);
        delay(random(3000)+500);
        Rb.blankDisplay();
    // }
  
}




