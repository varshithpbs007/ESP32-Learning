// - In access point mode, ESP32 creates its own wi-fi hotspot, enabling devices like mobile phones and laptops to connect to it.
// - No internet or router needed.
// - It can serve web pages locally.
// - It works like a mini router.
// - We obtain the IP addres of ESP32 in AP mode and use it to request for web pages.

#include <WiFi.h>

const char* AP_SSID = "ESP32_Hotspot";
const char* AP_PASSWORD = "12345678"; // must be 8 charecters long
void setup()
{
  Serial.begin(115200);
  
  WiFi.softAP(AP_SSID, AP_PASSWORD); // Starting a WiFi hotspot, ESP32 in Access Point mode, acting as a router
  Serial.println("Acceess Point Started");
  Serial.print("IP address:");
  Serial.println(WiFi.softAPIP()); // This will return the IP address ESP32 assigns itself during hotspot in Access Point mode, which can be used to request the server(ESP32) for webpages
  // Generally the IP address is AP mode is 192.168.4.1
}

void loop()
{
  // Nothing here for now
}
