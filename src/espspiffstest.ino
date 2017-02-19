#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Hash.h>
#include <FS.h>
#include "secrets.h"

AsyncWebServer webServer(80);

void setup() {
  Serial.begin(115200);
  delay(200);

  // try connecting to wifi
  Serial.print("\nwifi connecting ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.print("\nconnected to: ");
  Serial.println(WiFi.localIP());
  
  SPIFFS.begin();
  webServer.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  webServer.begin();
}

void loop() {
}
