#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include <Stepper.h>

ESP8266WebServer server(80);

WiFiManager wifiManager;

const int stepsPerRevolution = 256;  

int motorSpeed = 15;
bool motorDirection = true;

Stepper myStepper(stepsPerRevolution, D5, D7, D8, D6);

const String mainHTML = "<html>\
  <head>\
    <title>Turntable controller</title>\
    <style>\
    </style>\
  </head>\
  <body>\
     <label for=\"direction\">speed</label>\
     <input type=\"range\" id=\"speed\" value=\"15\" min=\"0\" max=\"130\">\
     <br/>\
     <label for=\"direction\">clockwise</label>\
     <input type=\"checkbox\" id=\"direction\" checked>\
     <script type=\"text/javascript\">\
        (() => { \
          const speedInput = document.getElementById('speed');\
          const directionInput = document.getElementById('direction');\
          const updateSettings = () => { fetch(`/settings?speed=${speed.value}&clockwise=${directionInput.checked ? 'true' : 'false'}`) };\
          speedInput.addEventListener('change', () => {updateSettings()}); \
          directionInput.addEventListener('change', () => {updateSettings()}); \
        })() \
     </script>\
  </body>\
</html>";



void handleRoot() {
  server.send(200, "text/html", mainHTML);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void handleSettings() {
  motorSpeed = server.arg("speed").toInt();
  motorDirection = server.arg("clockwise").equalsIgnoreCase("true");
  
  server.send(200, "text/plain", "ok");
}

void setup() {
  wifiManager.autoConnect("turntable");
  wifiManager.setConfigPortalTimeout(180);
  WiFi.mode(WIFI_STA);
  WiFi.begin();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.on("/", handleRoot);
  server.on("/settings", handleSettings);


  server.onNotFound(handleNotFound);

  server.begin();
}

void loop() {
  server.handleClient();
  
  if (motorSpeed == 0) {
    digitalWrite(D5, LOW);
    digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);
    digitalWrite(D8, LOW);
  } else {
    myStepper.setSpeed(motorSpeed);
    myStepper.step(motorDirection ? 10 : -10);
  } 
}
