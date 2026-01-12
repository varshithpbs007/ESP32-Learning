/*
* File name: button_simulation.ino
* Platform: ESP32
* Concept:
*   - Simulating a button as input for GPIO
*   - By default the input GPIO pins are undefined(floating) unless a pull-up or pull-down is enabled
*   - With pull-up enabled, the default input state is HIGH(3.3 V) when the button is not pressed
*   - When a button is pressed, then it is read as LOW(0 V)
*   - Here we are simulating the button press virtually through the keyboard to understand the concept
*   - P => Pressed => LOW => 0 V
*   - R => Released => HIGH => 3.3 V
*/

void setup()
{
  Serial.begin(115200);
  delay(2000); //this delay is not for the esp32 but for the PC side + USB serial link
  /*
  This delay means waiting 2 seconds before sending data to the ESP32, so that in the meantime, the PC has time to connect and listen.
  As the ESP32 executes very fast, till then the serial monitor is not established through USB and the PC can miss some early messages
  */
  Serial.println("Simulating BUTTON with Serial");
  Serial.println("Type P or R for  P = Button Pressed , R = Button Released");
}

void loop()
{
  if(Serial.available() > 0){
    char c = Serial.read();

    if(c == 'P'){
      Serial.println("Button Pressed => GPIO reads LOW");
    }
    else if (c == 'R'){
      Serial.println("Button Released => GPIO reads HIGH");
    }
  }
}
