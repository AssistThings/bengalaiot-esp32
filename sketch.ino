#include <Arduino.h>
#include <NewPing.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// Defina os pinos dos sensores ultrassônicos
#define TRIGGER_PIN1 12
#define ECHO_PIN1 13
#define TRIGGER_PIN2 14
#define ECHO_PIN2 15

// Pino do motor vibracall
#define VIBRACALL_PIN 27

// Defina a distância máxima de leitura (em centímetros)
#define MAX_DISTANCE 200

// Inicialize os sensores ultrassônicos
NewPing sensor1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE);
NewPing sensor2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE);

// Intervalo entre as leituras (em milissegundos)
unsigned long interval = 1000;
unsigned long previousMillis = 0;

// Configuração do Bluetooth
BLEServer *pServer = nullptr;
BLECharacteristic *pCharacteristic = nullptr;
bool deviceConnected = false;
const char *SERVICE_UUID = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";
const char *CHARACTERISTIC_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26a8";

class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    deviceConnected = true;
  }

  void onDisconnect(BLEServer *pServer)
  {
    deviceConnected = false;
  }
};

void setup()
{
  Serial.begin(115200);

  // Configuração do pino do motor vibracall como saída
  pinMode(VIBRACALL_PIN, OUTPUT);

  // Configuração do Bluetooth
  BLEDevice::init("ESP32_Ultrasonic");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_NOTIFY);

  pCharacteristic->addDescriptor(new BLE2902());
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}

void loop()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    // Leia as distâncias dos sensores ultrassônicos
    unsigned int distance1 = sensor1.ping_cm();
    unsigned int distance2 = sensor2.ping_cm();

    // Calcule a menor distância entre os dois sensores
    unsigned int minDistance = min(distance1, distance2);

    // Imprima as distâncias lidas
    Serial.print("Distância Sensor 1: ");
    Serial.print(distance1);
    Serial.print(" cm");
    Serial.print("\t");
    Serial.print("Distância Sensor 2: ");
    Serial.print(distance2);
    Serial.println(" cm");

    // Enviar dados via Bluetooth
    // Enviar dados via Bluetooth
    if (deviceConnected)
    {
      String data = "Distância Sensor 1: " + String(distance1) + " cm, Distância Sensor 2: " + String(distance2) + " cm";
      pCharacteristic->setValue(data.c_str());
      pCharacteristic->notify();
    }

    // Ajuste a intensidade do motor vibracall com base na distância mínima
    if (minDistance <= MAX_DISTANCE)
    {
      int intensity = map(minDistance, 0, MAX_DISTANCE, 255, 0);
      ledcSetup(0, 5000, 8);
      ledcAttachPin(VIBRACALL_PIN, 0);
      ledcWrite(0, intensity);
    }
    else
    {
      // Desligue o motor vibracall se a distância for maior que MAX_DISTANCE
      ledcWrite(0, 0);
    }
  }
}
