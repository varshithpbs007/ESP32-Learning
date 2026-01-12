/*
* File: gpio_control_uart_blink.ino
* Platform: ESP32
* Description:
*  - Controls LED using UART input
*  - '1' -> LED ON
*  - '0' -> LED OFF
* Concepts:
*  - GPIO output
*  - UART serial communication
*  - Polling using Serial.available() <-- inbuilt object of C++
*/


//This code makes me understand GPIO's INPUT(virtual in this code for understanding GPIO) and OUTPUT

#define LED_PIN 2
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(2000); //2000ms = 2s

  pinMode(LED_PIN,OUTPUT);
  Serial.println("Type '1' for LED ON / Type '0' for LED_OFF");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){   //Polling and Serial.available returns number of bytes
    char c = Serial.read();

    if(c == '1'){
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED ON");
    }
    else if(c == '0'){
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED OFF");
    }
  }
}
