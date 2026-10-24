# bengalaiot-esp32

**Português** · [Español](README.es.md) · [English](README.en.md)

Versão da **Bengala IoT** com ESP32. Dois sensores ultrassônicos medem a distância até obstáculos e um motor de vibração avisa a pessoa: quanto mais perto o obstáculo, mais forte a vibração. As leituras também são enviadas por Bluetooth LE.

**[Simule no Wokwi](https://wokwi.com/projects/360982537270744065)**, sem precisar de hardware.

## Como funciona

- A cada 1 segundo, lê os dois sensores (alcance máximo de 200 cm).
- Usa a menor das duas distâncias para regular a intensidade da vibração (PWM).
- Acima de 200 cm, a vibração desliga.
- Com um aparelho conectado, envia as duas distâncias pelo Bluetooth LE (dispositivo `ESP32_Ultrasonic`).

## Ligações

| Componente | Pino do ESP32 |
| --- | --- |
| Sensor ultrassônico 1 (trigger / echo) | 12 / 13 |
| Sensor ultrassônico 2 (trigger / echo) | 14 / 15 |
| Motor de vibração | 27 |

## Bibliotecas

- [NewPing](https://bitbucket.org/teckel12/arduino-new-ping)
- BLE do ESP32 (já vem no pacote de placas ESP32 da Arduino IDE)

## Arquivos

| Arquivo | Conteúdo |
| --- | --- |
| `sketch.ino` | Código do ESP32 |
| `diagram.json` | Circuito para o Wokwi |
| `libraries.txt` | Bibliotecas usadas no Wokwi |

---

Parte do [AssistThings](https://assistthings.github.io): tecnologia assistiva aberta com IA e IoT.
