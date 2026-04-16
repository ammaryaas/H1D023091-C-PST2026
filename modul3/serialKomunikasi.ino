#include <Arduino.h>

void setup()
{
  Serial.begin(9600);
  Serial.println("Ketik '1' untuk menyalakan LED, '0' untuk mematikan LED");
  pinMode(12, OUTPUT);
}

void loop()
{
  if (Serial.available() > 0) {
    char data = Serial.read();
    
    if (data == '1') {
      digitalWrite(12, HIGH);
      Serial.println("LED ON");
    } else if (data == '0') {
      digitalWrite(12, LOW);
      Serial.println("LED OFF");
    } else if (data != '\n' && data != '\r') {
      Serial.println("Perintah Tidak Dikenal!");
    }
  }
}