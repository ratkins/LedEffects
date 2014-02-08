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
    
    void calcFrame(int time) {
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                int16_t v = 0;
                
//                v += sin16(x * 1024 + time);
//                v += cos16(y * 2048 + time);
                
//                v = sin(10 *(x * sin(time / 2) + y * cos(time / 3)) + time)
                
                v += sin16(128 * (512 * x * sin16(time / 128) + 128 * y * cos16(time / 512)) + time);
                
                pixel(x, y) = CHSV((v >> 8) + 128, 255, 255);
            }
        }
        LEDS.show();
    }
    
    uint8_t sin8(uint16_t x) {
        return (sin16(x) >> 8) + 128;
    }
};


