#include <SPI.h>
#include <LoRa.h>
#include "../lora_config.h"

// Prevent the unsupported MKR WAN to be cmopiled
# ifdef ARDUINO_SAMD_MKRWAN1300
#   error "This sketch is not compatible with the Arduino MKR WAN 1300 board!"
# endif

int counter = 0;

// Initiate LoRa 
void initLoRa() {
  LoRa.setPins(CS_PIN, RESET_PIN, IRQ_PIN);

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  
  // Uncomment the next line to disable the default AGC and set LNA gain, values between 1 - 6 are supported
  // LoRa.setGain(6);
}

void sendLoRa(String message) {
  // wait until the radio is ready to send a packet
  while (LoRa.beginPacket() == 0) {
    Serial.print("waiting for radio ... ");
    delay(100);
  }

  Serial.print("Sending packet non-blocking: ");
  Serial.println(counter);

  // send in async / non-blocking mode
  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket(true); // true = async / non-blocking mode

  counter++;
}

