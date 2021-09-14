#include <SPI.h>
#include <LoRa.h>

# if defined(ARDUINO_T_Beam)
const int CS_PIN = 18;          // LoRa radio chip select
const int RESET_PIN = 23;        // LoRa radio reset
const int IRQ_PIN = 26;          // change for your board; must be a hardware interrupt pin
# elif defined(ARDUINO_ARCH_ESP32) || defined(ESP32) || defined(ARDUINO_ESP32_DEV)
// wiring is according to https://circuitdigest.com/microcontroller-projects/interfacing-sx1278-lora-module-with-esp32
const int CS_PIN = 5;
const int RESET_PIN = 14;
const int IRQ_PIN = 2;
# else
#	  error "Architecture unknown and not supported"
# endif

# ifdef ARDUINO_SAMD_MKRWAN1300
#   error "This sketch is not compatible with the Arduino MKR WAN 1300 board!"
# endif

int counter = 0;

// Initiate LoRa and sets the callback
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
