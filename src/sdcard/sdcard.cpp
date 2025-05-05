#include "sdcard.h"

SDCard::SDCard(int chipSelectPin) : _chipSelectPin(chipSelectPin) {
}

bool SDCard::begin() {
    if (!SD.begin(_chipSelectPin)) {
        Serial.println("SD Card initialization failed!");
        return false;
    }
    Serial.println("SD Card initialized.");
    return true;
}

bool SDCard::saveFile(const String& filename, const uint8_t* data, size_t size) {
    File file = SD.open(filename, FILE_WRITE);
    if (!file) {
        Serial.println("Failed to open file for writing");
        return false;
    }
    
    size_t written = file.write(data, size);
    file.close();
    
    if (written != size) {
        Serial.println("Write failed");
        return false;
    }
    
    Serial.println("File saved successfully");
    return true;
}

bool SDCard::deleteFile(const String& filename) {
    if (SD.exists(filename)) {
        if (SD.remove(filename)) {
            Serial.println("File deleted: " + filename);
            return true;
        } else {
            Serial.println("Delete failed: " + filename);
            return false;
        }
    } else {
        Serial.println("File does not exist: " + filename);
        return false;
    }
}

bool SDCard::isImageFile(const String& filename) {
    String lowerFilename = filename;
    lowerFilename.toLowerCase();
    return (lowerFilename.endsWith(".jpg") || 
            lowerFilename.endsWith(".jpeg") || 
            lowerFilename.endsWith(".png"));
}

int SDCard::getImageCount() {
    File root = SD.open("/");
    if (!root) {
        Serial.println("Failed to open directory");
        return 0;
    }
    
    int count = 0;
    File file = root.openNextFile();
    
    while (file) {
        if (!file.isDirectory() && isImageFile(file.name())) {
            count++;
        }
        file = root.openNextFile();
    }
    
    root.close();
    return count;
}

void SDCard::getImageList(String* imageList, int maxCount) {
    File root = SD.open("/");
    if (!root) {
        Serial.println("Failed to open directory");
        return;
    }
    
    int count = 0;
    File file = root.openNextFile();
    
    while (file && count < maxCount) {
        String filename = "/" + String(file.name());
        if (!file.isDirectory() && isImageFile(filename)) {
            imageList[count++] = filename;
        }
        file = root.openNextFile();
    }
    
    root.close();
}