# ESP32 Concepts
## What happens just after power is supplied and esp32 is powered on:
* Analogically esp32 is reborn everytime its powered up
* After powering up the bootloader ( factory code burned into ROM ) is executed to decide the role of esp32 ( to run usercode i.e., firmware or to wait for programming )
* Then the bootloader decides if the user code/ firmware, which is in the flash memory ( containing setup() and loop() ) should run or not
* To decide the role of esp32, the bootloader checks few pins called "strapping pins"
* Strapping pins are GPIO pins whose voltage is read at power-up to decide how the esp32 should start

## Sampling a strapping pin at boot:
* Sampling a strapping pin at boot means that after power ON, esp32 waits for few microseconds and then reads voltage on GPIO 0,2,12,15 and then makes decisions based on their voltages and continues boot
* After the checking is done GPIOs are back to being normal pins from strapping pins
* i.e., Strapping pin state matters ONLY at the boot time

### GPIO 0 ( The most impoertant pin ):
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
### Flash pins (GPIO 6 - 11):
### Input-only pins:
## Safe Pin Philosophy:
