# Jawaban Pertanyaan Praktikum Modul 2 - Input

**1. Gambarkan rangkaian schematic yang digunakan pada percobaan!**
<img width="506" height="392" alt="schematic input" src="https://github.com/user-attachments/assets/15ceddff-5f15-44d2-8818-7eb92984b3b9" />

**2. Mengapa pada *push button* digunakan mode `INPUT_PULLUP` pada Arduino Uno? Apa keuntungannya dibandingkan rangkaian biasa?**
```cpp
pinMode(btnUp, INPUT_PULLUP);
```
Mode `INPUT_PULLUP` digunakan pada Arduino untuk mengaktifkan resistor *pull-up* internal, memastikan pin input bernilai `HIGH` (logika 1) saat tombol tidak ditekan, dan `LOW` (logika 0) saat ditekan. Ini menghilangkan kebutuhan komponen eksternal (resistor), menyederhanakan rangkaian, menghemat ruang di *breadboard*, serta mencegah sinyal *floating* yang tidak stabil.

**3. Jika salah satu LED segmen tidak menyala, apa saja kemungkinan penyebabnya dari sisi hardware maupun software?**
- kesalahan konfigurasi pin
- pin belum terinisialisasi
- kode mengakses LED yang belum dikonfigurasi
- komponen rusak

**4. Modifikasi rangkaian dan program dengan dua push button yang berfungsi sebagai penambahan (increment) dan pengurangan (decrement) pada sistem counter**
```c
#include <Arduino.h>

const int segmentPins[8] = {7, 6, 5, 11, 10, 8, 9, 4};
const int btnUp = 3;
const int btnDown = 2; // button untuk mengubah ke indeks bawah

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
    {1,1,1,1,0,1,1,0}, // 9
    {1,1,1,0,1,1,1,0}, // A
    {0,0,1,1,1,1,1,0}, // b
    {1,0,0,1,1,1,0,0}, // C
    {0,1,1,1,1,0,1,0}, // d
    {1,0,0,1,1,1,1,0}, // E
    {1,0,0,0,1,1,1,0}  // F
};
int currentDigit = 0;
bool lastUpState = HIGH;
bool lastDownState = HIGH; // state default untuk button

void displayDigit(int num) 
{
  for (int i = 0; i < 8; i++)
  {
      digitalWrite(segmentPins[i], digitPattern[num][i]);
  }
}

void setup()
{
  for (int i = 0; i < 8; i++)
  {
      pinMode(segmentPins[i], OUTPUT);
  }

  pinMode(btnUp, INPUT_PULLUP);
  pinMode(btnDown, INPUT_PULLUP); // inisiasi button down
  displayDigit(currentDigit);
}

void loop(){
  bool upState = digitalRead(btnUp);
  bool downState = digitalRead(btnDown); // baca keadaan tombol saat ini
  if (lastUpState == HIGH && upState == LOW)
  {
      currentDigit++;
      if (currentDigit > 15){
          currentDigit = 0;
      }
      displayDigit(currentDigit);
  }
  
  if (lastDownState == HIGH && downState == LOW)
  {
  	currentDigit--; // mengurangi indeks
    if (currentDigit < 0){
      currentDigit = 15; // reset ke indeks ke 15 setelah menyentuh indeks ke-0
    }
    displayDigit(currentDigit);
  }
    
  lastUpState = upState;
  lastDownState = downState;
}
```
