# Jawaban Pertanyaan Praktikum Modul 2 - Output

**1. Gambarkan rangkaian schematic yang digunakan pada percobaan!**
**2. Apa yang terjadi jika nilai `num` lebih dari 15?**
```cpp
for (int i = 0; i < 16; i++)
{
    displayDigit(i);
    delay(1000);
}
```
fungsi `displayDigit(int num)` dideklarasikan pada 
```cpp
void displayDigit(int num) 
{
    for (int i = 0; i < 8; i++)
    {
        digitalWrite(segmentPins[i], digitPattern[num][i]);
    }
}
```
yang mana nilai `num` ini merujuk pada array dua dimensi `digitPattern` yang berisi *byte hexadecimal* untuk keluaran yang akan tampil pada *7 segments display*. Lalu apa yang akan terjadi ketika nilai `num` lebih dari 15? Ia akan mengakses *array* yang tidak ada (tidak didefinisikan pada `digitPattern`) sehingga *7 segments* akan menampilkan keluaran acak yang tidak beraturan.
**3. Apakah program ini menggunakan *common cathode* atau *common anode*? Jelaskan alasanya!** 
Program ini menggunakan *common cathode* karena penghubungnya menggunakan GND sebagai pin bersama yang nantinya akan terhubung juga memiliki logika nyala yang bernilai 1 atau HIGH.
**4. Modifikasi program agar tampilan berjalan dari F ke 0**
```c
const int segmentPins[8] = {7, 6, 5, 11, 10, 8, 9, 4};

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
}

void loop()
{
    for (int i = 15; i >= 0; i--) // nilai num diubah menjadi hitung mundur
    {
        displayDigit(i);
        delay(1000);
    }
}
```