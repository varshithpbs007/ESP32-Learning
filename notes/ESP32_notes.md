# ESP32 Notes
# Index:
* Key Points
* What happens just after power is supplied and the ESP32 is powered on
    * Boot Process (Physically)
* Power Pins & GPIOs
* Boot button
* EN (reset) button
* Bootstrapping pins
* Flash pins (GPIO 6 - 11) [NEVER TOUCH THEM]
* Input-only pins ( GPIO 34,35,36,39 )
* Safe Pin Philosophy
* Analog input pins
* PWM (Pulse Width Modulation) pins
*  DAC Pins
*  How ESP32 Talks to Other Devices (Communication Protocols)
    *  UART (Universal Asynchronous Transmitter Reciever)
    *  I2C (Inter Integrated Circuit)
    *  SPI (Serial Peripheral Interface)
* Touch Pins
* Wi-Fi mode
  * Different Wi-Fi modes
  * Wi-Fi communication protocols in ESP32
    * HTTP
    * MQTT
    * WebSocket
    * TCP/UDP



## Key Points:
* ESP Devkit = ESP32 + Other components.
* The ESP32 core module is shielded with a metallic cover to isolate it on the DevKit to reduce EM interference and obtain clean signals. The metallic cover also acts as a natural heat sink.
* ESP32 is a powerful 32-bit microcontroller SoC made by ESPRESSIF.
* ESP32 has built-in WiFi (2.4 GHz 802.11 b/g/n)and Bluetooth (Classic + BLE).
* ESP32 can run up to 240 MHz, i.e., has clock options of 80,160,240 MHz.
* It is dual-core (Tensilica Xtensa LX6 cores).
* ESP32 DevKit has a voltage regulator (1117 33 e447) which converts 5v (USB/Vin) from usb to 3.3v which esp32 can handle.
* As ESP32 natively does not support USB, it has a USB-to-serial converter (CH9102X), which helps us flash code and also access the serial monitor.
* ESP32 DevKit has an EN (Reset) button, which when pushed pulls the EN low and resets the ESP32, and releasing the button brings EN to high again to enable ESP32 to restart execution.
* i.e., EN = 3.3v(HIGH/untouched) means ESP32 runs, if EN = 0v(LOW/Pushed) means ESP32 is held in reset.
* 512 Kb internal SRAM, which is inside the ESP32 chip itself, etched on the same silicon die as CPU cores and registers. Internal SRAM is used for stack, heap, Global/static variables, RTOS tasks, and Runtime data.
* SRAM is very fast, but Volatile (lost when power off) and its size is fixed at fabrication.
* 4 MB external flash memory is a seperate IC block on the DevKit and is connected via SPI/QSPI lines to esp32. It's used for program code(.text), constants, Firmware, File systems (SPIFFS/LittleFS), and OTA updates.
* External flash memory is non-volatile (retains data without power), but slower than SRAM.

  
## What happens just after power is supplied and the ESP32 is powered on:
* Analogically, ESP32 is reborn every time it's powered up.
* After powering up, the ROM bootloader (factory code burned into ROM) is executed to decide the role of esp32 ( It should run user code, i.e., firmware, or to wait for programming).
* Then the bootloader decides if the user code/ firmware, which is in the flash memory (containing setup() and loop()), should run or not.
* To decide the role of ESP32, the bootloader checks a few pins called "strapping pins."
* Strapping pins are GPIO pins whose voltage is read at power-up to decide how the ESP32 should start.
  ### Boot Process (Physically)
  1. ESP32 powers ON.
  2. ROM bootloader (inside chip) runs.
  3. Firmware is read from external flash.(If GPIO 0 is High(3.3V) which is normal)
  4. Code is:
     * Executed directly from flash (XIP), or
     * Copied into internal SRAM
  5. Variables live in SRAM during execution. 

## Power Pins & GPIOs:
* ESP32 is a low-power microcontroller and runs at only 3.3V.
* Although technically ESP32 has 48 pins, only 30 of them are broken out and accessible through the DevKit peripherally as Power pins and GPIOs, because some pins are internally used (flash, boot, power).
* We totally have 4 power-related pins, namely VIN, GND, 3V3, and GND.
* ESP32 DevKit has a VIN pin, and a GND pin on the left bottom side to which we can connect any 5V source externally and through the voltage regulator (1117 33 e447) on board, which regulates it to 3.3V at the right bottom side to use with 3V3 and GND pins.
* In the remaining 26 pins, 25 are GPIO pins and one is EN pin.






