#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include <TFT_eSPI.h>

class ImageProcessing {
public:
    ImageProcessing(TFT_eSPI* tft);
    void displayImage(const String& filename);
    void drawJpeg(int x, int y); // Add this line
    void loadImage(const String& filename);
    void slideshow(const String* images, size_t count, unsigned long interval);
    
private:
    TFT_eSPI* tft;
    void drawImage(uint16_t* imgData, int width, int height);
};

#endif // IMAGE_PROCESSING_H