#include <SoftwareSerial.h>
#include "PMS.h"

#if defined (ARDUINO_ARCH_ESP32) || defined(ESP32)
#	define ESP32_ARCH 1
# define PMS_RX_PIN T0 // Rx from PMS (== PMS Tx)
# define PMS_TX_PIN T2 // Tx to PMS (== PMS Rx)
#elif defined(ARDUINO_ARCH_ESP8266)
# define PMS_RX_PIN D4 // Rx from PMS (== PMS Tx)
# define PMS_TX_PIN D2 // Tx to PMS (== PMS Rx)
#else
#	error "Architecture unknown and not supported"
#endif

SoftwareSerial pmsSerial(PMS_RX_PIN, PMS_TX_PIN); // Rx pin = GPIO2 (D4 on Wemos D1 Mini)
PMS pms(pmsSerial, false);           // Use the software serial port for the PMS
PMS::DATA data;

void setup()
{
  Serial.begin(9600);   // GPIO1, GPIO3 (TX/RX pin on ESP-12E Development Board)
  Serial1.begin(9600);  // GPIO2 (D4 pin on ESP-12E Development Board)
}

void loop()
{
  if (pms.read(data))
  {
    Serial1.print("PM 1.0 (ug/m3): ");
    Serial1.println(data.PM_AE_UG_1_0);

    Serial1.print("PM 2.5 (ug/m3): ");
    Serial1.println(data.PM_AE_UG_2_5);

    Serial1.print("PM 10.0 (ug/m3): ");
    Serial1.println(data.PM_AE_UG_10_0);

    Serial1.println();
  }
}
