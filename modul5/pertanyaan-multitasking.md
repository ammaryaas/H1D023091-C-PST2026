# Jawaban Pertanyaan Praktikum Modul 5 - Multitasking

**1. Apakah ketiga task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!**

Dalam konsep RTOS pada arduino sebenarnya seluruh *task* tidak dikerjakan secara bersamaan secara literal, RTOS melakukan *context switching* dengan sangat cepat. Jika ada tiga *task* maka RTOS akan tetap menjalankan ketiga *task* tersebut secara bergantian satu per satu, hanya saja dilakukan dengan membagi waktu pada masing-masing *task* dan berpindah dari satu *task* ke *task* lain dengan sangat cepat. Dengan mekanisme ini sistem akan lebih responsif dan terorganisir.

**2. Bagaimana cara menambahkan task keempat? Jelaskan langkahnya!**

Langka pertama adalah membuat fungsi baru misalnya `void TaskLCD(void *pvParameters)` yang di dalamnya berisi program yang akan dijalankan oleh *task* tersebut. Selanjutnya fungsi tersebut perlu didaftarkan pada `setup()` sesuai dengan format berikut
```cpp
xTaskCreate(
  TaskLCD,     // fungsi task
  "task4",       // nama task
  128,           // ukuran stack
  NULL,          // parameter
  1,             // prioritas
  NULL           // task handle
);
```
Setelah *task* dibuat dan didaftarkan, maka sistem RTOS siap bekerja.

**3. Modifikasilah program dengan menambah sensor (misalnya potensiometer), lalu gunakan nilainya untuk mengontrol kecepatan LED! Bagaimana hasilnya?**

```cpp
#include <Arduino_FreeRTOS.h>

void TaskBlink1(void *pvParameters);
void TaskBlink2(void *pvParameters);
void TaskSensor(void *pvParameters); // inisialisasi fungsi baru
void Taskprint(void *pvParameters);

int delayLED = 0; // inisiasi variabel delay untuk LED

void setup()
{
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
    xTaskCreate(
        TaskBlink1, "task1", 128, NULL, 1, NULL);
    xTaskCreate(
        TaskBlink2, "task2", 128, NULL, 1, NULL);
    xTaskCreate(
        Taskprint, "task3", 128, NULL, 1, NULL);
    xTaskCreate(
      TaskSensor, "task4", 128, NULL, 1, NULL);
    vTaskStartScheduler();
}

void loop()
{

}

void TaskBlink1(void *pvParameters)
{
    pinMode(8, OUTPUT);
    while (1)
    {
        Serial.println("Task1");
        digitalWrite(8, HIGH);
        vTaskDelay(200 / portTICK_PERIOD_MS);
        digitalWrite(8, LOW);
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

void TaskBlink2(void *pvParameters)
{
    pinMode(7, OUTPUT);
    while (1)
    {
        Serial.println("Task2");
        digitalWrite(7, HIGH);
        vTaskDelay(delayLED / portTICK_PERIOD_MS); // ubah nilai delay menggunakan value dari sensor
        digitalWrite(7, LOW);
        vTaskDelay(delayLED / portTICK_PERIOD_MS); // ubah nilai delay menggunakan value dari sensor
    }
}

// task sensor untuk potensiometer
void TaskSensor(void *pvParameters)
{  
  Serial.print("Task4: ");
  delayLED = analogRead(A0); // ubah nilai dari variabel
  Serial.println(delayLED); // print nilai delay
  vTaskDelay(500 / portTICK_PERIOD_MS);
}

void Taskprint(void *pvParameters)
{
    int counter = 0;
    while (1)
    {
        counter++;
        Serial.println(counter);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
```