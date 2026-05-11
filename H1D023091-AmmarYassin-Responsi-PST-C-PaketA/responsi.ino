#include <Arduino.h>

const int segmentPins[8] = {7, 6, 5, 11, 10, 9, 8, 4};
const int btnUp = 2;
const int grnPin = 12;
const int redPin = 13;

bool lastUpState = HIGH;

byte digitPattern[16][8] = {
  {1,1,1,1,1,1,0,0}, // 0
  {0,1,1,0,0,0,0,0}, // 1
  {1,1,0,1,1,0,1,0}, // 2
  {1,1,1,1,0,0,1,0}, // 3
  {0,1,1,0,0,1,1,0}, // 4
  {1,0,1,1,0,1,1,0}, // 5
  {1,0,1,1,1,1,1,0}, // 6
  {1,1,1,0,0,0,0,0}, // 7
  {1,1,1,1,1,1,1,0}, // 8
  {1,1,1,1,0,0,1,1}, // 9
};

void displayDigit(int num) 
{
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(segmentPins[i], digitPattern[num][i]);
  }
}

void setup() {
  pinMode(btnUp, INPUT_PULLUP);
  pinMode(grnPin, OUTPUT);
  pinMode(redPin, OUTPUT);
}

void loop() {
  digitalWrite(grnPin, HIGH);

  bool upState = digitalRead(btnUp);
  if (lastUpState == HIGH && upState == LOW)
  {
    digitalWrite(redPin, HIGH);
    digitalWrite(grnPin, LOW);

    for (int i = 9; i >= 0; i--)
    {
      displayDigit(i);
      delay(1000);
    }
    
    digitalWrite(redPin, LOW);
    digitalWrite(grnPin, HIGH);
  }

  lastUpState = upState;
}
