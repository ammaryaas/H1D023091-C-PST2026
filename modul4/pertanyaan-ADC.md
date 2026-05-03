# Jawaban Pertanyaan Praktikum Modul 4 - ADC

**1. Apa fungsi perintah `analogRead()` pada rangkaian praktikum ini?**

Perintah `analogRead()` adalah perintah untuk membaca data analog yang dimasukkan — dalam hal ini adalah *potentiometer* sebagai masukannya. Sebelum diubah menjadi *digital* sinyal analog ini perlu dibaca dan disimpan, perintah `analogRead()` inilah yang berfungsi sebagai kode untuk membaca sinyal tersebut.

**2. Mengapa diperlukan fungsi map() dalam program tersebut?**

Fungsi `map()` pada kode tersebut digunakan sebagai *converter* rentang nilai — mengubah suatu nilai dari suatu skala ke skala yang lain. Cara kerjanya cukup sederhana fungsi `map()` akan membaca nilai minimal dan maksimal dari kedua skala lalu melakukan interpolasi linear. Bentuk umumnya adalah sebagai berikut
```cpp
map(x, in_min, in_max, out_min, out_max)
```
yang mana x ini adalah variabel nilai input `(in_min, in_max)` yang akan diubah secara proporsional ke dalam rentang nilai keluaran `(out_min, out_max)`. Fungsi `map()` digunakan untuk mengubah nilai hasil pembacaan ADC dari *potentiometer* (0–1023) menjadi sudut yang dapat dipahami oleh servo (0–180 derajat). Proses ini memastikan bahwa setiap perubahan posisi *potentiometer* akan diterjemahkan secara proporsional menjadi pergerakan servo, sehingga sistem dapat bekerja dengan akurat dan stabil.

**3. Modifikasi program berikut agar servo hanya bergerak dalam rentang 30° hingga 150°, meskipun potensiometer tetap memiliki rentang ADC 0–1023.**

```cpp
#include <Servo.h> 

Servo myservo;

// ===================== PIN SETUP =====================
// Tentukan pin yang digunakan untuk potensiometer dan servo
const int potensioPin = A0;
const int servoPin = 3;

// ===================== VARIABEL =====================
// Variabel untuk menyimpan data ADC dan sudut servo
int pos = 0;
int val = 0;

void setup() {

  // Hubungkan servo ke pin yang sudah ditentukan
  myservo.attach(servoPin);

  // Aktifkan komunikasi serial untuk monitoring
  Serial.begin(9600);

}

void loop() {

  // ===================== PEMBACAAN ADC =====================
  // Baca nilai dari potensiometer (rentang 0–1023)
  val = analogRead(potensioPin);

  // ===================== KONVERSI DATA =====================
  // Ubah nilai ADC menjadi sudut servo (0–180 derajat)
  pos = map(val,
             0,   
             1023,
             30,    // ganti nilai minimum servo menjadi 30 
             150);  // ganti nilai maksimum servo menjadi 150

  // ===================== OUTPUT SERVO =====================
  // Gerakkan servo sesuai hasil mapping
  myservo.write(pos); 

  // ===================== MONITORING DATA =====================
  // Tampilkan data ADC dan sudut servo ke Serial Monitor
  Serial.print("ADC Potensio: ");
  Serial.print(val); 

  Serial.print(" | Sudut Servo: ");
  Serial.println(pos);

  // ===================== STABILISASI =====================
  // Delay untuk memberi waktu servo bergerak stabil
  delay(500); 
}
```