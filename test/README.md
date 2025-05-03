# ESP32 TFT Photo Display Project

This project utilizes an ESP32 microcontroller to create a photo display system that interfaces with an ILI9341 TFT SPI screen. The system allows users to upload JPG or PNG files to an onboard SD card, which can then be displayed on the TFT screen. Additionally, it features a slideshow mode and buttons for navigating between different modes, including "photo taking mode," "special pic," and "back."

## Project Structure

- **src/**: Contains the source code files.
  - **main.cpp**: The main entry point of the application.
  - **config.h**: Configuration settings for the project.
  - **camera/**: Contains files related to camera functionality.
    - **camera.cpp**: Implementation of camera functions.
    - **camera.h**: Header file for camera functions.
  - **display/**: Contains files related to the display functionality.
    - **display.cpp**: Implementation of display functions.
    - **display.h**: Header file for display functions.
  - **sdcard/**: Contains files related to SD card operations.
    - **sdcard.cpp**: Implementation of SD card functions.
    - **sdcard.h**: Header file for SD card functions.
  - **webserver/**: Contains files related to the web server functionality.
    - **webserver.cpp**: Implementation of web server functions.
    - **webserver.h**: Header file for web server functions.
  - **interface/**: Contains files related to user interface and button handling.
    - **buttons.cpp**: Implementation of button functions.
    - **buttons.h**: Header file for button functions.
  - **utils/**: Contains utility functions, including image processing.
    - **image_processing.cpp**: Implementation of image processing functions.
    - **image_processing.h**: Header file for image processing functions.
  
- **data/**: Contains web files for the web server.
  - **index.html**: The main HTML file served by the web server.
  - **style.css**: CSS styles for the web interface.
  - **script.js**: JavaScript for client-side functionality.

- **lib/**: Contains libraries used in the project.
  - **README.md**: Documentation for libraries.

- **include/**: Contains additional header files.
  - **README.md**: Documentation for included files.

- **test/**: Contains test files and documentation.
  - **README.md**: Documentation for testing procedures.

- **platformio.ini**: Configuration file for PlatformIO.

## Features

- Upload images to the ESP32's SD card via a web interface.
- Display uploaded images on the ILI9341 TFT screen.
- Slideshow feature to cycle through images.
- User interface with buttons for navigating modes.

## Getting Started

1. Clone the repository to your local machine.
2. Install the required libraries and dependencies.
3. Connect the ESP32 to your computer and upload the code using PlatformIO.
4. Access the web interface by connecting to the ESP32's Wi-Fi network.
5. Upload images and enjoy the photo display features!

## License

This project is open-source and available for modification and distribution under the MIT License.