# Wi-Fi Enabled Medicine Locator 💊📍

An IoT-powered smart inventory and retrieval shelf system built with the **ESP32 microcontroller**. It eliminates search time and dispensing errors in pharmacies, clinics, and home care environments by combining visual LED compartment guidance with real-time stock tracking via physical input mechanisms.

---

## 📌 Features

- **🌐 Embedded Web Dashboard:** ESP32 hosts a responsive local web server for querying medicines, viewing inventory levels, and managing slot configurations.
- **💡 Visual Compartment Locator:** Selecting a medicine on the dashboard triggers localized LEDs at the exact shelf slot to pinpoint its physical location instantly.
- **🔄 Auto-Decrement Inventory:** Physical push-button switches at each compartment detect retrieval and automatically update stock counts in real time—eliminating manual logging.
- **⚠️ Low-Stock Alerts:** Visual and dashboard warnings when a compartment's stock dips below a defined threshold.
- **⚡ Lightweight & Standalone:** Operates over local Wi-Fi without requiring external cloud dependencies or paid APIs.

---

## 🛠️ Hardware & Components

| Component | Description |
| :--- | :--- |
| **ESP32 Development Board** | Main microcontroller hosting the web server & managing GPIOs |
| **LEDs / Addressable LED Strip** | Visual indicators for shelf compartment guidance |
| **Push Buttons / Microswitches** | Input triggers for physical stock decrement |
| **Resistors (220Ω / 10kΩ)** | Current limiting and pull-up/pull-down networks |
| **Breadboard / Custom PCB & Wiring** | Prototyping framework and interconnects |
| **5V / 3.3V Power Supply** | Dedicated regulated power source |

---

## 💻 Tech Stack & Tools

- **Firmware / Embedded C/C++:** Arduino IDE / ESP-IDF / PlatformIO
- **Web Frontend:** HTML5, CSS3, JavaScript (embedded in ESP32 SPIFFS/LittleFS or PROGMEM)
- **Networking:** AsyncWebServer / WebSockets, mDNS, Wi-Fi AP/Station mode
- **Simulation & Design:** Proteus / Fritzing

---

## 🚀 Getting Started

### Prerequisites
1. [Arduino IDE](https://www.arduino.cc/en/software) with the ESP32 board package installed.
2. Required Libraries:
   - `WiFi.h`
   - `WebServer.h`
   - `LiquidCrystal_I2C.H`
   - `Wire.h`

### Installation & Flashing
1. **Clone the repository:**
   ```bash
   git clone [https://github.com/your-username/wifi-enabled-medicine-locator.git](https://github.com/your-username/wifi-enabled-medicine-locator.git)
   cd wifi-enabled-medicine-locator
