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
