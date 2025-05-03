#ifndef SDCARD_H
#define SDCARD_H

#include "SD.h"
#include <SPI.h>

class SDCard {
public:
    SDCard(int chipSelectPin);
    bool begin();
    bool saveFile(const String& filename, const uint8_t* data, size_t size);
    bool deleteFile(const String& filename);
    int getImageCount();
    void getImageList(String* imageList, int maxCount);
    
private:
    int _chipSelectPin;
    bool isImageFile(const String& filename);
};

#endif // SDCARD_H