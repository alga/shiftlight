/*
 *  Arduino shift light.
 *
 */

int leds[] = {2, 3, 4, 5, 6};
int threshholds[] = {4500, 5000, 5500, 6000, 6500};
int WARNING_THRESHOLD = 7000;
int tach = 12;

unsigned long time, last_rise;
int interval = 0;


void update_leds(const int microseconds) {
        // 60 seconds, 2 sparks per rev
        long rpm = 60L * 1000*1000 / microseconds / 2;
        boolean blinker = true;

        if (rpm > WARNING_THRESHOLD) {
                blinker = millis() / 50 % 2; // Switch state 20 times a second
        }

        for (unsigned i=0; i < sizeof leds; i++) {
                digitalWrite(leds[i], threshholds[i] < rpm && blinker);
        }
}


void setup() {
        for (unsigned i=0; i < sizeof leds; i++) {
                pinMode(leds[i], OUTPUT);
        }
        pinMode(7, INPUT);
        time = micros();
        last_rise = time;
}


boolean val = LOW, last_val = LOW;

void loop() {
        val = digitalRead(tach);
        if (val == HIGH && last_val == LOW) {
                time = micros();
                interval = time - last_rise;
                last_rise = time;
        }

        update_leds(interval);
        last_val = val;
}
