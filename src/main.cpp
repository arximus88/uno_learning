#include <Arduino.h>

int signal = 0; // Змінна для зберігання даних

void setup() {
  Serial.begin(9600); // Ініціалізація серійного з'єднання на швидкості 9600 бод
}

void loop() {
  Serial.println("Hello from Arduino №" + String(signal)); // Виводимо повідомлення
  signal++; // Збільшуємо значення змінної на 1
  delay(1000); // Затримка в 1 секунду
}