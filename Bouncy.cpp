//
//  Bouncy.cpp
//  GauntletII
//
//  Created by Robert Atkins on 26/09/13.
//  Copyright (c) 2013 Robert Atkins. All rights reserved.
//

#import "Effect.h"

class Bouncy : public Effect {
    
private:
    int ax, ay;
    int vx, vy;
    int x, y;
    
public:
    
    Bouncy(CRGB *leds, int width, int height): Effect(leds, width, height) {
        ax = 0;
        ay = -9;
        
        vx = 0;
        vy = 5;
        
        x = 0;
        y = 17;
    }
    
    void start() {
        Serial.println("Starting...");
        for (int time = 0; time < 50; time++) {
            x = x + vx * time + 0.5 * (ax * (time^2));
            y = y + vy * time + 0.5 * (ay * (time^2));
            vx = vx * ax * time;
            vy = vy * ay * time;
            
//            if (!inXRange(x)) {
//                vx = height;
//            }
            
//            if (!inYRange(y)) {
//                vy = -vy;
//            }
            Serial.print("x = "); Serial.print(x); Serial.print(", y = "); Serial.println(y);
            pixel(x, y) = CRGB::White;
            LEDS.show();
            delay(50);
            pixel(x, y) = CRGB::Black;
            LEDS.show();
        }
    }
    
};


