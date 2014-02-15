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
    
public:
    
    Life(CRGB *leds, int width, int height): Effect(leds, width, height) {}
    
    void seed() {
        for (int i = 0; i < width * height; i++) {
            if (random(10) > 8) {
                leds[i] = CRGB::White;
            }
        }
    }
    
    void start() {
        seed();
        
        for (int time = 0; time < 1000; time++) {
            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    int neighbours = numNeighbours(x, y);
                    if (pixel(x, y) == (CRGB)CRGB::White) {
                        if (neighbours < 2 || neighbours > 3) {
                            pixel(x, y) = CRGB::Black;
                        }
                    } else if (neighbours == 3) {
                        pixel(x, y) = CRGB::White;
                    }
                }
            }
            LEDS.show();
        }
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
        if (inXRange(x) && inYRange(y)) {
            return pixel(x, y) == (CRGB)CRGB::White;
        }
    }

};
