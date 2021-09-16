#include "../config.h"
#include "lora_receiver.h"
#include "wifi.h"

/*--------------------------- Global Variables ---------------------------*/
uint16_t  g_pm1p0_sp_value      = 0;  // Standard Particle calibration pm1.0 reading
uint16_t  g_pm2p5_sp_value      = 0;  // Standard Particle calibration pm2.5 reading
uint16_t  g_pm10p0_sp_value     = 0;  // Standard Particle calibration pm10.0 reading

uint16_t  g_pm1p0_ae_value      = 0;  // Atmospheric Environment pm1.0 reading
uint16_t  g_pm2p5_ae_value      = 0;  // Atmospheric Environment pm2.5 reading
uint16_t  g_pm10p0_ae_value     = 0;  // Atmospheric Environment pm10.0 reading

uint32_t  g_pm0p3_ppd_value     = 0;  // Particles Per Deciliter pm0.3 reading
uint32_t  g_pm0p5_ppd_value     = 0;  // Particles Per Deciliter pm0.5 reading
uint32_t  g_pm1p0_ppd_value     = 0;  // Particles Per Deciliter pm1.0 reading
uint32_t  g_pm2p5_ppd_value     = 0;  // Particles Per Deciliter pm2.5 reading
uint32_t  g_pm5p0_ppd_value     = 0;  // Particles Per Deciliter pm5.0 reading
uint32_t  g_pm10p0_ppd_value    = 0;  // Particles Per Deciliter pm10.0 reading

void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.print("Ma-ti Air Quality Sensor starting up, v");
  Serial.println(VERSION);
  initLora(receivePayload);
  initWifi();
}

void loop()
{
  // here we should receive and send the data
}

void receivePayload(char payload[]) {
  Serial.print("payload received: ");
  Serial.println(payload);
  updatePmsReadings(payload);
  reportToHttp(g_pm1p0_sp_value, g_pm2p5_sp_value, g_pm10p0_sp_value);
}

/*
  Update particulate matter sensor values
*/
void updatePmsReadings(char payload[])
{
  char* values = strtok(payload, ":");
  // Put the most recent values into globals for reference elsewhere
  g_pm1p0_sp_value   = values[0];
  g_pm2p5_sp_value   = values[1]; 
  g_pm10p0_sp_value  = values[2]; 

  g_pm1p0_ae_value   = values[3]; 
  g_pm2p5_ae_value   = values[4]; 
  g_pm10p0_ae_value  = values[5]; 

  uint32_t  new_pm0p3_ppd_value  = values[6]; 
  uint32_t  new_pm0p5_ppd_value  = values[7]; 
  uint32_t  new_pm1p0_ppd_value  = values[8]; 
  uint32_t  new_pm2p5_ppd_value  = values[9]; 
  uint32_t  new_pm5p0_ppd_value  = values[10]; 
  uint32_t  new_pm10p0_ppd_value = values[11];

  // This condition below should NOT be required, but currently I get all
  // 0 values for the PPD results every second time. This check only updates
  // the global values if there is a non-zero result for any of the values:
  if (
    new_pm0p3_ppd_value +
    new_pm0p5_ppd_value +
    new_pm1p0_ppd_value +
    new_pm2p5_ppd_value +
    new_pm5p0_ppd_value +
    new_pm10p0_ppd_value
      != 0)
  {
    g_pm0p3_ppd_value  = new_pm0p3_ppd_value;
    g_pm0p5_ppd_value  = new_pm0p5_ppd_value;
    g_pm1p0_ppd_value  = new_pm1p0_ppd_value;
    g_pm2p5_ppd_value  = new_pm2p5_ppd_value;
    g_pm5p0_ppd_value  = new_pm5p0_ppd_value;
    g_pm10p0_ppd_value = new_pm10p0_ppd_value;
  }
}
