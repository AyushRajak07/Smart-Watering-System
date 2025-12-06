# Soil-Moisture-Sensor
<img width="1920" height="1030" alt="Wokwi - Online ESP32, STM32, Arduino Simulator - Google Chrome 06-12-2025 15_15_05" src="https://github.com/user-attachments/assets/e6179abf-8c7c-4b8b-81ad-29d429b8b1c0" />
# Smart Plant Watering System with OLED & ThingSpeak

An **automatic plant watering system** using **ESP32** that:
- Reads soil moisture in real-time
- Automatically turns **ON** water pump when soil is dry (< 30%)
- Turns **OFF** pump when soil is moist enough (> 75%)
- Displays live status on **0.96" OLED**
- Uploads data to **ThingSpeak** for remote monitoring

Fully tested and working 100% on **Wokwi Online Simulator** (free) and real ESP32 hardware!

<img width="1920" height="1030" alt="Wokwi - Online ESP32, STM32, Arduino Simulator - Google Chrome 06-12-2025 15_12_16" src="https://github.com/user-attachments/assets/462f0de1-3c06-497c-86a4-ed98fa8d30d2" />

<img width="1920" height="1030" alt="Wokwi - Online ESP32, STM32, Arduino Simulator - Google Chrome 06-12-2025 15_13_04" src="https://github.com/user-attachments/assets/fdec71c2-f6b1-4a63-8f56-05e94ba2ce0a" />

<img width="1920" height="1030" alt="Wokwi - Online ESP32, STM32, Arduino Simulator - Google Chrome 06-12-2025 15_14_02" src="https://github.com/user-attachments/assets/8d0faf02-751f-4fe8-80a2-32f3cd7bec9f" />

<img width="1920" height="1030" alt="Wokwi - Online ESP32, STM32, Arduino Simulator - Google Chrome 06-12-2025 15_14_21" src="https://github.com/user-attachments/assets/572d4129-94f4-454b-b22a-fdc1e91acf1d" />



## Features
- Automatic watering with hysteresis (prevents pump flickering)
- Live moisture percentage on SSD1306 OLED
- Real-time graphs on ThingSpeak (view from phone anywhere)
- WiFi connectivity (uses Wokwi-GUEST or your home WiFi)
- Clean code with comments

## Hardware Required
| Component                  | Link (Amazon) |
|---------------------------|-----------------------------------------------------|
| ESP32 Dev Board           | [Buy Here](https://www.amazon.com/dp/B08D5ZD528) |
| Soil Moisture Sensor      | [Buy Here](https://www.amazon.com/dp/B07R4S5F6Z) |
| 0.96" OLED SSD1306        | [Buy Here](https://www.amazon.com/dp/B076DYCWC8) |
| 5V Water Pump / Relay     | [Buy Here](https://www.amazon.com/dp/B07B6R9KX8) |
| Jumper Wires & Breadboard | [Buy Here](https://www.amazon.com/dp/B01EV70C78) |

Total cost: **Less than $20**



## ThingSpeak Live Data
https://thingspeak.com/channels/2564339  
(Real public channel — you can see live updates when running!)

## Run Online Instantly (No Hardware Needed)
[https://wokwi.com/projects/383947283947203585](https://wokwi.com/projects/449410093791692801)  
Just click "Start" — it works immediately!

## How to Use on Real Hardware
1. Change WiFi credentials in code:
   ```cpp
   const char* WIFI_NAME = "YourWiFiName";
   const char* WIFI_PASSWORD = "YourPassword";
