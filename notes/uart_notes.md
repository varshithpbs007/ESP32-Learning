# UART Serial Communication protocol

* UART = Universal Asynchronous Transmitter Receiver.
* Asynchronous because it does not have a clock to sync data between Tx and Rx.
* It's used and preferred for point-to-point communication of devices and but has low speeds compared to I2C and SPI.
* UART is a Full-Duplex mode of communication protocol, meaning that there are separate lines for Tx and Rx, and data can be transmitted and received simultaneously.
* UART uses only two lines for communication (Tx, Rx).
* Data frame format and transmission speeds ( Baud rate ) are configurable in the UART

## Configuration of UART module and data frame format before transmission
  * Both the transmit and receive devices must be configured with the same baud rate in the BRR(Baud rate register)
  * Baud rate: Baud rate is the rate at which information is transmitted in a communication channel. In the context of UART, baud rate represents the number of signal units(bits) sent per second.
  * Key Rule: For successful communication, both the Tx and Rx must be set to the same baud rate, and the receiver can know how to slice the incoming signal into bits. If they don't match, the timing will be off, and the data will appear as 'garbage' text or symbols.
  * Common baud rates are 9600 bps ( Classic low speed and very stable over long wires ), 115200 ( The standard for esp32 and modern microcontrollers, 921600+ bps ( used for high-speed data transfers like uploading firmware )
  * Since UART is asynchronous, it does not have a clock wire to tell the receiver when a bit starts and ends, so it uses the baud rate to determine the "width" of each bit in time
    1. Start bit: The default high line drops to low signalling the start of a frame
    2. Data bits: Usually 8 bits of data are sent
    3. Parity bit (optional): We can include one optional parity bit to detect any errors
    4. Stop bit: The line returns to a high state signaling the  end of a data frame.
* Bit duration = 1 / Baud Rate
* Ex: for 115200 baud rate, Duration of one bite = 1/115200 ~ 8.68 microseconds

## Advantages of UART
  * Simple 2-wire serial full-duplex communication protocol
  * Low power consumption due to only 2 wires ( Tx and Rx )

## Disadvantages of UART
  * Low speed compared to I2C and SPI
  * No synchronization of data
  
