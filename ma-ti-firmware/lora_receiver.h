#include <SPI.h>
#include <LoRa.h>
#include "../lora_config.h"

// Prevent the unsupported MKR WAN to be cmopiled
# ifdef ARDUINO_SAMD_MKRWAN1300
#   error "This sketch is not compatible with the Arduino MKR WAN 1300 board!"
# endif

int counter = 0;
void (*_onReceive)(char[]);

void loraReceive(int packetSize);

// Initiate LoRa 
void loraInit(void(*callback)(char[])) {
  LoRa.setPins(CS_PIN, RESET_PIN, IRQ_PIN);

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  
  // Uncomment the next line to disable the default AGC and set LNA gain, values between 1 - 6 are supported
  // LoRa.setGain(6);

  _onReceive = callback;
  
  // register the receive callback
  LoRa.onReceive(loraReceive);

  // put the radio into receive mode
  LoRa.receive();
}

void loraReceive(int packetSize) {
  // received a packet
  Serial.print("Received packet '");

  char payload[packetSize];

  // read packet
  for (int i = 0; i < packetSize; i++) {
    payload[i] = (char)LoRa.read();
    Serial.print(payload[i]);
  }

  // print RSSI of packet
  Serial.print("' with RSSI ");
  Serial.println(LoRa.packetRssi());

  if (_onReceive) {
    _onReceive(payload);
  }
}
