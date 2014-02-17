//
//  Life.cpp
//  GauntletII
//
//  Created by Robert Atkins on 26/09/13.
//  Copyright (c) 2013 Robert Atkins. All rights reserved.
//

#import "Effect.h"

const int deltaLen = 36;

class Life : public Effect {
    
private:
    
    uint8_t density;
    uint16_t delta[deltaLen];
    
public:
    
    Life(CRGB *leds, int width, int height, int density): Effect(leds, width, height), density(density) {}
    
    void seed() {
        for (int i = 0; i < width * height; i++) {
            if (random(255) < density) {
                leds[i] = CRGB::White;
            }
        }
    }
    
    void start() {
        memset8(delta, 0, deltaLen);
        
        seed();
        uint8_t hue = 0;
        for (int time = 0; time < 128; time++) {
            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    int neighbours = numNeighbours(x, y);
                    if (pixel(x, y)) {
                        if (neighbours < 2 || neighbours > 3) {
                            setChanged(x, y);
                        }
                    } else {
                        if (neighbours == 3) {
                            setChanged(x, y);
                        }
                    }
                }
            }
            updateWithChanges();
            for (int i = 0; i < deltaLen; i++) {
                delta[i] = 0;
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
        delta[deltaIndex(x, y)] |= 1 << (x < 16 ? x : x - 16);
    }
    
    void updateWithChanges() {
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                if (delta[deltaIndex(x, y)] & (1 << (x < 16 ? x : x - 16))) {
                    if (pixel(x, y)) {
                        pixel(x, y) = CRGB::Black;
                    } else {
                        pixel(x, y) = CRGB::White;
                    }
                }
            }
        }
    }
    
    int deltaIndex(int x, int y) {
        return y * 2 + (x < 16 ? 0 : 1);
    }
    
    void fadeout() {
        for (int brightness = 0; brightness < 256; brightness++) {
            for (int i = 0; i < width * height; i++) {
                leds[i]--;
            }
            LEDS.show();
        }
    }

};
