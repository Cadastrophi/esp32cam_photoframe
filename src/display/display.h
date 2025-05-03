#ifndef DISPLAY_H
#define DISPLAY_H

#include <SPI.h>
#include <TFT_eSPI.h>
#include "tft_config.h"

class Display {
public:
    Display();
    void begin();
    void clearScreen();
    void displayImage(const String& filename);
    void drawText(const String& text, int x, int y);
    void drawCameraFrame(const uint8_t* jpegData, size_t jpegSize);
    
private:
    TFT_eSPI tft;
    void drawJpeg(const uint8_t* jpegData, size_t jpegSize, int x, int y);
};

#endif // DISPLAY_H