# 🌐 ESP32 Smart IoT Dashboard (AP • STA • MQTT)

Sistem IoT berbasis **ESP32** yang mendukung **multi-mode koneksi** (Access Point, Station, dan MQTT Cloud) untuk monitoring sensor dan kontrol perangkat secara realtime, baik lokal maupun melalui internet. Mendukung banyak perangkat sekaligus untuk terhubung, monitoring, dan mengontrol (bergantian) secara langsung.

---

## 🚀 Fitur Utama

* 📡 Monitoring jarak (HC-SR04) secara realtime
* 📊 Grafik data sensor live
* 🎮 Kontrol RGB LED (Web & MQTT)
* 🔁 Auto reconnect WiFi & MQTT
* 🌐 Dual Mode WiFi:

  * **AP Mode** → akses langsung tanpa internet
  * **STA Mode** → terhubung ke WiFi rumah
* ☁️ MQTT Cloud (HiveMQ) → akses global
* 🔄 Dual Communication:

  * **WebSocket (lokal / AP)**
  * **MQTT (internet / cloud)**

---

## 🧠 Arsitektur Sistem

### 🔹 Mode Lokal (AP / STA)

```id="ars1"
User → ESP32 (WebSocket) → Sensor & LED
```

### 🔹 Mode Internet (Cloud)

```id="ars2"
ESP32 → MQTT Broker (HiveMQ) → Web Dashboard (GitHub Pages)
```

---

## ⚙️ Teknologi yang Digunakan

* ESP32 (Arduino IDE)
* MQTT (HiveMQ Cloud)
* Async Web Server & WebSocket
* HTML, CSS, JavaScript
* GitHub Pages (Web Hosting)

---

## 📁 Struktur Project

```id="str1"
docs/                 → Dokumentasi tambahan
images/               → Gambar project
src/2ModeAP&MQTT/     → Source code ESP32
README.md             → Dokumentasi project
```

---

## ▶️ Cara Menggunakan

### 🔹 Mode AP (Tanpa Internet)

* Connect ke WiFi:

```id="ap1"
ESP32_IoT
```

* Akses:

```id="ap2"
http://192.168.4.1
```

---

### 🔹 Mode STA (WiFi Rumah)

* ESP32 connect ke WiFi
* Akses via IP lokal:

```id="sta1"
http://192.168.x.x
```

---

### 🔹 Mode Internet (Cloud)

* Akses dashboard:

```id="cloud1"
https://hemart-tn.github.io/esp32-iot-dashboard/
```
## 📸 Hasil Project

1. Hasil Pembacaan Sensor Jarak (HC-SR04)
<p align="center"> <img src="https://github.com/user-attachments/assets/aad884a5-e6d5-426c-acc1-13e778bf1224" width="300"> </p>

Keterangan:
Gambar di atas menunjukkan penggunaan dashboard dengan 3 perangkan yang berbeda dan cara koneksi yang berbeda (web hosting, STA, AP). Semuanya menunjukkan kesesuaian dalam menunjukkan data jarak yang diperoleh sensor ultrasonik.

2. Hasil Kontrol LED RGB
<p align="center"> <img src="https://github.com/user-attachments/assets/5fa3b5d9-243b-4c32-abe0-44804146ebd2" width="300"> </p>

Keterangan:
Gambar menunjukkan LED RGB yang dapat dikontrol melalui web dashboard menggunakan slider. Perubahan nilai warna (Red, Green, Blue) akan langsung mempengaruhi warna LED secara realtime. Ketiga perangkat dengan cara koneksi yang berbeda semuanya dapat mengontrol led tersebut secara bergantian.

---

## 📡 MQTT Topic

```id="mqtt1"
iot/esp32/jarak   → data sensor
iot/esp32/rgb     → kontrol LED
```

---

## 🔥 Keunggulan Sistem

* Tidak bergantung pada satu jaringan
* Bisa berjalan offline maupun online
* Fleksibel (lokal & cloud)
* Realtime dan responsif
* Cocok untuk project IoT skala lanjut

---

## 👨‍💻 Author

**Hema Tata Nugraha**
ESP32 IoT Project
