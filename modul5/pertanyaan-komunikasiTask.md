# Jawaban Pertanyaan Praktikum Modul 5 - Komunikasi Task

**1. Apakah kedua task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!**

Penggunaan *queue* pada RTOS tidak menghentikan *multitasking*, melainkan menyediakan mekanisme komunikasi yang aman antar *task*. *Queue* bekerja sebagai media pertukaran data yang diatur langsung oleh RTOS sehingga akses data dilakukan secara bergantian dan terkontrol. Dengan cara ini, *race condition* dapat dihindari karena *task* tidak mengakses variabel yang sama secara langsung pada waktu bersamaan.

**2. Apakah program ini berpotensi mengalami *race condition*? Jelaskan!**

*Race condition* adalah kondisi ketika dua atau lebih *task* mengakses data yang sama sehingga data berpotensi tidak konsisten entah dalam pembacaan ataupun dalam penulisan data tersebut. Ketika melakukan komunikasi antar *task*, alih-alih menggunakan variabel global yang berpotensi besar menimbulkan *race condition* RTOS menyediakan mekanisme yang lebih terstruktur. *Queue*. Dengan *queue* satu *task* tidak akan "berebut" dalam membaca atau menulis nilai di dalam sebuah variabel. Ia akan membuat sebuah *handle* yang bisa bebas diakses oleh *task* dengan tetap mempertahankan konsistensi dari nilai pada variabel tersebut.  

**3. Modifikasilah program dengan menggunakan sensor DHT sesungguhnya sehingga informasi yang ditampilkan dinamis. Bagaimana hasilnya?**

```cpp
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <DHT.h>

// inisiasi pin DHT
#define DHTPIN 2 
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

struct readings
{
    float temp;
    float hum;
};

QueueHandle_t my_queue;

void read_data(void *pvParameters);
void display_data(void *pvParameters);

void setup()
{
  Serial.begin(9600);

  // Inisialisasi sensor DHT
  dht.begin();

  // Membuat queue
  my_queue = xQueueCreate(1, sizeof(struct readings));

  // Membuat task
  xTaskCreate(
    read_data, "Read Sensor", 128, NULL, 1, NULL);
  xTaskCreate(
    display_data, "Display Data", 128, NULL, 1, NULL);
}

void loop()
{
  
}

void read_data(void *pvParameters)
{
  struct readings data;

  for (;;)
  {
    // Membaca data dari DHT
    data.temp = dht.readTemperature();
    data.hum  = dht.readHumidity();

    // Validasi pembacaan sensor
    if (!isnan(data.temp) && !isnan(data.hum))
    {
      xQueueSend(my_queue, &data, portMAX_DELAY);
    }

    // Delay task 1 detik
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void display_data(void *pvParameters)
{
  struct readings receivedData;

  for (;;)
  {
    // Menerima data dari queue
    if (xQueueReceive(my_queue, &receivedData, portMAX_DELAY) == pdPASS)
    {
      Serial.print("Temperature : ");
      Serial.print(receivedData.temp);
      Serial.println(" C");

      Serial.print("Humidity    : ");
      Serial.print(receivedData.hum);
      Serial.println(" %");

      Serial.println("----------------------");
    }
  }
}
```

Setelah dimodifikasi menggunakan sensor DHT, sistem berhasil menampilkan data suhu dan kelembapan secara dinamis sesuai kondisi lingkungan nyata. *Task* pembacaan sensor bekerja mengambil data dari DHT lalu mengirimkannya ke *queue*, sedangkan *task display* menerima data tersebut dan menampilkannya melalui Serial Monitor. Penggunaan *queue* memungkinkan komunikasi antar *task* berlangsung secara aman dan sinkron tanpa menyebabkan *race condition*. Dengan pendekatan ini, sistem RTOS mampu menjalankan proses pembacaan sensor dan tampilan data secara *multitasking* dan lebih terstruktur dibanding program *sequential* biasa.