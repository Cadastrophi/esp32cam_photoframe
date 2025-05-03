# ESP32 TFT Photo Display Project

This project is designed to utilize an ESP32 microcontroller to interface with an ILI9341 TFT SPI screen, allowing users to upload JPG or PNG files to an onboard SD card. The uploaded images will be displayed on the TFT screen, and a slideshow feature will be implemented with buttons for "photo taking mode," "special pic," and "back."

## Project Structure

- **src/**: Contains the main application code.
  - **main.cpp**: The entry point of the application.
  - **config.h**: Configuration settings for the project.
  - **camera/**: Code related to camera functionality.
    - **camera.cpp**: Implementation of camera functions.
    - **camera.h**: Header file for camera functions.
  - **display/**: Code for managing the TFT display.
    - **display.cpp**: Implementation of display functions.
    - **display.h**: Header file for display functions.
  - **sdcard/**: Code for managing the SD card.
    - **sdcard.cpp**: Implementation of SD card functions.
    - **sdcard.h**: Header file for SD card functions.
  - **webserver/**: Code for hosting a web server.
    - **webserver.cpp**: Implementation of web server functions.
    - **webserver.h**: Header file for web server functions.
  - **interface/**: Code for managing user interface buttons.
    - **buttons.cpp**: Implementation of button functions.
    - **buttons.h**: Header file for button functions.
  - **utils/**: Utility functions, including image processing.
    - **image_processing.cpp**: Implementation of image processing functions.
    - **image_processing.h**: Header file for image processing functions.

- **data/**: Contains web files for the web server.
  - **index.html**: The main HTML file for the web interface.
  - **style.css**: CSS styles for the web interface.
  - **script.js**: JavaScript for the web interface.

- **lib/**: Additional libraries used in the project.
  - **README.md**: Documentation for libraries.

- **include/**: Additional header files or documentation.
  - **README.md**: Documentation for the include directory.

- **test/**: Contains test files or documentation.
  - **README.md**: Documentation for tests.

- **platformio.ini**: Configuration file for PlatformIO.

- **README.md**: Main documentation for the project.

## Features

- Upload images via a web interface.
- Display images on the ILI9341 TFT screen.
- Slideshow functionality to cycle through images.
- User interface buttons for navigation and actions.

## Getting Started

1. Clone the repository.
2. Install the required libraries.
3. Connect the ESP32 to your computer.
4. Upload the code using PlatformIO.
5. Access the web interface to upload images and control the slideshow.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.