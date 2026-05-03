**1. Jelaskan mengapa LED dapat diatur kecerahannya menggunakan fungsi `analogWrite()`!**

*Pulse Width Modulation*, konsep ini memungkinkan sinyal *digital* yang hanya menerima masukan berupa 0 (off) dan 1 (on) menjadi nilai tengah rata-rata yang lebih bervariasi dengan memanfaatkan sinyal analog. Sehingga alih-alih hanya menerima masukan untuk menyala dan mati, lampu dapat diatur kecerahannya menggunakan konsep PWM ini. 

**2. Apa hubungan antara nilai ADC (0–1023) dan nilai PWM (0–255)?**

Masing-masing nilai tersebut adalah representasi dari masing-masing *power* yang dapat dikeluarkan. Hubungan antara nilai ADC (0–1023) dan PWM (0–255) adalah hubungan linier skala, di mana nilai ADC 10-bit (\$2^{10}\$=1024 level) dikonversi menjadi nilai PWM 8-bit (\$2^8\$=256 level) dengan cara membaginya dengan empat (ADC : 4 = PWM). Hal ini sering digunakan untuk mengatur intensitas (LED/Motor) berdasarkan *input* sensor.

**3. Modifikasilah program berikut agar LED hanya menyala pada rentang kecerahan sedang, yaitu hanya ketika nilai PWM berada pada rentang 50 sampai 200.**

```cpp
// ===================== PIN SETUP =====================
// Tentukan pin yang digunakan untuk potensiometer dan LED PWM
const int potPin = A0;   
const int ledPin = 3;   

// ===================== VARIABEL =====================
// Variabel untuk menyimpan hasil pembacaan dan konversi PWM
int nilaiADC = 0;  
int pwm = 0;       

void setup() {

  // ===================== OUTPUT SETUP =====================
  // Atur pin LED sebagai output
  pinMode(ledPin, OUTPUT);

  // ===================== SERIAL MONITOR =====================
  // Aktifkan komunikasi serial untuk melihat data pembacaan
  Serial.begin(9600);
}

void loop() {

  // ===================== PEMBACAAN SENSOR =====================
  // Baca nilai analog dari potensiometer (rentang 0–1023)
  nilaiADC = analogRead(potPin); 

  // ===================== PEMROSESAN DATA (SCALING) =====================
  // Ubah nilai ADC (0–1023) menjadi nilai PWM (0–255)
  pwm = map(nilaiADC,
            0,   
            1023,
            50,   // ubah rentang nilai PWM menjadi 50-200
            200);  

  // ===================== OUTPUT PWM =====================
  // Kirim sinyal PWM ke LED (mengatur kecerahan)
  analogWrite(ledPin, pwm); 

  // ===================== MONITORING DATA =====================
  // Tampilkan data ADC dan PWM ke Serial Monitor
  Serial.print("ADC: ");
  Serial.print(nilaiADC);

  Serial.print(" | PWM: ");
  Serial.println(pwm); 

  // ===================== STABILISASI SISTEM =====================
  // Delay untuk menstabilkan pembacaan dan tampilan data
  delay(50); 
}
```
