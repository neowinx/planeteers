# suchi-firmare

Firmware for a sensor that sends Particulate Matter information to a receiving node using LoRa for [AireLibre](https://airelib.re/)

This should be accompained with a [Ma-ti](https://github.com/neowinx/ma-ti-firmware) node to send the PMS data to the corresponding [Linka](https://github.com/garyservin/linka-firmware) instance

I know that probably there's no need for two repositories for both roles (the sender and the receiver) since we could've just manage those differences using precompiled macros.
The reason for not doing that, is that we want a minimal codebase in order to have a small memory footprint for the nodes, and having to manage precompiled macros and the resulting
code from them will probably result in someone (mainly myself) making a regretable mistake.
Also, it looks cleaner to have those two things separated for people not very into coding but that wants to contribute to the project in a foreseeable future, so in the meantime,
we will mantain these two repositories until I see otherwise even if that means that some lines of code will be duplicated in both projects

### Why not LoRaWAN?

The first prototype for this project was indeed a LoRaWAN node in order to use the [ TTN infraestructure ](https://www.thethingsnetwork.org/). But since gateways are rather
scarse in Paraguay (0 gateways actually in my city) I began to construct one of those single channel gateways (or single channel relays.. or whatever they are called now...)
for testing purposes, only to find out that those are condemned by the TTN community and that the
[ V2 of the TTN will be shutdown this 31 of december 2021 ](https://www.thethingsnetwork.org/forum/t/the-things-network-v2-is-permanently-shutting-down-scheduled/50710), 
and, at the current date, not accepting new nodes, only leaving me with the V3 option that only accepts official (proper) gateways from one of the selected manufacturers 
or [ building a proper one ](https://www.thethingsnetwork.org/docs/gateways/start/build/) myself.
All that just gives me the same headache you're probably having now, so I will only use LoRa for the moment since the application of the technology is rather simple for this case.
Maybe in the future I will reevaluate to use LoRaWAN.
Thank you for reading until this point, If I haven't lost you, let's proceed to the more interesting part of the project

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
