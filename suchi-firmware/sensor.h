#include <SoftwareSerial.h>
#include "PMS.h"

# if defined (ARDUINO_ARCH_ESP32) || defined(ESP32)
#   define ESP32_ARCH 1
#   define PMS_RX_PIN T0 // Rx from PMS (== PMS Tx)
#   define PMS_TX_PIN T2 // Tx to PMS (== PMS Rx)
# elif defined(ARDUINO_ARCH_ESP8266)
#   define PMS_RX_PIN D4 // Rx from PMS (== PMS Tx)
#   define PMS_TX_PIN D2 // Tx to PMS (== PMS Rx)
# else
# 	error "Architecture unknown and not supported"
# endif

SoftwareSerial pmsSerial(PMS_RX_PIN, PMS_TX_PIN); // Rx pin = GPIO2 (D4 on Wemos D1 Mini)
PMS pms(pmsSerial, false);           // Use the software serial port for the PMS
PMS::DATA data;

void pmsStart() {
  pmsSerial.begin(9600);   // Connection for PMSx003
}

bool  pmsRead() {
  return pms.read(data);
}
