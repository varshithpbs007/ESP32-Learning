# ESP32 Notes
## Key Points:
* ESP Devkit = ESP32 + Other components.
* The ESP32 core module is shielded with a metallic cover to isolate it on the DevKit to reduce EM interference and obtain clean signals. The metallic cover also acts as a natural heat sink.
* ESP32 is a powerful 32-bit microcontroller SoC made by ESPRESSIF.
* ESP32 has built-in WiFi (2.4 GHz 802.11 b/g/n)and Bluetooth (Classic + BLE).
* ESP32 can run up to 240 MHz, i.e., has clock options of 80,160,240 MHz.
* It is dual-core (Tensilica Xtensa LX6 cores).
* ESP32 DevKit has a voltage regulator (1117 33 e447) which converts 5v (USB/Vin) from usb to 3.3v which esp32 can handle.
* It has a USB-to-serial converter (CH9102X), which helps us flash code and also access the serial monitor.
* ESP32 DevKit has an EN (Reset) button, which when pushed pulls the EN low and resets the ESP32, and releasing the button brings EN to high again to enable ESP32 to restart execution.
* i.e., EN = 3.3v(HIGH/untouched) means ESP32 runs, if EN = 0v(LOW/Pushed) means ESP32 is held in reset.
* 512 Kb internal SRAM, which is inside the ESP32 chip itself, etched on the same silicon die as CPU cores and registers. Internal SRAM is used for stack, heap, Global/static variables, RTOS tasks, and Runtime data.
* SRAM is very fast, but Volatile (lost when power off) and its size is fixed at fabrication.
* 4 MB external flash memory is a seperate IC block on the DevKit and is connected via SPI/QSPI lines to esp32. Its used for program code(.text), constants, Firmware, File systems (SPIFFS/LittleFS), OTA updates.
* External flash memory is non-volatile (retains data without power), but slower than SRAM.

  
## Power Pins:
* ESP32 is a low-power microcontroller and runs at only 3.3V.
* Although technically ESP32 has 48 pins, only 30 of them are broken out and accessible through the DevKit peripherally as Power pins and GPIOs, because some pins are internally used (flash, boot, power).
* We totally have 4 power-related pins, namely VIN, GND, 3V3, and GND.
* ESP32 DevKit has a VIN pin, and a GND pin on the left bottom side to which we can connect any 5V source externally and through the voltage regulator (1117 33 e447) on board, which regulates it to 3.3V at the right bottom side to use with 3V3 and GND pins.
* Remaining 26 pins are GPIOs



## What happens just after power is supplied and esp32 is powered on:
* Analogically, ESP32 is reborn every time it's powered up.
* After powering up, the ROM bootloader (factory code burned into ROM) is executed to decide the role of esp32 ( It should run user code i.e., firmware, or to wait for programming).
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

## Sampling a strapping pin at boot:
* Sampling a strapping pin at boot means that after power ON, esp32 waits for a few microseconds and then reads voltage on GPIO 0,2,12,15, and then makes decisions based on their voltages and continues boot.
* After the checking is done GPIOs are back to being normal pins from strapping pins.
* i.e., Strapping pin state matters ONLY at boot time, Therefore they are also called bootstrapping pins.

### GPIO 0 ( The most important pin ):
* If we can understand GPIO 0, we can understand esp32 booting.
* GPIO0 is the most important boot-strapping pin in the ESP32.
* At reset, the ESP32’s ROM bootloader samples GPIO0 to decide the boot mode. Note that the reset can be of two types, one is power-on reset and second is EN(reset) pin toggling.
* If GPIO0 is HIGH(3.3V), the ESP32 boots normally and executes user firmware from SPI flash.
* If GPIO0 is LOW(0V), the ESP32 enters UART download mode and waits for new firmware.
* This design ensures that even if the firmware in flash is corrupted, the chip remains programmable.
* On development boards, the USB-to-UART interface (generally a USB-to-UART chip) automatically pulls GPIO0 low using the wired DTR(Data Terminal Ready) signal, resets the chip during flashing (EN pin toggle) using wired RTS(Ready to Send) signal, which is why we can upload code from Arduino IDE without manual intervention.

### GPIO 2:
### GPIO 12:
### GPIO 15:
## Flash pins (GPIO 6 - 11) [NEVER TOUCH THEM]:

## Input-only pins ( GPIO 34,35,36,39 ):
* These pins can READ voltage.
* But, they cannot DRIVE voltage.
* So, these input-only pins are great for sensors and useless for LEDs.
* Using them as output doesnot damage anything, but simply doesnot work.
  
## Safe Pin Philosophy:
* The basic thumb-rule is use pins the bootloader doesnot care about and are ignored during boot.
* Safe GPIOs for DOIT ESP32 DEVKIT V1 are GPIO 4,5,18,19,21,22,23
