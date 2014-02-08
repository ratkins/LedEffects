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
    int vx, vy, vx0, vy0;
    int x, y, x0, y0;
    
public:
    
    Bouncy(CRGB *leds, int width, int height): Effect(leds, width, height) {
      reset();
    }
    
    void reset() {
        ax = 0;
        ay = 1;
        
        vx0 = 0;
        vy0 = 1;
        
        x0 = 0;
        y0 = 0;
        
        x = 0;
        y = 0;
    }
    
    // http://stackoverflow.com/a/344632/17294
    void start() {
        Serial.println("Starting...");
        reset();
        
        for (int time = 0; time < 50; time++) {
          Serial.print(" t = "); Serial.println(time);          
          Serial.print(" y = "); Serial.println(y);
          Serial.print("vy = "); Serial.println(vy);
          Serial.print("ay = "); Serial.println(ay);

            x = x0 + vx * time + 0.5 * (ax * (time^2));
            y = y0 + vy * time + 0.5 * (ay * (time^2));
            vx = vx0 * ax * time;
            vy = vy0 * ay * time;
            
//            if (!inXRange(x)) {
//                vx = height;
//            }
            
//            if (!inYRange(y)) {
//                vy = -vy;
//            }
//            Serial.print("time = "); Serial.print(time); Serial.print(", x = "); Serial.print(x); Serial.print(", y = "); Serial.println(y);
            if (inXRange(x) && inYRange(y)) {
              pixel(x, y) = CRGB::White;
              LEDS.show();
              delay(50);
              pixel(x, y) = CRGB::Black;
              LEDS.show();
            }
            delay(1000);
        }
    }
};


