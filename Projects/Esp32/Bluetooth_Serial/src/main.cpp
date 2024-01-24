#include <Arduino.h>
#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() 
{
  Serial.begin(115200);


  SerialBT.begin("ESP32_BTController");
  Serial.println(SerialBT.getBtAddressString());
}

void loop()
{
  if (SerialBT.available()) { 
    char command = SerialBT.read();
    Serial.println(command);
  }

}
