#include "../config.h"
#include "lora_receiver.h"
#include "wifi.h"

/*--------------------------- Global Variables ---------------------------*/
uint16_t  g_pm1p0_sp_value      = 0;  // Standard Particle calibration pm1.0 reading
uint16_t  g_pm2p5_sp_value      = 0;  // Standard Particle calibration pm2.5 reading
uint16_t  g_pm10p0_sp_value     = 0;  // Standard Particle calibration pm10.0 reading

// ** Not need to store all these other values since they are not used in Linka
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
void updatePmsReadings(char payload[]) {
  // Split the value in two strs
  char* separator = strchr(payload, ':');
  while (separator != 0)
  {
    ++separator;
    int position = atoi(separator);

    // Do something with servoId and position
  }
  // Find the next value in payload string
  value = strchr(0, ":");

  // Put the most recent values into globals for reference elsewhere
  g_pm1p0_sp_value   = atoi(values[0]);
  g_pm2p5_sp_value   = atoi(values[1]); 
  g_pm10p0_sp_value  = atoi(values[2]); 
}
