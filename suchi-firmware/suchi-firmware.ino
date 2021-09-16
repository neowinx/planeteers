#include "../config.h"
#include "lora_sender.h"
#include "sensor.h"

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
  Serial.print("Suchi Air Quality Sensor starting up, v");
  Serial.println(VERSION);
  pmsStart();
  initLoRa();
}

void loop()
{
  if (pmsRead())
  {
    g_pm1p0_sp_value   = data.PM_SP_UG_1_0;
    g_pm2p5_sp_value   = data.PM_SP_UG_2_5;
    g_pm10p0_sp_value  = data.PM_SP_UG_10_0;

    g_pm1p0_ae_value   = data.PM_AE_UG_1_0;
    g_pm2p5_ae_value   = data.PM_AE_UG_2_5;
    g_pm10p0_ae_value  = data.PM_AE_UG_10_0;

    // This condition below should NOT be required, but currently I get all
    // 0 values for the PPD results every second time. This check only updates
    // the global values if there is a non-zero result for any of the values:
    if (data.PM_TOTALPARTICLES_0_3 + data.PM_TOTALPARTICLES_0_5
        + data.PM_TOTALPARTICLES_1_0 + data.PM_TOTALPARTICLES_2_5
        + data.PM_TOTALPARTICLES_5_0 + data.PM_TOTALPARTICLES_10_0
        != 0)
    {
      g_pm0p3_ppd_value  = data.PM_TOTALPARTICLES_0_3;
      g_pm0p5_ppd_value  = data.PM_TOTALPARTICLES_0_5;
      g_pm1p0_ppd_value  = data.PM_TOTALPARTICLES_1_0;
      g_pm2p5_ppd_value  = data.PM_TOTALPARTICLES_2_5;
      g_pm5p0_ppd_value  = data.PM_TOTALPARTICLES_5_0;
      g_pm10p0_ppd_value = data.PM_TOTALPARTICLES_10_0;
    }

    String _message = g_pm1p0_sp_value + ":"
      + g_pm2p5_sp_value + ":" 
      + g_pm10p0_sp_value + ":" 
      + g_pm1p0_ae_value + ":" 
      + g_pm2p5_ae_value + ":" 
      + g_pm10p0_ae_value + ":" 
      + g_pm0p3_ppd_value + ":" 
      + g_pm0p5_ppd_value + ":" 
      + g_pm1p0_ppd_value + ":" 
      + g_pm2p5_ppd_value + ":" 
      + g_pm5p0_ppd_value + ":" 
      + g_pm10p0_ppd_value;
    
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

