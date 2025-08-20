# ESP32 I2C Bus Scanner

![ESP32-I2C](https://img.shields.io/badge/ESP32-I2C_Scanner-blue)
![ESP-IDF](https://img.shields.io/badge/ESP--IDF-v4.4%2B-orange)

## 📌 Overview
A lightweight I2C bus scanner utility for ESP32 microcontrollers that detects connected devices and displays their addresses in hexadecimal format. Perfect for debugging I2C connections during hardware development.

## ✨ Features
- 🔍 Scans all 127 possible I2C addresses
- 🚀 Fast detection with configurable timeout
- 📊 Clear terminal output with device count
- ⚡ Supports standard 100kHz and 400kHz modes
- 🔧 Easy-to-configure GPIO pins

## 🛠 Hardware Setup
| ESP32 Pin | I2C Connection |
|-----------|----------------|
| GPIO 32   | SDA (Data)     |
| GPIO 33   | SCL (Clock)    |
| 3.3V      | VCC            |
| GND       | GND            |


I2C Master-Slave Example
------------------------

       +---------+        SDA        +---------+
       |         |<----------------->|         |
       |  MASTER |                   |  SLAVE  |
       | (ESP32) |        SCL        | (0x3C)  |
       |         |<----------------->|         |
       +---------+                   +---------+

           SDA — Serial Data Line (bidirectional)
           SCL — Serial Clock Line (managed by the master)


> 💡 **Note:** Most I2C devices require pull-up resistors (4.7kΩ recommended) on SDA/SCL lines if not built-in.

## 🛠 Building and⚡Flashing
.
```bash
idf.py build
idf.py -p com[your_com_port] flash monitor
```
## 🔍 Serial Monitor Output
```bash
I (287) i2c-master: Starting I2C scan...
I (297) i2c-master: Found device at 0x3C
I (297) i2c-master: Scan complete
```
