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

1. Koneksi WiFi ESP32 (Access Point)
<p align="center"> <img src="https://github.com/user-attachments/assets/347e2330-a174-46d8-8b07-35d1d33e5657" width="300"> </p>

Keterangan:
Gambar di atas menunjukkan perangkat smartphone yang terhubung langsung ke jaringan WiFi yang dibuat oleh ESP32 (mode Access Point). Pengguna dapat mengakses web dashboard melalui alamat IP 192.168.4.1 tanpa menggunakan koneksi internet.

2. Hasil Pembacaan Sensor Jarak (HC-SR04)
<p align="center"> <img src="https://github.com/user-attachments/assets/9fbf9cef-488c-4c43-ad5e-a23be9a38f71" width="300"> </p>

Keterangan:
Gambar menunjukkan tampilan web dashboard yang menampilkan hasil pembacaan sensor ultrasonik HC-SR04 secara realtime. Nilai jarak yang terbaca akan berubah sesuai dengan objek yang berada di depan sensor.

3. Hasil Kontrol LED RGB
<p align="center"> <img src="https://github.com/user-attachments/assets/0c14e30e-2bce-4e50-83cf-79dd45e34336" width="300"> </p>

Keterangan:
Gambar menunjukkan LED RGB yang dapat dikontrol melalui web dashboard menggunakan slider. Perubahan nilai warna (Red, Green, Blue) akan langsung mempengaruhi warna LED secara realtime.

---
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
