/*
 * Effect implementation for LEDEffects.
 */

#import "Effect.h"

class Plasma : public Effect {
    
public:
    
    Plasma(CRGB *leds, int width, int height) : Effect(leds, width, height) {
    }
    
    void start() {
        for (uint16_t time = 0, cycles = 0; cycles < 2048; time += 128, cycles++) {
            calcFrame(time);
        }
    }
    
    void calcFrame(int time) {
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                int16_t v = 0;
                uint16_t wibble = sin8(time);
                v += sin16(x * wibble * 8 + time);
                v += cos16(y * (128 - wibble) * 4 + time);
                v += sin16(y * x * cos8(-time) / 2);
                
                pixel(x, y) = CHSV((v >> 8) + 127, 255, 255);
            }
        }
        LEDS.show();
    }
    
    uint8_t sin8(uint16_t x) {
        return (sin16(x) >> 8) + 128;
    }
    
    uint8_t cos8(uint16_t x) {
        return (cos16(x) >> 8) + 128;
    }

};


