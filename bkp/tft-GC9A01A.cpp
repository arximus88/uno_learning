#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_GC9A01A.h> // Hardware-specific library


	// 1.	CS (Chip Select): пін 10 на Arduino.
	// 2.	DC (Data/Command): пін 9 на Arduino.
	// 3.	RST (Reset): пін 8 на Arduino.
	// 4.	MOSI (Master Out Slave In): пін 11 на Arduino.
	// 5.	SCK (Serial Clock): пін 13 на Arduino.
	// 6.	GND (Ground): з’єднаний з GND на Arduino.
	// 7.	VCC (Power): з’єднаний з 5V на Arduino (перевірте, чи ваш дисплей підтримує 5V).

// Define color constants
#define GC9A01A_BLACK   0x0000
#define GC9A01A_WHITE   0xFFFF
#define GC9A01A_RED     0xF800
#define GC9A01A_GREEN   0x07E0
#define GC9A01A_BLUE    0x001F

// Pin definitions for the display
#define TFT_CS     10
#define TFT_RST    8   // Or set to -1 and connect to Arduino RESET
#define TFT_DC     9

// Display object
Adafruit_GC9A01A tft = Adafruit_GC9A01A(TFT_CS, TFT_DC, TFT_RST);

void setup(void) {
  Serial.begin(9600);
  
  // Initialize display
  tft.begin();

  // Clear the display
  tft.fillScreen(GC9A01A_BLACK);
}

void loop() {
  // Text output
  tft.setTextColor(GC9A01A_WHITE);
  tft.setTextSize(1);
  tft.setCursor(0, 0);
  tft.println("Display Active");

  // Draw a white circle
  tft.drawCircle(60, 60, 50, GC9A01A_WHITE);

  // Draw a red rectangle
  tft.drawRect(30, 30, 60, 60, GC9A01A_RED);

  // Draw a green triangle
  tft.drawTriangle(160, 120, 130, 180, 190, 180, GC9A01A_GREEN);

  // Draw a blue line
  tft.drawLine(0, 0, tft.width(), tft.height(), GC9A01A_BLUE);

  delay(5000);

  // Clear the screen before next draw cycle
  tft.fillScreen(GC9A01A_BLACK);

  delay(1000);
}