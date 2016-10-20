

#include <Rainbowduino.h>
#include "cp437_font.h"


byte display[] = {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0
};

char vel[] = {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0
};

unsigned char RED[64] = {
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,238,221,204,188,171,154,137,119,102,85,
  68,51,34,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,17,35,52};

unsigned char GREEN[64] = {
  0,17,34,51,68,85,102,119,136,153,170,187,204,221,238,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,238,221,204,188,170,154,136,120,102,86,68,52,34,18,0,0,0,0};

unsigned char BLUE[64] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,18,34,52,68,86,102,120,136,154,170,188,
  204,221,238,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};

void setup() {
  Rb.init();

  for (unsigned char c = 0; c < 64; c++) {
    display[c] = (c % 8) + (c / 8) & B01111111;
    vel[c] = 1;
  }
}

void writeLetter(unsigned char ascii,unsigned int poX, unsigned int poY,  uint32_t colorRGB)
{
    if((ascii < 0x20)||(ascii > 0x7e))//Unsupported char.
    {
        ascii = '?';
    }
    for(unsigned char i=0;i<8;i++)
    {
        unsigned char temp = pgm_read_byte(&cp437_font[ascii-0x20][i]);
        for(unsigned char f=0;f<8;f++)
        {
            if((temp>>f)&0x01)
            {
                Rb.setPixelXY(poY+f, poX+i, colorRGB);
            }

        }
    }
}

void loop() {

  for ( unsigned char c = 0;c < 26;c++){
    
   //unsigned char ascii[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
   unsigned char ascii[26] = {'*','x','*','x','-','h','a','p',' ','p','y','h','a','l','o','w','e', ' ','e','n','-','0','x','*','x','*'};
   for (unsigned char x = 0; x < 8; x++) {

    unsigned char temp = pgm_read_byte(&cp437_font[ascii[c]-0x20][x]);
    
     for (unsigned char y = 0; y < 8; y++) {
        unsigned char ofs = (y << 3) + x;
        unsigned char hue = display[ofs];
        uint32_t colour = ((uint32_t)RED[hue] << 16) | ((uint32_t)GREEN[hue] << 8) | BLUE[hue];
        if((temp>>y)&0x01) {
          Rb.setPixelXY(y, x, colour);
        }
        
        hue = hue+vel[ofs];
        if (hue < 0 || hue > 63) {
          vel[ofs] = -vel[ofs];
          hue += vel[ofs];
        }
        display[ofs] = hue;
     }
   }
   
  delay(200);
  Rb.blankDisplay();
}
}
