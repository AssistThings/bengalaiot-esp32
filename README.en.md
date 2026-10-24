# bengalaiot-esp32

[Português](README.md) · [Español](README.es.md) · **English**

ESP32 version of **Bengala IoT** (smart cane). Two ultrasonic sensors measure the distance to obstacles and a vibration motor warns the person: the closer the obstacle, the stronger the vibration. Readings are also sent over Bluetooth LE.

**[Simulate it on Wokwi](https://wokwi.com/projects/360982537270744065)**, no hardware needed.

## How it works

- Every second, it reads both sensors (maximum range 200 cm).
- It uses the shorter of the two distances to set the vibration strength (PWM).
- Beyond 200 cm, the vibration turns off.
- When a device is connected, it sends both distances over Bluetooth LE (device `ESP32_Ultrasonic`).

## Wiring

| Component | ESP32 pin |
| --- | --- |
| Ultrasonic sensor 1 (trigger / echo) | 12 / 13 |
| Ultrasonic sensor 2 (trigger / echo) | 14 / 15 |
| Vibration motor | 27 |

## Libraries

- [NewPing](https://bitbucket.org/teckel12/arduino-new-ping)
- ESP32 BLE (bundled with the ESP32 boards package for the Arduino IDE)

## Files

| File | Contents |
| --- | --- |
| `sketch.ino` | ESP32 code |
| `diagram.json` | Wokwi circuit |
| `libraries.txt` | Libraries used in Wokwi |

---

Part of [AssistThings](https://assistthings.github.io/en/): open assistive technology with AI and IoT.
