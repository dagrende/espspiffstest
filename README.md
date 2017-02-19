# espspiffstest
Test of ESPAsyncWebServer serving a simple web app from SPIFFS

I have problems serving files larger than about 3K with server.serveStatic. This is my test program.

I use a WeMos d1 mini, and PlatformIO to develop.

To run it with PlatformIO:
```
git clone https://github.com/dagrende/espspiffstest.git
cd espspiffstest
pio run -t uploadfs
pio run -t upload
```
