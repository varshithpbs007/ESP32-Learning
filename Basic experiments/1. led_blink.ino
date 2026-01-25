/*
* File: led_blink.ino
* Platform: ESP32
* Description:
*  - Blinks LED connected to GPIO 2
*  - 1 second ON, 1 second OFF
* Concepts:
*  - GPIO input 
*  - Blocking delay
*  - Arduino execution model
*/


#define LED_PIN 2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_PIN,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  delay(1000);
}

