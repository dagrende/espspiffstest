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

  webServer.on("/asd", HTTP_GET, [](AsyncWebServerRequest *request) {
    File* fp = new File(SPIFFS.open("/box.js", "r"));
    size_t fileSize = fp->size();
    Serial.print("fileSize: ");Serial.println(fileSize);

    request->send("application/javascript", fileSize, [fp, fileSize](uint8_t *buffer, size_t maxLen, size_t index) -> size_t {
      if (*fp) {
        size_t bytesToRead = std::min((size_t)1000, maxLen);
        size_t bytesRead = fp->read(buffer, bytesToRead);
        Serial.print(" index: "); Serial.print(index);
        Serial.print(" maxLen: "); Serial.print(maxLen);
        Serial.print(" bytesToRead: "); Serial.print(bytesToRead);
        Serial.print(" bytesRead: "); Serial.print(bytesRead);
        Serial.println();
        if (index + bytesRead >= fileSize) {
          Serial.println("all is read");
          fp->close();
          // delete fp;
        }
        return bytesRead;
      } else {
        return 0;
      }
    });
  });

  webServer.on("/qwe", HTTP_GET, [](AsyncWebServerRequest *request) {
    // send 5000 bytes as plain text
    request->send("text/plain", 5000, [](uint8_t *buffer, size_t maxLen, size_t index) -> size_t {
      //Write up to "maxLen" bytes into "buffer" and return the amount written.
      //index equals the amount of bytes that have been already sent
      //You will not be asked for more bytes once the content length has been reached.
      //Keep in mind that you can not delay or yield waiting for more data!
      //Send what you currently have and you will be asked for more again
      if (10 > maxLen) {
        return 0;
      }
      sprintf((char *)buffer, "%9d\n", index);
      return 10;
    });
  });

  webServer.begin();
}

void loop() {
}
