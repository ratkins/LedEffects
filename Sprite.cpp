/*
 * Circles implementation for the GauntletII project.
 */

#include "Effect.h"

#define SPRITE_WIDTH 9
#define SPRITE_HEIGHT 9

static uint8_t heartData[SPRITE_WIDTH * SPRITE_HEIGHT] = {
    
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

class Sprite : public Effect {

   
private:
    
    int spriteWidth, spriteHeight;
    

public:
    Sprite(CRGB *leds, int width, int height) : Effect(leds, width, height), spriteWidth(SPRITE_WIDTH), spriteHeight(SPRITE_HEIGHT) {
    }
    
    void start() {
        for (int i = 0; i < 1000; i++) {
            blit(heartData, random(0, width - spriteWidth), random(0, height));
            LEDS.show();
            delay(100);
            for (int i = 0; i < width * height; i++) {
                leds[i] %= 196;
            }
        }
    }
    
    void blit(uint8_t *sprite, int x, int y) {
        uint8_t saturation = random(8, 16) * 16;
        for (int spx = 0; spx < spriteWidth; spx++) {
            for (int spy = 0; spy < spriteHeight; spy++) {
                if (inXRange(spx + x) && inYRange(spy + y)) {
                    uint8_t spritePixel = sprite[spy * spriteHeight + spx];
                    if (spritePixel) {
                        pixel(spx + x, spy + y) = CHSV(0, saturation, spritePixel);
                    }
                }
            }
        }
    }
};

