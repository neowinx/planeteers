#define VERSION 0.1

#include "sensor.h"
#include "lora.h"

void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.print("Suchi Air Quality Sensor starting up, v");
  Serial.println(VERSION);
  pmsStart();
  initLoRa();
}

void loop()
{
  if (pmsRead())
  {
    String _message = String(data.PM_AE_UG_1_0) + ":" + String(data.PM_AE_UG_2_5) + ":" + String(data.PM_AE_UG_10_0);
    
    Serial.print("PM 1.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_1_0);

    Serial.print("PM 2.5 (ug/m3): ");
    Serial.println(data.PM_AE_UG_2_5);

    Serial.print("PM 10.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_10_0);

    Serial.println();

    sendLoRa(_message);
    
  }
  Serial.println("no data ?");
  delay(20000);
}

