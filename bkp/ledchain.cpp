#include <Arduino.h>

constexpr int BASE = 2;    // The I/O pin for the first LED
constexpr int NUM = 6;     // Number of LEDs
int ledDelay = 100;        // The delay time between LEDs

void setup() {
    Serial.begin(9600); // Set up Serial library at 9600 bps
    for (int i = BASE; i < BASE + NUM; i++) {
        pinMode(i, OUTPUT); // Set I/O pins as output
    }
}

void loop() {
    if (Serial.available() > 0) { // Check if data is available to read
        int val = Serial.read(); // Read the instruction or character from PC to Arduino
        switch (val) {
            case '1': ledDelay = 10; break;  // Set the delay time to 10ms
            case '2': ledDelay = 50; break;  // Set the delay time to 50ms
            case '3': ledDelay = 100; break; // Set the delay time to 100ms
            case '4': ledDelay = 200; break; // Set the delay time to 200ms
            case '5': ledDelay = 500; break; // Set the delay time to 500ms
        }
    }

    for (int i = BASE; i < BASE + NUM; i++) {
        digitalWrite(i, HIGH); // Turn on LED
        delay(ledDelay);       // Delay
        digitalWrite(i, LOW);  // Turn off LED
        delay(ledDelay);       // Delay
    }
}