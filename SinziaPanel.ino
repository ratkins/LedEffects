#include <FastLED.h>

#include "Plasma.cpp"
#include "TestPattern.cpp"
#include "Snake.cpp"
#include "Twinkle.cpp"
#include "DeadChannel.cpp"
#include "Bouncy.cpp"
#include "HiRez.cpp"
#include "Boxes.cpp"

#define WIDTH 32
#define HEIGHT 18
#define NUM_LEDS WIDTH * HEIGHT

#define DATA_PIN 8

CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:

    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//    TestPattern testPattern(leds, WIDTH, HEIGHT);
//    testPattern.start();

//    Plasma2 plasma(leds, WIDTH, HEIGHT);
//    plasma.start();
    
//    Perlin perlin(leds, WIDTH, HEIGHT);
//    perlin.start();
    
//    Sprite sprite(leds, WIDTH, HEIGHT);
//    sprite.start();
    
//    SpaceInvader spaceInvader(leds, WIDTH, HEIGHT);
//    spaceInvader.start();


//    doDeadChannel();
//    doPlasma();
//    doTwinkle();
//    doSnake();
//    doBouncy();
//    doHiRez();
    doBoxes();
}

void doDeadChannel() {
    DeadChannel deadChannel(leds, WIDTH, HEIGHT);
    deadChannel.start();
}

void doPlasma() {
    Plasma plasma(leds, WIDTH, HEIGHT);
    plasma.start();
}

void doTwinkle() {
    Twinkle twinkle(leds, WIDTH, HEIGHT, true, true);
    twinkle.start();
}

void doSnake() {
    Snake snake(leds, WIDTH, HEIGHT);
    snake.start();
}

void doBouncy() {
    Bouncy bouncy(leds, WIDTH, HEIGHT);
    bouncy.start();
}

void doHiRez() {
    HiRez hiRez(leds, WIDTH, HEIGHT);
    hiRez.start();
}

void doBoxes() {
    Boxes boxes(leds, WIDTH, HEIGHT);
    boxes.start();
}
