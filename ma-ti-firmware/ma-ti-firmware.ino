#include "../config.h"
#include "lora_receiver.h"
#include "wifi.h"
#include "utils.h"

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.print("Ma-ti Air Quality Sensor starting up, v");
  Serial.println(VERSION);
  Serial.println("Initializing Wifi...");
  initWifi();
  Serial.println("Initializing LoRa...");
  initLora();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  String payload = receiveLoRa();
  if(payload != "") {
    Serial.println("payload received");
    String suchistr = getValue(payload, ':', 0);
    if (suchistr == "suchi") {
      String g_pm1p0_sp_value = getValue(payload, ':', 1);
      String g_pm2p5_sp_value = getValue(payload, ':', 2);
      String g_pm10p0_sp_value = getValue(payload, ':', 3);
      Serial.print("payload received: ");
      Serial.print("pm1p0: " + String(g_pm1p0_sp_value) + ", ");
      Serial.print("pm2p5: " + String(g_pm2p5_sp_value) + ", ");
      Serial.println("pm10p0: " + String(g_pm10p0_sp_value));
      reportToHttp(g_pm1p0_sp_value, g_pm2p5_sp_value, g_pm10p0_sp_value);
    }
  }
}
