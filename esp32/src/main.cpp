#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// Define BLE service and characteristic UUIDs
#define SERVICE_UUID        "e2f5aee7-94ba-4132-98f1-c2bb3cb5cf80"
#define CHARACTERISTIC_UUID "e2f5aee7-94ba-4132-98f1-c2bb3cb5cf81"

// Callback class for BLE events
class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string value = pCharacteristic->getValue();
    if (value.length() > 0) {
      Serial.println("Received data via BLE:");
      for (int i = 0; i < value.length(); i++) {
        Serial.print(value[i]);
      }
      Serial.println();
    }
  }
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  Serial.println("Starting BLE...");

  // Initialize BLE
  BLEDevice::init("Spark-Trigger");
  BLEServer *pServer = BLEDevice::createServer();

  // Create BLE service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create BLE characteristic
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_WRITE
  );

  // Set callback for BLE writes
  pCharacteristic->setCallbacks(new MyCallbacks());

  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->start();
  Serial.println("BLE is ready and advertising!");
}

void loop() {
  // Add your main logic here
}