#ifndef CAMERA_H
#define CAMERA_H

#include "esp_camera.h"

class Camera {
public:
    Camera();
    bool init();
    camera_fb_t* capture();
    void returnFrameBuffer(camera_fb_t* fb);
    void setResolution(framesize_t resolution);
    void setQuality(int quality);
    
private:
    camera_config_t config;
    bool initialized;
};

#endif // CAMERA_H