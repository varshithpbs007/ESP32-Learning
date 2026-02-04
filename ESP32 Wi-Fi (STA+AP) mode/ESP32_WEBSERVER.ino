#include <WiFi.h>
#include <WebServer.h> // gives us lighweight http server which runs on esp32 which can accept requests from a browser

// Access Point credentials
const char* ssid = "ESP32_Hotspot"; // network name
const char* password = "12345678"; // password

// Creating web server on port(80)

WebServer server(80); // default port used for http

// Defining LED pin (GPIO 2 for Onboard LED)

const int ledPin = 2; // pin 2 on-board LED is used 
bool ledState = LOW; // varible to keep track of LED state

// HTML (Hypertext Markup Language) content to be served
const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 LED Control</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      text-align: center;
      bbackground-color: #f0f0f0;
      margin-top: 50px;
    }
    h1 {
      color: #333;
    }
    .button {
      padding: 16px 36px;
      margin: 20px;
      font-size: 20px;
      border-radius: 10px;
      cursor: pointer;
      transition: background 0.3s;
    }
    .on {
      background-color: #4CAF50;
      color: white;
    }
    .on:hover {
      background-color: #45a049;
    }
    .off {
      background-color: #f44336;
      color: white;
    }
    .off:hover {
      background-color: #da190b;
    }
  </style>
</head>
<body>
  <h1>ESP32 LED Control</h1>
  <p><strong>Status:</strong><span id="ledStatus">%STATE%</span></p>
  <button class="button on" onclick="location.href='/led/on'">Turn ON</button>
  <button class="button off" onclick="location.href='/led/off'">Turn OFF</button>
</body>
</html>
)rawliteral";


void handleRoot() {
  String html = htmlPage;
  html.replace("%STATE%", ledState ? "ON" : "OFF");
  server.send(200, "text/html", html);
}


void handleLedOn() {
  digitalWrite(ledPin, HIGH);
  ledState = true;
  handleRoot();
}



void handleLedOff() {
  digitalWrite(ledPin, LOW);
  ledState = false;
  handleRoot();
}



void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  // Start Access Point
  WiFi.softAP(ssid, password);
  Serial.println("Access Point started");
  Serial.print("IP address:");
  Serial.println(WiFi.softAPIP()); // connect to this IP address from a browser

 // Define routes
 // These line maps the url from browser to the function in the code
 server.on("/",handleRoot); // gets triggered when we connect to AP and request with 192.168.4.1
 server.on("/led/on",handleLedOn); // this line registers the mapping between path and function linked to that path and gets triggered when requested with 192.168.4.1/led/on
 server.on("/led/off",handleLedOff); // gets triggered when we connect to AP and request with 192.168.4.1/led/off

 server.begin();
}


void loop() {
  // 1. This loop function continuosly listens for web requests.
  // 2. Is there a new browser request?
  // 3. Which path is being requested?
  // 4. Okay, which function is linked to that path?
  // 5. Let me call that function and send the response.
  server.handleClient();
}
