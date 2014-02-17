//
//  Life.cpp
//  GauntletII
//
//  Created by Robert Atkins on 26/09/13.
//  Copyright (c) 2013 Robert Atkins. All rights reserved.
//

#import "Effect.h"

class Life : public Effect {
    
private:
    uint8_t density;
    uint16_t delta[36];
    
public:
    
    Life(CRGB *leds, int width, int height, int density): Effect(leds, width, height), density(density) {}
    
    void seed() {
        for (int i = 0; i < width * height; i++) {
            if (random(255) < density) {
                leds[i] = CHSV(0, 255, 255);
            }
        }
    }
    
    void start() {
        seed();
        uint8_t hue = 0;
        for (int time = 0; time < 128; time++) {
            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    int neighbours = numNeighbours(x, y);
                    if (pixel(x, y)) {
                        if (neighbours < 2 || neighbours > 3) {
                            pixel(x, y) = CHSV(0, 0, 0);
                        }
                    } else {
                        if (neighbours == 3) {
                            pixel(x, y) = CHSV(hue++, 255, 255);
                        }
                    }
                }
            }
            LEDS.show();
        }
        
        fadeout();
    }
    
    /*
    x - 1, y + 1|x = x, y + 1|x + 1, y + 1
    x - 1, y = y|      x     |x + 1, y = y
    x - 1, y - 1|x = x, y - 1|x + 1, y - 1
    */
    
    int numNeighbours(int x, int y) {
        int numNeighbours = 0;
        numNeighbours += alive(x - 1, y + 1) ? 1 : 0;
        numNeighbours += alive(x, y + 1) ? 1 : 0;
        numNeighbours += alive(x + 1, y + 1) ? 1 : 0;
        numNeighbours += alive(x - 1, y) ? 1 : 0;
        numNeighbours += alive(x + 1, y) ? 1 : 0;
        numNeighbours += alive(x - 1, y - 1) ? 1 : 0;
        numNeighbours += alive(x, y - 1) ? 1 : 0;
        numNeighbours += alive(x + 1, y - 1) ? 1 : 0;
        return numNeighbours;
    }
    
    bool alive(int x, int y) {
        return inXRange(x) && inYRange(y) && pixel(x, y);
    }
    
    // xxxx xxxx xxxx xxxx  xxxx xxxx xxxx xxxx
    // xxxx xxxx xxxx xxxx  xxxx xxxx xxxx xxxx
    
    void setChanged(int x, int y) {
        int index = y * 2;
        if (x < 16) {
            index += 0;
        } else if (x < 32) {
            index += 1;
        }
        delta[index] |= 1 << (x % 2);
    }
    
    void fadeout() {
        for (int brightness = 0; brightness < 256; brightness++) {
            for (int i = 0; i < width * height; i++) {
                leds[i]--;
            }
            LEDS.show();
        }
//        delay(10);
    }

};
