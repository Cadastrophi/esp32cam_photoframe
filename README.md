# ESP32 TFT Photo Display Project

This project utilizes an ESP32 microcontroller to create a photo display system that interfaces with an ILI9341 TFT SPI screen. The system allows users to upload JPG or PNG files to an onboard SD card via a web server. Once uploaded, the images can be displayed on the TFT screen, and a slideshow feature is implemented for easy viewing.

## Features

- **Web Server**: Hosts a web interface for uploading images to the SD card.
- **Image Display**: Displays uploaded images on the ILI9341 TFT screen.
- **Slideshow Mode**: Automatically cycles through uploaded images.
- **User Interface**: Includes buttons for navigating between modes:
  - Photo Taking Mode
  - Special Picture Mode
  - Back to Main Menu

## Directory Structure

- `src/`: Contains the source code files.
  - `main.cpp`: The main entry point of the application.
  - `config.h`: Configuration settings for the project.
  - `camera/`: Camera-related functionalities.
    - `camera.cpp`: Implementation of camera functions.
    - `camera.h`: Header file for camera functions.
  - `display/`: Functions for handling the TFT display.
    - `display.cpp`: Implementation of display functions.
    - `display.h`: Header file for display functions.
  - `sdcard/`: Functions for managing the SD card.
    - `sdcard.cpp`: Implementation of SD card functions.
    - `sdcard.h`: Header file for SD card functions.
  - `webserver/`: Web server functionalities.
    - `webserver.cpp`: Implementation of web server functions.
    - `webserver.h`: Header file for web server functions.
  - `interface/`: User interface components.
    - `buttons.cpp`: Implementation of button functionalities.
    - `buttons.h`: Header file for button functionalities.
  - `utils/`: Utility functions, including image processing.
    - `image_processing.cpp`: Implementation of image processing functions.
    - `image_processing.h`: Header file for image processing functions.
- `data/`: Contains web files for the web server.
  - `index.html`: Main HTML file for the web interface.
  - `style.css`: CSS file for styling the web interface.
  - `script.js`: JavaScript file for client-side functionality.
- `lib/`: Library files (if any).
- `include/`: Additional include files (if any).
- `test/`: Test files (if any).
- `platformio.ini`: PlatformIO configuration file.

## Getting Started

1. **Hardware Requirements**:
   - ESP32 development board
   - ILI9341 TFT display
   - Micro SD card module
   - Micro SD card

2. **Software Requirements**:
   - PlatformIO IDE or compatible environment
   - Required libraries for TFT display and SD card functionality

3. **Installation**:
   - Clone the repository or download the project files.
   - Open the project in PlatformIO.
   - Install the necessary libraries as specified in `platformio.ini`.
   - Upload the code to the ESP32.

4. **Usage**:
   - Connect to the ESP32's Wi-Fi network.
   - Open a web browser and navigate to the ESP32's IP address.
   - Use the web interface to upload images.
   - Navigate through the images using the buttons on the TFT display.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.