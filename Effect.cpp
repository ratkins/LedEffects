/*
 * The Effect implementation for the TechnocolourDreamcoat project.
 */

#include "Effect.h"

Effect::Effect(CRGB *leds, int width, int height): leds(leds), width(width), height(height) {}

bool Effect::inXRange(int x) {
    return x >= 0 && x < width;
}

bool Effect::inYRange(int y) {
    return y >= 0 && y < height;
}

struct CRGB& Effect::pixel(int x, int y) {
    if (x % 2 == 0) {
        return leds[(x * height) + y];
    } else {
        return leds[(x * height) + height - y - 1];
    }
}

void Effect::clearLeds() {
    memset8(leds, 0, width * height * 3);
}
