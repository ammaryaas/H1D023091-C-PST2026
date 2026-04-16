# Jawaban Pertanyaan Praktikum Modul 3 - I2C

**1. Jelaskan bagaimana cara kerja komunikasi I2C antara Arduino dan LCD pada rangkaian tersebut!**
LCD adalah perangkat keluaran (*slave*) yang dioperasikan melalui Arduino (*master*). Dengan menggunakan protokol I2C, LCD tidak lagi membutuhkan banyak pin sekaligus, ini sangat rapih dan menghemat banyak pin. Pada protokol I2C, pin yang dibutuhkan hanya 4 buah yang masing-masing adalah GND sebagai jalur referensi tegangan (0 volt), jalur pulang arus listrik, VCC yang memberikan tegangan 5 volt kepada Arduino dan lCD sebagai energi untuk menyalakannya, lalu ada SDA sebagai jalur pengiriman data yang terhubung melalui A4 pada Arduino, pin ini berfungsi untuk menentukan karakter yang akan ditampilkan dan yang terakhir ada SCl yang terhubung pada A5 pada Arduino sebagai jalur sinkronisasi waktu, pin ini menjaga data dibaca dan dikirim pada waktu yang tepat.

**2. Apakah pin potensiometer harus seperti itu? Jelaskan yang terjadi apabila pin kiri dan pin kanan tertukar!**
Tidak, pin kiri dan kanan potensiometer tidak harus selalu seperti itu. Susunan pada rangkaian tersebut adalah konfigurasi umum, tetapi secara elektrik pin kiri dan kanan bisa ditukar tanpa merusak rangkaian. Yang berubah hanyalah arah perubahan nilainya.

**3. Modifikasi program dengan menggabungkan antara UART dan I2C (keduanya sebagai output) sehingga:**
- Data tidak hanya ditampilkan di LCD tetapi juga di Serial Monitor
- Adapun data yang ditampilkan pada Serial Monitor sesuai dengan table berikut:
| ADC: 0 | Volt: 0.00 V | Persen: 0% |
Tampilan jika potensiometer dalam kondisi diputar paling kiri
- ADC: 0 0% | setCursor(0, 0) dan Bar (level) | setCursor(0, 1)
- Berikan penjelasan disetiap baris kode nya dalam bentuk README.md!
```cpp
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pinPot = A0;

// fungsi untuk merubah ADC menjadi voltase
float voltage (int adcValue) {
  return adcValue * (5.0/1023.0);
}

// fungsi untuk merubah ADC menjadi bentuk persen
float percentage (int adcValue) {
  return (adcValue/1023.0) * 100;
}

void setup() {
  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();
}

void loop() {
  int nilai = analogRead(pinPot);
  
  int panjangBar = map(nilai, 0, 1023, 0, 16);
  
  Serial.print("Nilai ADC: ");
  Serial.print(nilai);
  Serial.print("| ");
  
  Serial.print("Nilai Voltase: ");
  Serial.print(voltage(nilai)); // panggil fungsi dan print di serial
  Serial.print("| ");
  
  Serial.print("Nilai Persentase: ");
  Serial.print(percentage(nilai)); // panggil fungsi dan print di serial
  Serial.println("| ");
  
  lcd.setCursor(0,0);
  lcd.print("ADC: ");
  lcd.print(nilai);
  lcd.print(" ");
  
  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    if (i < panjangBar) {
      lcd.print((char)255);
    } else {
      lcd.print(" ");
    }
  }
  
  delay(200);
}
```

**4. Lengkapi table berikut berdasarkan pengamatan pada Serial Monitor**
 ADC | Volt(v) | Persen(%) |
 :--- | :--- | :--- |
1 | 0,005 | 0,10
21 | 0,103 | 2,05
49 | 0,240 | 4,79
74 | 0,362 | 7,23
96 | 0,469 | 9,38