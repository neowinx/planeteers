#include <SPI.h>
#include <LoRa.h>
#include "../lora_config.h"

// Prevent the unsupported MKR WAN to be cmopiled
# ifdef ARDUINO_SAMD_MKRWAN1300
#   error "This sketch is not compatible with the Arduino MKR WAN 1300 board!"
# endif

int counter = 0;

// Initiate LoRa 
void initLora() {
  LoRa.setPins(CS_PIN, RESET_PIN, IRQ_PIN);

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  // Uncomment the next line to disable the default AGC and set LNA gain, values between 1 - 6 are supported
  // LoRa.setGain(6);
}

String receiveLoRa() {
  String payload = "";
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      payload += (char)LoRa.read();
    }

    Serial.print(payload);

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
  return payload;
}
