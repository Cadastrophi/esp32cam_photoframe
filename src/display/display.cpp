#include "display.h"
#include <JPEGDecoder.h>
#include "config.h"

Display::Display() {
}

void Display::begin() {
    tft.init();
    tft.setRotation(1); // Landscape orientation
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(1);
}

void Display::clearScreen() {
    tft.fillScreen(TFT_BLACK);
}

void Display::drawText(const String& text, int x, int y) {
    tft.drawString(text, x, y);
}

void Display::displayImage(const String& filename) {
    clearScreen();

    File jpgFile = SD.open(filename);
    if (!jpgFile) {
        drawText("Failed to open " + filename, 10, 10);
        return;
    }

    if (!JpegDec.decodeSdFile(jpgFile)) {
        drawText("Failed to decode JPEG", 10, 20);
        jpgFile.close();
        return;
    }

    // Render each MCU block
    while (JpegDec.read()) {
        tft.pushImage(
            JpegDec.MCUx * JpegDec.MCUWidth,
            JpegDec.MCUy * JpegDec.MCUHeight,
            JpegDec.MCUWidth,
            JpegDec.MCUHeight,
            JpegDec.pImage
        );
    }

    jpgFile.close();
}

void Display::drawCameraFrame(const uint8_t* jpegData, size_t jpegSize) {
    clearScreen();

    // Decode from the in-RAM buffer:
    if (!JpegDec.decodeArray(jpegData, jpegSize)) {
        drawText("JPEG decode failed", 10, 10);
        return;
    }

    // Push each MCU (block) to the TFT:
    while (JpegDec.read()) {
        tft.pushImage(
            JpegDec.MCUx * JpegDec.MCUWidth,
            JpegDec.MCUy * JpegDec.MCUHeight,
            JpegDec.MCUWidth,
            JpegDec.MCUHeight,
            JpegDec.pImage
        );
    }
}
