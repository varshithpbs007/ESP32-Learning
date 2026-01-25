/*
* File name: Input-Descision-Output(full_loop).ino
* Platform: ESP32

* Concept:
*   Right now : 
*   - Input - keyboard(serial)
*   - Decision - if logic
*   - Output - On board LED ( GPIO 2 )
*   
*   Later :
*   - Keyboard becomes button/sensor/Network packet
*   - Decision logic will be there
*   - LED will become relay/motor/display
*/



#define LED_PIN 2   // Onboard LED

void setup() {
  Serial.begin(115200);
  delay(2000);

  pinMode(LED_PIN, OUTPUT);

  Serial.println("=== BUTTON → LED SIMULATION ===");
  Serial.println("P = Button Pressed  (LED ON)");
  Serial.println("R = Button Released (LED OFF)");
}

void loop() {
  if (Serial.available() > 0) {

    char c = Serial.read();   // INPUT

    if (c == 'P' || c == 'p') {     // DECISION
      digitalWrite(LED_PIN, HIGH);  // OUTPUT
      Serial.println("Button PRESSED → LED ON");
    }
    else if (c == 'R' || c == 'r') {
      digitalWrite(LED_PIN, LOW);
      Serial.println("Button RELEASED → LED OFF");
    }
  }
}

