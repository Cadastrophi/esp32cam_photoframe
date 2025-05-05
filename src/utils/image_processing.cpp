#include "image_processing.h"
#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <JPEGDecoder.h>

TFT_eSPI tft = TFT_eSPI(); // Create TFT object

void initDisplay() {
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
}

void drawJpeg(int x, int y) {
    // Get the width and height details
    uint16_t *pImg;
    uint16_t mcu_w = JpegDec.MCUWidth;
    uint16_t mcu_h = JpegDec.MCUHeight;
    uint32_t max_x = JpegDec.width;
    uint32_t max_y = JpegDec.height;
    
    // Fetch data from the file
    while (JpegDec.read()) {
        // Get pointer to the decoded MCU block data
        pImg = JpegDec.pImage;
        
        // Calculate coordinates of top left corner of current MCU
        int mcu_x = JpegDec.MCUx * mcu_w + x;
        int mcu_y = JpegDec.MCUy * mcu_h + y;
        
        // Draw the MCU as a block of pixels
        tft.pushImage(mcu_x, mcu_y, mcu_w, mcu_h, pImg);
    }
}

void displayImage(const char* filename) {
    File file = SD.open(filename);
    if (!file) {
        Serial.println("Failed to open file for reading");
        return;
    }

    JpegDec.decodeFsFile(filename);
    drawJpeg(0, 0);
    file.close();
}


void clearDisplay() {
    tft.fillScreen(TFT_BLACK);
}