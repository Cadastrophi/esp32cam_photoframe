#ifndef CONFIG_H
#define CONFIG_H

// Wi-Fi credentials for AP mode
static const char* ap_ssid     = "PhotoFrame";
static const char* ap_password = "photo1234";


// // ILI9341 TFT display settings
// #define TFT_MISO 13  // Updated for your connections
// #define TFT_MOSI 12  // Updated for your connections
// #define TFT_SCLK 14  // Updated for your connections
// #define TFT_CS   15
// #define TFT_DC   2
// #define TFT_RST  -1  // Connect to ESP32 EN pin or set to -1 if connected to 3.3V

// SD card settings (using the one on ESP32-CAM)
#define SD_CS      5

// Button pin definitions
#define BUTTON_PHOTO  4   // Updated to IO4
#define BUTTON_BACK   16  // Updated to IO16

// Button timing
#define LONG_PRESS_TIME 3000 // 3 seconds for long press

// Image settings
#define IMAGE_CHANGE_INTERVAL 10000 // 10 seconds between images

#endif // CONFIG_H