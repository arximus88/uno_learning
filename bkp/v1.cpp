#include <Arduino.h>

// The wiring of line tracking sensors
#define L_pin 11 // for the sensor in the left
#define M_pin 7 // for the sensor in the middle
#define R_pin 8 // for the sensor in the right

#define LED 9      // Define the LED pin

int sensorPin = A1;  // A1 is the input pin of photoresistor
int sensorValue = 0; // save the value of photoresistors
int outputValue = 0; // Value output to PMW

void setup()
{
    Serial.begin(9600);    // Set up Serial library at 9600 bps
    pinMode(LED, OUTPUT);  // Initialize the LED pin to output mode }
    pinMode(L_pin, INPUT); // Set all pins of the line tracking sensors to input mode
    pinMode(M_pin, INPUT);
    pinMode(R_pin, INPUT);
}

void loop()
{
    int sensorValue = analogRead(sensorPin);              // Зчитуємо значення з датчика
    int outputValue = map(sensorValue, 100, 600, 255, 0); // Перетворення значень для світлодіода

    // Обмеження значень щоб вони не виходили за межі
    outputValue = constrain(outputValue, 0, 255);

    int L_val = digitalRead(L_pin); // Read the value of the left sensor
    int M_val = digitalRead(M_pin); // Read the value of the middle sensor
    int R_val = digitalRead(R_pin); // Read the value of the right sensor
    Serial.print(L_val);
    Serial.print("  ");
    Serial.print(M_val);
    Serial.print("  ");
    Serial.print(R_val);
    Serial.println("  ");
    delay(50); // Delay in 500ms
}