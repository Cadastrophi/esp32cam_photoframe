#include <Arduino.h>
#include <WiFi.h>
#include <SPI.h>
#include "config.h"
#include "camera/camera.h"
#include "display/display.h"
#include "sdcard/sdcard.h"
#include "webserver/webserver.h"
#include "interface/buttons.h"

// Global objects
Display display;
SDCard sdCard(SD_CS);
WebServer webServer;
Camera camera;
Buttons buttons;

// Global variables
enum AppMode {
  SLIDESHOW,
  CAMERA_PREVIEW,
  CAMERA_CAPTURE
};

AppMode currentMode = SLIDESHOW;
unsigned long lastImageChangeTime = 0;
int currentImageIndex = 0;
String* imageList = nullptr;
int imageCount = 0;

void updateImageList() {
  // Free previous list if exists
  if (imageList != nullptr) {
    delete[] imageList;
  }
  
  // Get image count first
  imageCount = sdCard.getImageCount();
  
  if (imageCount > 0) {
    imageList = new String[imageCount];
    sdCard.getImageList(imageList, imageCount);
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000); // Give serial monitor time to open
  
  Serial.println("Setting up system...");
  
  // Initialize components
  display.begin();
  display.clearScreen();
  display.drawText("Starting...", 10, 10);
  
  if (!sdCard.begin()) {
    display.drawText("SD Card Init Failed!", 10, 40);
    delay(3000);
  }
  
  // Set up WiFi in AP mode
  WiFi.softAP(ap_ssid, ap_password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  display.drawText("AP: " + String(ap_ssid), 10, 40);
  display.drawText("IP: " + IP.toString(), 10, 70);
  
  // Initialize camera
  if (!camera.init()) {
    display.drawText("Camera Init Failed!", 10, 100);
    delay(3000);
  }
  
  // Initialize web server
  webServer.begin();
  
  // Initialize buttons
  buttons.begin();
  
  // Get initial image list
  updateImageList();
  
  delay(2000);
  display.clearScreen();
}

void loop() {
  // Handle button presses
  buttons.update();
  
  // Different behavior based on current mode
  switch (currentMode) {
    case SLIDESHOW: {
      // Cycle through images
      if (millis() - lastImageChangeTime > IMAGE_CHANGE_INTERVAL) {
        if (imageCount > 0) {
          display.displayImage(imageList[currentImageIndex]);
          currentImageIndex = (currentImageIndex + 1) % imageCount;
        } else {
          display.clearScreen();
          display.drawText("No images found", 10, 10);
        }
        lastImageChangeTime = millis();
      }
      
      // Check for mode change (photo button pressed)
      if (buttons.isPressed(BUTTON_PHOTO)) {
        currentMode = CAMERA_PREVIEW;
        display.clearScreen();
      }
      
      // Check for special photo (long press)
      if (buttons.isLongPressed(BUTTON_PHOTO)) {
        display.displayImage("/special_photo.jpg");
        while (!buttons.isPressed(BUTTON_BACK)) {
          buttons.update();
          delay(10);
        }
        // Go back to slideshow when back is pressed
        lastImageChangeTime = 0; // Force immediate image change
      }
      break;
    }
      
    case CAMERA_PREVIEW: {
      // Show camera preview
      camera_fb_t* fb = camera.capture();
      if (fb) {
        display.drawCameraFrame(fb->buf, fb->len);
        camera.returnFrameBuffer(fb);
      }
      
      // Check for photo capture (photo button pressed again)
      if (buttons.isPressed(BUTTON_PHOTO)) {
        currentMode = CAMERA_CAPTURE;
        display.drawText("Captured! Press again to save", 10, 10);
      }
      
      // Check for back button
      if (buttons.isPressed(BUTTON_BACK)) {
        currentMode = SLIDESHOW;
        lastImageChangeTime = 0; // Force immediate image change
      }
      break;
    }
      
    case CAMERA_CAPTURE: {
      // Show captured image and wait for confirmation
      
      // If photo button pressed again, save the image
      if (buttons.isPressed(BUTTON_PHOTO)) {
        camera_fb_t* fb = camera.capture();
        if (fb) {
          String filename = "/photo_" + String(millis()) + ".jpg";
          if (sdCard.saveFile(filename, fb->buf, fb->len)) {
            display.drawText("Saved!", 10, 30);
            updateImageList(); // Update the image list
          } else {
            display.drawText("Save failed!", 10, 30);
          }
          camera.returnFrameBuffer(fb);
          delay(1000);
        }
        currentMode = SLIDESHOW;
        lastImageChangeTime = 0;
      }
      
      // If back button pressed, discard and go back to slideshow
      if (buttons.isPressed(BUTTON_BACK)) {
        currentMode = SLIDESHOW;
        lastImageChangeTime = 0;
      }
      break;
    }
  }
  
  delay(10); // Small delay to prevent CPU hogging
}