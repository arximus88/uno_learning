#include <Arduino.h>
#include <IRremote.h> // IRremote library statement

int RECV_PIN = A2;    // define the pin of the IR receiver as A2
int LED = 9;
bool flag = 0;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
    Serial.begin(9600);
    pinMode(LED, OUTPUT); // set pins of LED as OUTPUT
    irrecv.enableIRIn();  // enable the receiver
}

// FF02FD is the value of OK key

// FF22DD is the value of LEFT key
// FFC23D is the value of RIGHT key
// FF629D is the value of UP key
// FFA857 is the value of DOWN key

// FF6897 is the value of 1 key
// FF9867 is the value of 2 key
// FFB04F is the value of 3 key
// FF30CF is the value of 4 key
// FF18E7 is the value of 5 key
// FF7A85 is the value of 6 key
// FF10EF is the value of 7 key
// FF38C7 is the value of 8 key
// FF5AA5 is the value of 9 key
// FF4AB5 is the value of 0 key

// FF42BD is the value of (*) CH+ key
// FF52AD is the value of (#) CH- key


void loop() {
    if (irrecv.decode(&results)) {
        if ((results.value == 0xFF02FD) && (flag == 0)) { // if OK key is pressed
            digitalWrite(LED, HIGH); // LED is on
            flag = 1;
        } else if ((results.value == 0xFF02FD) && (flag == 1)) { // press again
            digitalWrite(LED, LOW); // LED is off
            flag = 0;
        }
        irrecv.resume(); // receive next value
    }
}