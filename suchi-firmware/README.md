# suchi-firmare

Firmware for a sensor that sends Particulate Matter information to a receiving node using LoRa for [AireLibre](https://airelib.re/)

This should be accompained with a [Ma-ti](https://github.com/neowinx/planeteers/tree/main/ma-ti-firmware) node to send the PMS data to the corresponding [Linka](https://github.com/garyservin/linka-firmware) instance

You can find more information about this project on the [ parent directory ](https://github.com/neowinx/planeteers)

## Installation

You can use [ PlatformIO ](https://platformio.org/platformio-ide) or [ Arduino IDE ](https://www.arduino.cc/en/software) to upload the firmware

### PlatformIO

Install [ PlatformIO ](https://platformio.org/platformio-ide) and...

#### ... in Visual Studio Code

- Open the project with vscode having the platformio plugin installed
- Click on the right arrow icon on the platformio toolbar

#### ... or in your terminal

```bash
platformio run -t upload
````

### Arduino IDE

Install [ Arduino IDE ](https://www.arduino.cc/en/software) and...

- Open **File -> Preferences** and copy the following urls on the __"Additional Boards Manager URLs"__ input text

```
https://arduino.esp8266.com/stable/package_esp8266com_index.json,https://dl.espressif.com/dl/package_esp32_index.json
```

and click on **Ok**

- Install the esp32 boards family on **Tools -> Boards Manager**

- Select the corresponding esp32 board on **Tools -> Board:** for example the **"DOIT BOARD "** 

- Install these libraries by clicking on the **Tools -> Manage Libraries...**

  * LoRa

- Select the correct port on the **Tools -> Port:** menu

- Upload the sketch using the arrow button or by selecting the **Sketch -> Upload** menu

# FAQ

## Enjoy!
