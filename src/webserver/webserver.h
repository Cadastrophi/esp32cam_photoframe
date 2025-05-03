#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <HTTP_Method.h>            // brings in HTTP_GET, HTTP_POST, HTTP_ANY, etc.
#include <AsyncTCP.h>               // required by AsyncWebServer on ESP32
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include "sdcard/sdcard.h"

class WebServer {
public:
    WebServer() : server(80) {}
    void begin();

private:
    AsyncWebServer server;

    void handleRoot(AsyncWebServerRequest *request);
    void handleFileList(AsyncWebServerRequest *request);
    void handleFileDelete(AsyncWebServerRequest *request);
    void handleNotFound(AsyncWebServerRequest *request);
    void handleFileUpload(AsyncWebServerRequest *request, const String& filename, size_t index, uint8_t *data, size_t len, bool final);

    String getContentType(const String& filename);
    bool handleFileRead(AsyncWebServerRequest *request, const String& path);
    String generateGalleryHTML();
    String generateDeleteConfirmHTML(const String& filename);
};

#endif // WEBSERVER_H