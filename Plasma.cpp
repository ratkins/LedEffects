//
//  Plasma.cpp
//  GauntletII
//
//  Created by Robert Atkins on 26/09/13.
//  Copyright (c) 2013 Robert Atkins. All rights reserved.
//

#import "Effect.h"

class Plasma : public Effect {
    
public:
    
    Plasma(CRGB *leds, int width, int height): Effect(leds, width, height) {
    }
    
    void start() {
        bool direction = true;
        int increment = 16;
        for (uint16_t time = 0;; time += 128 /*(sin8(time)*/) {
            calcFrame(time);
        }
    }
    //sin(distance(x, y, (128 * sin(-t) + 128), (128 * cos(-t) + 128)) / 40.74)
    
    // v = sin(10 * (x * sin(time / 2) + y * cos(time / 3)) + time)
    
    void calcFrame(int time) {
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                int16_t v = 0;
                uint16_t wibble = sin8(time);
                v += sin16(x * wibble * 8 + time);
                v += cos16(y * (128 - wibble) * 4 + time);
                v += sin16(y * x * cos8(-time) / 2);
                
                
//                v += sin16((1024 * x * sin16(time) + 2048 * y * cos16(time)) + time);
    
//                v += sin16(1024 * distance(512 * x, 1024 * y, sin16(-time), cos16(-time)) / 128);
                pixel(x, y) = CHSV((v >> 8) + 128, 255, 255);
            }
        }
        LEDS.show();
    }
    
    int16_t distance(int x1, int y1, int x2, int y2) {
        return sqrt((x2 - x1)^2 + (y1 - y2)^2);
    }
    
    uint8_t sin8(uint16_t x) {
        return (sin16(x) >> 8) + 128;
    }
    
    uint8_t cos8(uint16_t x) {
        return (cos16(x) >> 8) + 128;
    }

};


