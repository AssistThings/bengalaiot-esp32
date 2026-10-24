# bengalaiot-esp32

[Português](README.md) · **Español** · [English](README.en.md)

Versión de la **Bengala IoT** (bastón inteligente) con ESP32. Dos sensores ultrasónicos miden la distancia a los obstáculos y un motor de vibración avisa a la persona: cuanto más cerca está el obstáculo, más fuerte vibra. Las lecturas también se envían por Bluetooth LE.

**[Simúlalo en Wokwi](https://wokwi.com/projects/360982537270744065)**, sin necesidad de hardware.

## Cómo funciona

- Cada 1 segundo lee los dos sensores (alcance máximo de 200 cm).
- Usa la menor de las dos distancias para regular la intensidad de la vibración (PWM).
- Por encima de 200 cm, la vibración se apaga.
- Con un dispositivo conectado, envía las dos distancias por Bluetooth LE (dispositivo `ESP32_Ultrasonic`).

## Conexiones

| Componente | Pin del ESP32 |
| --- | --- |
| Sensor ultrasónico 1 (trigger / echo) | 12 / 13 |
| Sensor ultrasónico 2 (trigger / echo) | 14 / 15 |
| Motor de vibración | 27 |

## Bibliotecas

- [NewPing](https://bitbucket.org/teckel12/arduino-new-ping)
- BLE del ESP32 (incluida en el paquete de placas ESP32 de Arduino IDE)

## Archivos

| Archivo | Contenido |
| --- | --- |
| `sketch.ino` | Código del ESP32 |
| `diagram.json` | Circuito para Wokwi |
| `libraries.txt` | Bibliotecas usadas en Wokwi |

---

Parte de [AssistThings](https://assistthings.github.io/es/): tecnología asistiva abierta con IA e IoT.
