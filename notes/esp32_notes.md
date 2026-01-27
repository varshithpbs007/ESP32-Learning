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
* If we can understand GPIO 0, we can understand esp32 booting
* At boot, esp32 asks GPIO 0, Should I run user code or wait for programming
* The decision logic is,
