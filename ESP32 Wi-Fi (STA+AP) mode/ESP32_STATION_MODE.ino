// 1. ESP32 supports only 2.4 GHz Wi-Fi with WPA2. Phone hotspots often operate at 2.4 GHz, which is why connection succeeded.
// 2. but some latest dual-band routers need explicit 2.4 GHz configuration. 


#include <WiFi.h>

const char* ssid = "varshith"; // APs (my iphone here in hotspot) SSID i.e., name of the router, declared as a constant string
const char* password = "pubhasava"; // Wi-Fi's password decclared as a constant string

void setup() { //This setup function code runs only once
  Serial.begin(115200);
  delay(1000); // delay of 1s

// 1. Setting WiFi mode and clearing previous WiFi data for a fresh connection
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true);
  delay(100); // delay of 10ms

// 2. Begin new connection to router(AP)
  WiFi.begin(ssid, password);
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
