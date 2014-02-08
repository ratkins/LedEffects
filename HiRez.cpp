//
//  HiRez.cpp
//  GauntletII
//
//  Created by Robert Atkins on 26/09/13.
//  Copyright (c) 2013 Robert Atkins. All rights reserved.
//

#import "Effect.h"

class HiRez : public Effect {
    
private:
    
    uint16_t hiWidth, hiHeight;
    uint8_t hue;
    
public:
    
    HiRez(CRGB *leds, int width, int height): Effect(leds, width, height),
        hue(0),
        hiWidth(256 * width),
        hiHeight(256 * height)
    {
    }
        
    void start() {
//        lo();
        hi();
    }
    
    void lo() {
        for (int x = 0; x < width; x++) {
            pixel(x, 0) = CHSV(hue, 255, 255);
            LEDS.show();
            delay(256);
            pixel(x, 0) = CRGB::Black;
            LEDS.show();
        }
    }
    //
    // x x x x | x x x x | x x x x | x x x x
    
    void hi() {
        for (uint16_t x = 1; x < hiWidth; x++) {
            uint16_t actual = x >> 8;
            
            pixel(actual - 1, 0) = CHSV(hue, 255, 255 - x & 0xFF);
            pixel(actual, 0) = CHSV(hue, 255, x & 0xFF);
            LEDS.show();
        }
    }
};


