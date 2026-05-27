#include <Wire.h>

void receiveEvent(int bytes)
{
  Serial.print("Bytes: ");
  Serial.println(bytes);

  while(Wire.available())
  {
    char c = Wire.read();

    Serial.print(c);
  }

  Serial.println();
}

void setup()
{
  Serial.begin(115200);

  delay(2000);

  Serial.println("ESP32 READY");

  Wire.begin(0x68);

  Wire.onReceive(receiveEvent);
}

void loop()
{

}