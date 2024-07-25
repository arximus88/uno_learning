#include <Arduino.h>
#include <IRremote.h> // IRremote library statement

int RECV_PIN = 3; // define the pin of the IR receiver as A2
int LED = 9;
bool flag = 0;
IRrecv irrecv(RECV_PIN);
decode_results results;

// define the value of each key on the IR remote control
unsigned long KEY_OK = 0xFF02FD;
unsigned long KEY_LEFT = 0xFF22DD;
unsigned long KEY_RIGHT = 0xFFC23D;
unsigned long KEY_UP = 0xFF629D;
unsigned long KEY_DOWN = 0xFFA857;
unsigned long KEY_1 = 0xFF6897;
unsigned long KEY_2 = 0xFF9867;
unsigned long KEY_3 = 0xFFB04F;
unsigned long KEY_4 = 0xFF30CF;
unsigned long KEY_5 = 0xFF18E7;
unsigned long KEY_6 = 0xFF7A85;
unsigned long KEY_7 = 0xFF10EF;
unsigned long KEY_8 = 0xFF38C7;
unsigned long KEY_9 = 0xFF5AA5;
unsigned long KEY_0 = 0xFF4AB5;
unsigned long KEY_CH_UP = 0xFF42BD;
unsigned long KEY_CH_DOWN = 0xFF52AD;

// define the image of the dot matrix
unsigned char clear[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char smile[] = {0x00, 0x00, 0x1c, 0x02, 0x02, 0x02, 0x5c, 0x40, 0x40, 0x5c, 0x02, 0x02, 0x02, 0x1c, 0x00, 0x00};
unsigned char smile_c[] = {0x00, 0x00, 0x1c, 0x02, 0x0a, 0x02, 0x5c, 0x40, 0x40, 0x5c, 0x02, 0x0a, 0x02, 0x1c, 0x00, 0x00};
unsigned char smile_l[] = {0x00, 0x00, 0x1c, 0x02, 0x02, 0x0a, 0x5c, 0x40, 0x40, 0x5c, 0x02, 0x02, 0x0a, 0x1c, 0x00, 0x00};
unsigned char smile_r[] = {0x00, 0x00, 0x1c, 0x0a, 0x02, 0x02, 0x5c, 0x40, 0x40, 0x5c, 0x0a, 0x02, 0x02, 0x1c, 0x00, 0x00};

#define SCL_Pin A5 // set a pin of clock to A5
#define SDA_Pin A4 // set a data pin to A4

void setup()
{
    // set the pin to OUTPUT
    pinMode(SCL_Pin, OUTPUT);
    pinMode(SDA_Pin, OUTPUT);
    pinMode(LED, OUTPUT); // set pins of LED as OUTPUT
    irrecv.enableIRIn();  // enable the receiver
    // clear screen
    // matrix_display(clear);
}

// the condition that data starts transmitting
void IIC_start()
{
    digitalWrite(SDA_Pin, HIGH);
    digitalWrite(SCL_Pin, HIGH);
    delayMicroseconds(3);
    digitalWrite(SDA_Pin, LOW);
    delayMicroseconds(3);
    digitalWrite(SCL_Pin, LOW);
}

// the sign that transmission of data ends
void IIC_end()
{
    digitalWrite(SCL_Pin, LOW);
    digitalWrite(SDA_Pin, LOW);
    delayMicroseconds(3);
    digitalWrite(SCL_Pin, HIGH);
    delayMicroseconds(3);
    digitalWrite(SDA_Pin, HIGH);
    delayMicroseconds(3);
}

// transmit data
void IIC_send(unsigned char send_data)
{
    for (byte mask = 0x01; mask != 0; mask <<= 1) // each character has 8 digits, which is detected one by one
    {
        if (send_data & mask)
        { // set high or low levels in light of each bit(0 or 1)
            digitalWrite(SDA_Pin, HIGH);
        }
        else
        {
            digitalWrite(SDA_Pin, LOW);
        }
        delayMicroseconds(3);
        digitalWrite(SCL_Pin, HIGH); // pull up the clock pin SCL_Pin to end the transmission of data
        delayMicroseconds(3);
        digitalWrite(SCL_Pin, LOW); // pull down the clock pin SCL_Pin to change signals of SDA
    }
}

// this function is used for the display of dot matrix
void matrix_display(unsigned char matrix_value[])
{
    IIC_start();    // use the function to start transmitting data
    IIC_send(0xc0); // select an address

    for (int i = 0; i < 16; i++) // image data have 16 characters
    {
        IIC_send(matrix_value[i]); // data to transmit pictures
    }

    IIC_end(); // end the data transmission of pictures

    IIC_start();
    IIC_send(0x8A); // show control and select pulse width 4/16
    IIC_end();
}

void loop()
{

    if (irrecv.decode(&results))
    {
        if (results.value == KEY_OK)
        { // if OK key is pressed
            matrix_display(smile_c);
        }
        else if (results.value == KEY_LEFT)
        { // if LEFT key is pressed
            matrix_display(smile_l);
        }
        else if (results.value == KEY_RIGHT)
        { // if RIGHT key is pressed
            matrix_display(smile_r);
        }

        irrecv.resume(); // receive next value
    }
    delay(10); // delay 10ms
}