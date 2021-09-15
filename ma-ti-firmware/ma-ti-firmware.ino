#include "../config.h"
#include "lora_receiver.h"

void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.print("Ma-ti Air Quality Sensor starting up, v");
  Serial.println(VERSION);
  initLoRa();
}

void loop()
{
  // here we should receive and send the data
}

