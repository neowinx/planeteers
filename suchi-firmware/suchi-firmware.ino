#include "../config.h"
#include "lora_sender.h"
#include "sensor.h"

uint16_t  g_pm1p0_sp_value      = 0;  // Standard Particle calibration pm1.0 reading
uint16_t  g_pm2p5_sp_value      = 0;  // Standard Particle calibration pm2.5 reading
uint16_t  g_pm10p0_sp_value     = 0;  // Standard Particle calibration pm10.0 reading

// ** Not need to send all these other values since they are not used in Linka
//    but we will mantain these comments in case they are needed in the future

// uint16_t  g_pm1p0_ae_value      = 0;  // Atmospheric Environment pm1.0 reading
// uint16_t  g_pm2p5_ae_value      = 0;  // Atmospheric Environment pm2.5 reading
// uint16_t  g_pm10p0_ae_value     = 0;  // Atmospheric Environment pm10.0 reading
// 
// uint32_t  g_pm0p3_ppd_value     = 0;  // Particles Per Deciliter pm0.3 reading
// uint32_t  g_pm0p5_ppd_value     = 0;  // Particles Per Deciliter pm0.5 reading
// uint32_t  g_pm1p0_ppd_value     = 0;  // Particles Per Deciliter pm1.0 reading
// uint32_t  g_pm2p5_ppd_value     = 0;  // Particles Per Deciliter pm2.5 reading
// uint32_t  g_pm5p0_ppd_value     = 0;  // Particles Per Deciliter pm5.0 reading
// uint32_t  g_pm10p0_ppd_value    = 0;  // Particles Per Deciliter pm10.0 reading

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.print("Suchi Air Quality Sensor starting up, v");
  Serial.println(VERSION);
  Serial.print("PMS_RX_PIN:");
  Serial.println(PMS_RX_PIN);
  Serial.print("PMS_TX_PIN:");
  Serial.println(PMS_TX_PIN);
  pmsStart();
  initLoRa();
}

void loop() {
  if (pmsRead()) {
    g_pm1p0_sp_value   = data.PM_SP_UG_1_0;
    g_pm2p5_sp_value   = data.PM_SP_UG_2_5;
    g_pm10p0_sp_value  = data.PM_SP_UG_10_0;

    String _message = "suchi:"
      + String(g_pm1p0_sp_value) + ":"
      + String( g_pm2p5_sp_value ) + ":" 
      + String( g_pm10p0_sp_value );
    
    Serial.println();

    Serial.print("PM 1.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_1_0);

    Serial.print("PM 2.5 (ug/m3): ");
    Serial.println(data.PM_AE_UG_2_5);

    Serial.print("PM 10.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_10_0);

    Serial.println();

    sendLoRa(_message);
  }

  Serial.println("deep sleep esp for 120 seconds");
  esp_sleep_enable_timer_wakeup(120000000);
  esp_deep_sleep_start();
}