## Bootstrapping pins:
* The strapping pins that are sampled at reset are GPIO 0,2,4,5,12,15
* Sampling a strapping pin at boot means that after power ON, the ESP32 waits for a few microseconds, reads the voltage on the strapping pins, and then makes decisions based on their voltages and continues boot.
* After the checking is done GPIOs are back to being normal pins from strapping pins.
* i.e., Strapping pin state matters ONLY at boot time; therefore, they are also called bootstrapping pins.
* GPIO 0,2,4,5,12,15 can be used normally after boot.
* Most critical bootstrapping pins are GPIO 0,2,12,15.

  ### GPIO 0 ( The most important pin ):
  * If we can understand GPIO 0, we can understand ESP32 booting.
  * GPIO 0 is the most important boot-strapping pin in the ESP32.
  * At reset, the ESP32’s ROM bootloader samples GPIO0 to decide the boot mode. Note that the reset can be of two types: a power-on reset and toggling the EN(reset) pin.
  * If GPIO 0 is HIGH(3.3V), the ESP32 boots normally and executes user firmware from SPI flash.
  * If GPIO 0 is LOW(0V), the ESP32 enters UART download mode and waits for new firmware.
  * This design ensures that even if the firmware in flash is corrupted, the chip remains programmable.
  * On development boards, the USB-to-UART interface (generally a USB-to-UART chip) automatically pulls GPIO0 low using the wired DTR(Data Terminal Ready) signal, resets the chip during flashing (EN pin toggle) using wired RTS(Ready to Send) signal, which is why we can upload code from Arduino IDE without manual intervention.
  ### Boot Button:
  * Boot button = GPIO 0 control.
  * The Boot button is physiclly connected to GPIO 0 and pushing that pulls GPIO 0 to LOW and releasing it makes GPIO 0 HIGH again.
  * GPIO 0 is HIGH (3.3V) by default, and has an internal pull-up resistor.
  * By default GPIO 0 HIGH (Boot button unpressed) means Boot from flash (our code).
  * GPIO 0 LOW (Boot button pressed and hold) means enter UART download mode.
  ### EN (Reset) button:
  * Pushing and releasing the EN button resets the ESP32 and makes it run firmware from flash. (If the boot button is unpressed during reset the ESP32 boots normally and executes firnware from flash memory) 
 







  ### GPIO 2:
  ### GPIO 12:
  ### GPIO 15:

### Do not use RX0 and TX0 pins and leave them free, which are related to UART 0, which are used during reset/boot. RX0 and TX0 are connected to a USB-to-serial interface and are required for flashing and debugging, so using them can interfere with booting and programming.
### So leave RX0/TX0 free and use UART1, UART2, SoftwareSerial(with care) to use with our peripherals.

## Flash pins (GPIO 6 - 11) [NEVER TOUCH THEM]:


## Input-only pins ( GPIO 34,35,36,39 ):
* These pins can READ voltage.
* But, they cannot DRIVE voltage.
* So, these input-only pins are great for sensors and useless for LEDs.
* Using them as output doesnot damage anything, but simply doesnot work.
  
## Safe Pin Philosophy:
* The basic thumb-rule is use pins the bootloader doesnot care about and are ignored during boot.
* Safe GPIOs for DOIT ESP32 DEVKIT V1 are GPIO 4,5,18,19,21,22,23

## Analog input pins:
* When we want to read changing signals like temperature, light, we need analog input pins.
* The ESP32 has 2 Analog units:
* 1. ADC1(GPIO 36[ADC1_0],39[ADC1_3],34[ADC1_6],35[ADC1_7],32[ADC1_4],33[ADC1_5]) and
  2. ADC2(GPIO
4[ADC2_0],2[ADC2_2],15[ADC2_3],13[ADC2_4],12[ADC2_5],14[ADC2_6],27[ADC2_7],26[ADC2_9],25[ADC2_8])
* These are 12-bit ADCs.
* These pins can read voltages between 0-3.3 V with 12-bit resolution.
* So, they can read values with 12-bit resolution between 0 - 4095. ( 0 - 2^12 -1 ).
* NOTE: If the project uses Wi-Fi, It's best to use ADC1 pins, because ADC2 pins are actually share hardware with the Wi-Fi system which can interfere with readings when Wi-Fi is active.

