#include <Arduino.h>
#include <IRremote.h> // IRremote library statement

#define light_L_Pin A2 // Use pin D3 for the left photosensitive sensor
#define light_R_Pin A1 // Define the pin of the photosensitive sensor on the right
#define ML_Ctrl 4      // Define the direction control pin of the left motor
#define ML_PWM 5       // Define the PWM control pin of the left motor
#define MR_Ctrl 2      // Define the direction control pin of the right motor
#define MR_PWM 6       // Define the PWM control pin of the right motor
#define RECV_PIN 3    // Define the pin of the IR receiver
#define SCL_Pin A5     // set a pin of clock to A5
#define SDA_Pin A4     // set a data pin to A4

int left_light;
int right_light;

bool allow_move = false;

IRrecv irrecv(RECV_PIN);
decode_results results;

unsigned long KEY_ASTERISK = 0xFF42BD;
unsigned char robo_on[] = {0x00, 0x00, 0x1c, 0x02, 0x02, 0x02, 0x5c, 0x40, 0x40, 0x5c, 0x02, 0x02, 0x02, 0x1c, 0x00, 0x00};
unsigned char robo_off[] = {0x00, 0x00, 0x22, 0x14, 0x08, 0x14, 0xa2, 0x80, 0x80, 0xa2, 0x14, 0x08, 0x14, 0x22, 0x00, 0x00};
unsigned char clear[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void Car_front() { // Move forward
    digitalWrite(MR_Ctrl, LOW);
    analogWrite(MR_PWM, 200);
    digitalWrite(ML_Ctrl, LOW);
    analogWrite(ML_PWM, 200);
}

void Car_left() { // Turn left
    digitalWrite(MR_Ctrl, LOW);
    analogWrite(MR_PWM, 200);
    digitalWrite(ML_Ctrl, HIGH);
    analogWrite(ML_PWM, 200);
}

void Car_right() { // Turn right
    digitalWrite(MR_Ctrl, HIGH);
    analogWrite(MR_PWM, 200);
    digitalWrite(ML_Ctrl, LOW);
    analogWrite(ML_PWM, 200);
}

void Car_Stop() { // Stop
    digitalWrite(MR_Ctrl, LOW);
    analogWrite(MR_PWM, 0);
    digitalWrite(ML_Ctrl, LOW);
    analogWrite(ML_PWM, 0);
}

void IIC_start() {
    pinMode(SDA_Pin, OUTPUT);
    pinMode(SCL_Pin, OUTPUT);
    digitalWrite(SDA_Pin, HIGH);
    digitalWrite(SCL_Pin, HIGH);
    delayMicroseconds(3);
    digitalWrite(SDA_Pin, LOW);
    delayMicroseconds(3);
    digitalWrite(SCL_Pin, LOW);
}

void IIC_end() {
    digitalWrite(SCL_Pin, LOW);
    digitalWrite(SDA_Pin, LOW);
    delayMicroseconds(3);
    digitalWrite(SCL_Pin, HIGH);
    delayMicroseconds(3);
    digitalWrite(SDA_Pin, HIGH);
    delayMicroseconds(3);
}

void IIC_send(unsigned char send_data) {
    for (byte mask = 0x01; mask != 0; mask <<= 1) { // each character has 8 digits, which is detected one by one
        if (send_data & mask) { // set high or low levels in light of each bit(0 or 1)
            digitalWrite(SDA_Pin, HIGH);
        } else {
            digitalWrite(SDA_Pin, LOW);
        }
        delayMicroseconds(3);
        digitalWrite(SCL_Pin, HIGH); // pull up the clock pin SCL_Pin to end the transmission of data
        delayMicroseconds(3);
        digitalWrite(SCL_Pin, LOW); // pull down the clock pin SCL_Pin to change signals of SDA
    }
}

void matrix_display(unsigned char matrix_value[]) {
    IIC_start(); // use the function to start transmitting data
    IIC_send(0xc0); // select an address

    for (int i = 0; i < 16; i++) { // image data have 16 characters
        IIC_send(matrix_value[i]); // data to transmit pictures
    }

    IIC_end(); // end the data transmission of pictures

    IIC_start();
    IIC_send(0x8A); // show control and select pulse width 4/16
    IIC_end();
}

void setup() {
    Serial.begin(9600);
    pinMode(light_L_Pin, INPUT);
    pinMode(light_R_Pin, INPUT);
    pinMode(ML_Ctrl, OUTPUT);
    pinMode(ML_PWM, OUTPUT);
    pinMode(MR_Ctrl, OUTPUT);
    pinMode(MR_PWM, OUTPUT);
    irrecv.enableIRIn(); // enable the receiver
    matrix_display(clear); // Display initial image
    matrix_display(robo_off); // Display initial image
}

void loop() {
    if (irrecv.decode(&results)) {
        if (results.value == KEY_ASTERISK) { // if Asterisk key is pressed, toggle the allow_move state
            allow_move = !allow_move;
            Serial.print("allow_move = ");
            Serial.println(allow_move);
            if (allow_move) {
                matrix_display(robo_on);
            } else {
                matrix_display(robo_off);
            }
        }
        irrecv.resume(); // receive next value
    }

    left_light = analogRead(light_L_Pin);
    right_light = analogRead(light_R_Pin);
    Serial.print("left_light_value = ");
    Serial.println(left_light);
    Serial.print("right_light_value = ");
    Serial.println(right_light);

    if (allow_move) {
        if (left_light > 750 && right_light > 750) { // Range value detected by the photosensitive sensor, move forward
            Car_front();
        } else if (left_light > 750 && right_light <= 750) { // Range value detected by the photosensitive sensor, turn left
            Car_left();
        } else if (left_light <= 750 && right_light > 750) { // Range value detected by the photosensitive sensor, turn right
            Car_right();
        } else { // In other conditions stop
            Car_Stop();
        }
    } else {
        Car_Stop(); // Ensure the car is stopped if movement is not allowed
    }
}