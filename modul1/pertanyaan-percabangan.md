# Jawaban Pertanyaan Praktikum Modul 1 - Percabangan

1. Pada kondisi apa program masuk ke blok `if` ?
```c
if (timeDelay <= 100>) {
```
ketika variabel `timedelay` memenuhi syarat (nilainya sama dengan atau kurang dari seratus).

2. Pada kondisi apa program masuk ke blok `else`?
```c
} else {
    timeDelay -= 100;
}
```
saat variabel `timeDelay` tidak lagi memenuhi syarat yang diberlakukan pada `if` sebelumnya.

3. Apa fungsi dari perintah `delay(timeDelay)`?
```cpp
delay(timeDelay)
```
fungsi `delay` akan melakukan penundaan (delay) sebanyak waktu sesuai dengan parameter yang dimasukkan pada fungsi tersebut.

4. Jika program yang dibuat memiliki alur mati → lambat → cepat → reset (mati), ubah menjadi LED tidak langsung reset → tetapi berubah dari cepat → sedang → mati
```c
const int ledPin = 4;
int timeDelay = 1000;
bool isReverse = false; //indikator apakah urutan akan mempercepat atau memperlambat
void setup() {
  pinMode(ledPin, OUTPUT);
}
void loop() {  
  // Nyalakan LED
  digitalWrite(ledPin, HIGH);
  delay(timeDelay);  
  // Matikan LED
  digitalWrite(ledPin, LOW);
  delay(timeDelay);  
  
  if (timeDelay <= 100) {
  	isReverse = true; // aktif ketika menyentuh angka 100 atau di bawahnya
  } else if (timeDelay >= 1000) {
    isReverse = false; //reset indikator isReverse
  	delay(3000); //jeda sebelum reset
    timeDelay = 1000; //reset waktu delay
  }
  
  if (isReverse == false) {
  	timeDelay -= 100; // percepatan berkala ketika isReverse tidak aktif
  } else {
  	timeDelay += 100; //perlambatan berkala ketika isReverse aktif
  }
}
```