#include "../config.h"
#include "lora_receiver.h"
#include "wifi.h"
#include "utils.h"

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.print("Ma-ti Air Quality Sensor starting up, v");
  Serial.println(VERSION);
  initLora(receivePayload);
  // initWifi();
}

void loop() {
  // here we should receive and send the data
}

void receivePayload(char payload[]) {
  Serial.print("payload received: ");
  Serial.println(payload);
  // String g_pm1p0_sp_value = getValue(payload, ':', 0);
  // String g_pm2p5_sp_value = getValue(payload, ':', 1);
  // String g_pm10p0_sp_value = getValue(payload, ':', 2);
  // reportToHttp(g_pm1p0_sp_value, g_pm2p5_sp_value, g_pm10p0_sp_value);
}