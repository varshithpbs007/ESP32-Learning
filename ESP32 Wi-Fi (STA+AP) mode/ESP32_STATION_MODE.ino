#include <WiFi.h>

const char* ssid = "Death Dealer"; // Wi-Fi's SSID, i.e., name of the router, declared as a constant string
const char* password = "112233445"; // Wi-Fi's password decclared as a constant string

void setup() { //This setup function code runs only once
  Serial.begin(115200);

// 1. Set WiFi mode to Station
  WiFi.mode(STA);

// 2. Begin connection to AP
  Wifi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");

// 3. Wait for IP assignment by the AP through DHCP
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("."); //....

  }

  Serial.println("\n WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Returns the IP address the router has given to our ESP32 in STATION mode

}

void loop() {
  // nothing here for now

}

