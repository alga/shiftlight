/*
 *  Arduino shift light.
 *
 *  The LEDs turn on one by one and when the warning threshold is
 *  exceeded they all start to blink quickly.
 *
 *  Copyright (c) 2014 Albertas Agejevas <alga@pov.lt>
 *
 *  Permission is hereby granted, free of charge, to any person
 *  obtaining a copy of this software and associated documentation
 *  files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy,
 *  modify, merge, publish, distribute, sublicense, and/or sell copies
 *  of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *  DEALINGS IN THE SOFTWARE.
 *
 */

const int leds[] = {2, 3, 4, 5, 6};
const int threshholds[] = {4500, 5000, 5500, 6000, 6500};
const int num_leds = sizeof leds / sizeof *leds;
const int WARNING_THRESHOLD = 7000;
const int tach_pin = 12;
const int led_pin = 13;

unsigned long time, last_rise;
int interval = 0;


void update_leds(const int microseconds) {
        // 60 seconds, 2 sparks per rev
        long rpm = 60L * 1000000L / microseconds / 2;
        boolean blinker = true;
        unsigned long clock = millis();

        if (rpm > WARNING_THRESHOLD) {
                blinker = clock / 50 % 2; // Switch state 20 times a second
        }

        for (unsigned i = 0; i < num_leds; i++) {
                digitalWrite(leds[i], threshholds[i] < rpm && blinker);
        }
}


void setup() {
        for (unsigned i = 0; i < num_leds; i++) {
                pinMode(leds[i], OUTPUT);
        }
        pinMode(tach_pin, INPUT);
        pinMode(led_pin, OUTPUT);
        time = micros();
        last_rise = time;
}


boolean val = LOW, last_val = LOW;

void loop() {
        val = digitalRead(tach_pin);
        if (val == HIGH && last_val == LOW) {
                time = micros();
                interval = time - last_rise;
                last_rise = time;
        }

        update_leds(interval);
        digitalWrite(led_pin, val);
        last_val = val;
}
