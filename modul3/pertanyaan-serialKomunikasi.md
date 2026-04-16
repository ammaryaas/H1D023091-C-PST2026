# Jawaban Pertanyaan Praktikum Modul 3 - Serial Komunikasi

**1. Jelaskan proses dari input keyboard hingga LED menyala/mati!**
pertama-tama sirkuit akan terlebih dahulu menginisialisasi serial monitor sebagai media masukan yang terdapat pada `Serial.begin(9600);`. Selanjutnya pada potongan kode 
```cpp
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
```
akan dilakukan *if branching* untuk mengecek apakah ada *input* yang masuk ke dalamnya, jika masukan yang terbaca adalah `1` maka sirkuit akan menyalakan LED dan *print* LED ON pada *serial monitor*. Sedangkan jika masukan yang terbaca adalah `0` maka sirkuit akan mematikan LED dan *print* LED OFF pada *serial monitor*. 

**2. Mengapa digunakan `Serial.available()` sebelum membaca data? Apa yang terjadi jika baris tersebut dihilangkan?**
`Serial.available()` digunakan untuk melakukan pengecekan terlebih dahulu apakah ada data yang dikirim melalui *serial monitor*. Tanpa pengecekan ini, `Serial.read()` akan terus menerus berjalan tanpa adanya pengecekan terlebih dahulu. Selain dapat menyebabkan percabangan masuk ke kondisi `else`, ia juga dapat menambahkan beban CPU. Walaupun kecil, dalam sistem tertanam kompleks ini dapat berpengaruh.

**3. Modifikasi program agar LED berkedip (blink) ketika menerima input '2' dengan kondisi jika ‘2’ aktif maka LED akan terus berkedip sampai perintah selanjutnya diberikan**
```cpp
const int ledPin = 12;

int mode = 0; //0 untuk mati, 1 hidup, 2 berkedip

unsigned long previousMillis = 0; // inisialisasi millis awal
const long interval = 300; // waktu berkedip
bool ledState = LOW; // default state LED ketika berkedip

void setup()
{
  Serial.begin(9600);
  Serial.println("Ketik '1' untuk menyalakan LED, '0' untuk mematikan LED, '2' untuk mengedipkan LED");
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  if (Serial.available() > 0) {
    char data = Serial.read();

    if (data == '1') {
      mode = 1; // ganti ke mode 1 (hidup)
      Serial.println("LED ON");
    } else if (data == '0') {
      mode = 0; // ganti ke mode 0 (mati)
      Serial.println("LED OFF");
    } else if (data == '2') {
      mode = 2; // ganti ke mode 2 (berkedip)
      Serial.println("LED Blink");
    } else if (data != '\n' && data != '\r') {
      Serial.println("Perintah Tidak Dikenal!");
    }
  }
  
  if (mode == 0) {
    digitalWrite(ledPin, LOW);
  } else if (mode == 1) {
    digitalWrite(ledPin, HIGH);
  } else if (mode == 2) {
    unsigned long currentMillis = millis(); // inisialisasi millis saat ini
    // cek apakah waktu telah melewati interval kedip
    if (currentMillis - previousMillis >= interval) { 
      previousMillis = currentMillis; // menjaga pengecekan waktu saat ini untuk tetap tidak melebihi interval
      ledState = !ledState; // merubah state LED
      digitalWrite(ledPin, ledState);
    }
  }
}
```

**4. Tentukan apakah menggunakan delay() atau milis()! Jelaskan pengaruhnya terhadap sistem**
Menggunakan `millis()`. Sirkuit memiliki ketrbatasan tidak dapat membaca serial selama `delay()` dilakukan, sehingga ketika menggunakan `delay()` yang mana program membutuhkan *value* sebagai indikator dalam menjalankan *loop*, ia tidak dapat keluar dari *loop* tersebut karena kita perlu *value* yang berasal dari serial, bukan yang diciptakan secara otomatis. Akan tetapi dengan `millis()` Arduino dapat tetap menjalankan program dan membaca serial secara bersamaan.