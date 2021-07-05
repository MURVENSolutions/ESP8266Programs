# ESP8266Programs

**Learning about ESP8266 Programming**

For most of the new learners and hobbyist, getting an hands on the embedded systems programming is really time consuming, error prone and laborious affair.

However, the simple solution is to use the off the shelf available ready micro controller with required support and user base. we may use PIC or 8051 micro controllers, but most of the peripherals and communication interface should be designed and implemented (time consuming). In recent years ESP8266 micro chip has been widely used for Embedded, Wi-Fi, TCP/IP, Drone control, IOT and Automation projects.

The ESP8266 is a low-cost Wi-Fi microchip (cost around 5US$) with full TCP/IP stack and microcontroller capability produced by Espressif Systems. This chip caught up the interest of developers and widely used for small projects from 2014 with the ESP-01 module made by Ai-Thinker(3rd party).

ESP8266 small size and easy use allows programs running in microcontroller to connect to a Wi-Fi network or create a Wi-Fi Hotspot and use  TCP/IP connections to create web server/client interactions.

![image](https://user-images.githubusercontent.com/6793806/124422609-2c60e780-dd81-11eb-9a5a-cb9497db145a.png)

**Main Features of ESP8266 (ESP-02)**
-> L106 32-bit RISC microprocessor core running at 80 MHz (can be clocked double)
-> 64 KB of instruction RAM, 96 KB of data RAM
-> External QSPI flash: up to 16 MiB is supported (512 KiB to 4 MiB typically included)
-> IEEE 802.11 b/g/n Wi-Fi
-> Integrated TR switch, LNA, power amplifier and matching network
-> WEP or WPA/WPA2 authentication or Open
-> 16 GPIO pins
-> SPI
-> I²C (software implementation)
-> I²S interfaces with DMA (sharing pins with GPIO)
-> UART on dedicated pins, plus a transmit-only UART can be enabled on GPIO2
-> 10-bit ADC (successive approximation ADC)

Now many vendors came up with their own development kits using ESP8266 module with USB to serial interface, GPIO pinouts and own SDK. One such variant is the NodeMCU development kit / Firmware which uses Lua scripting language (similar to C/C++). Moreover, Arduino IDE can be used for programming NodeMCU with few tweaks.

![image](https://user-images.githubusercontent.com/6793806/124422719-6a5e0b80-dd81-11eb-99f7-bdd1624af004.png)

![image](https://user-images.githubusercontent.com/6793806/124422730-6e8a2900-dd81-11eb-89ca-0ffe66021c67.png)

**NodeMCU kit pin out details**
1. FLASH button: Need to be pressed before programming.

2. Reset button:

3. LED

Lets get started on using the NodeMCU with small programs...

![image](https://user-images.githubusercontent.com/6793806/124422771-83ff5300-dd81-11eb-8934-ca9af9d43420.png)