## PWM (Pulse Width Modulation) pins:
* PWM pins are important and enable to control things in more defined way.
* EX: Rather than just turing a LED on/off we can make it dim and bright smoothly.
* ESP32 DevKit has 16-PWM channels which can be used with any GPIO pin.

## DAC Pins:
* DAC pins lets ESP32 send out smooth analog voltages (opposite of ADC).
* There are 2 built-in DAC channels available at GPIO 25[DAC1],26[DAC2] which can ouput voltages between 0-3.3 V.




# How ESP32 Talks to other devices (Communication Protocols):
## Serial Communication:
### UART (Universal Asynchronous Transmitter Reciever):
* UART is a full-duplex asynchronous 2-wire serial communication protocol, which is used every time we upload code to the ESP32 or check the serial monitor to print debug messages.
* ESP32 has 3 hardware UARTS:
  1. UART0 for Serial monitor/Uploading and connected to USB by default (TX: GPIO 1, RX: GPIO 3)
  2. UART1 for Custom use (TX: GPIO 10, RX: GPIO 9 (not available on all boards))
  3. UART2 for Custom use (TX: GPIO 17, RX: GPIO 16 (can be changed to other pins easily))

### I2C (Inter Integrated Circuit):
* Great when we want to connect multiple sensors or modules.
* It only needs two wires, SCL (GPIO 22) and SDA (GPIO 21) are default.
* It's a half-duplex serial communication protocol.

### SPI (Serial Peripheral Interface):
* High-speed cousin of I2C.
* Its Full-duplex with 4 wires CLK, MOSI, MISO, SS/CS(Slave Select/Chip select Lines) like SS1(SPI slave 1),SS2(SPI slave 2),etc.
* SPI_MOSI(GPIO 23), SPI_MISO(GPIO 19), SPI_CLK(GPIO 18), SPI_CS(GPIO 5).
* Its perfect when speed really matters. Like when dealing with SD card or memory chips.

## Touch Pins:



# Wi-Fi:
* ESP32 supports standard Wi-Fi 802.11 b/g/n.
* It operates in the 2.4 GHz band.
* It can operate in 3 modes:
    1. STA (Station mode): 
    2. AP (Access Point mode):
    3. STA + AP mode

1. STA mode:
  * In station mode, ESP32 connects to an existing wi-fi network, acting as a client to the server and connects to the internet through a Router (Access Point), just like other devices like mobile phones, laptops, etc.
  * Can pull or push data from the cloud using protocols like HTTP, MQTT.

2. AP mode:
  * In access point mode, ESP32 creates its own wi-fi hotspot, enabling devices like mobile phones and laptops to connect to it.
  * No internet or router needed.
  * It can serve web pages locally.

## Wi-Fi communication protocols in ESP32:
1. HTTP - Hypertext Transfer Protocol:
   * It's the same protocol our browser uses to load web pages.
   * ESP32 can send GET and POST requests to web servers and APIs.
   * Easy to use and supported everywhere.
   * Best for: Cloud APIs, basic control systems, and data logging
  
2. MQTT - Message Queueing Telemetry Transport:
   * Lightweight protocol and designed for real-time IoT messaging.
   * Works on a publish-subscribe model.
   * But, requires a broker like Mosquitto to handle messages.
   * Best for: Live sensor feeds, automation, smart homes.
  
  3. WebSocket:
   * Full-duplex communication, means both sides can send data at the same time.
   * More efficient than HTTP for continuous data streams.
   * Best for: Live dashboards, real-time control panels.

  4. TCP/UDP (Low-Level Protocols)
   * TCP: Reliable, connection-oriented.
   * UDP: Faster, connectionless, but less reliable.
   * TCP/UDP are used when we need custom, fast data exchange between devices.

## Assigning ESP32 to  a specific Wi-Fi mode:
## STA (Station mode): Find code in the dedicated folder
## AP (Access Point mode): Find code in the dedicated folder











