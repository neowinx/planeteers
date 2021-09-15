#include "../config.h"
#include "lora_receiver.h"

void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.print("Ma-ti Air Quality Sensor starting up, v");
  Serial.println(VERSION);
  loraInit(receivePayload);
}

void loop()
{
  // here we should receive and send the data
}

void receivePayload(char payload[]) {
  Serial.print("payload received: ");
  Serial.println(payload);
}
