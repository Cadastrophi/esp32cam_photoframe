#include "webserver.h"
#include <SD.h>
#include "config.h"

extern SDCard sdCard;

void WebServer::begin() {
    // Define web server routes
    server.on("/", HTTP_GET, [this](AsyncWebServerRequest *request) {
        handleRoot(request);
    });
    
    server.on("/list", HTTP_GET, [this](AsyncWebServerRequest *request) {
        handleFileList(request);
    });
    
    server.on("/delete", HTTP_GET, [this](AsyncWebServerRequest *request) {
        handleFileDelete(request);
    });
    
    server.on("/upload", HTTP_POST, [](AsyncWebServerRequest *request) {
        request->send(200);
    }, [this](AsyncWebServerRequest *request, const String& filename, size_t index, uint8_t *data, size_t len, bool final) {
        handleFileUpload(request, filename, index, data, len, final);
    });
    
    server.onNotFound([this](AsyncWebServerRequest *request) {
        if (!handleFileRead(request, request->url())) {
            handleNotFound(request);
        }
    });
    
    server.begin();
    Serial.println("Web server started");
}

void WebServer::handleRoot(AsyncWebServerRequest *request) {
    String html = generateGalleryHTML();
    request->send(200, "text/html", html);
}

void WebServer::handleFileUpload(AsyncWebServerRequest *request, const String& filename,
                                 size_t index, uint8_t *data, size_t len, bool final) {
    static File uploadFile;

    if (index == 0) {
        String path = "/" + filename;
        Serial.println("Upload Start: " + path);
        if (SD.exists(path)) {
            SD.remove(path);
        }
        uploadFile = SD.open(path, FILE_WRITE);
    }

    if (uploadFile) {
        uploadFile.write(data, len);
    }

    if (final) {
        Serial.println("Upload End: " + filename + ", size: " + String(index + len));
        if (uploadFile) {
            uploadFile.close();
        }
    }
}

void WebServer::handleFileList(AsyncWebServerRequest *request) {
    String jsonResponse = "[";
    File root = SD.open("/");
    if (root) {
        File file = root.openNextFile();
        bool firstFile = true;
        
        while (file) {
            String filename = String(file.name());
            String lowerFilename = filename;
            lowerFilename.toLowerCase();
            
            if (!file.isDirectory() && 
                (lowerFilename.endsWith(".jpg") || 
                 lowerFilename.endsWith(".jpeg") || 
                 lowerFilename.endsWith(".png"))) {
                
                if (!firstFile) {
                    jsonResponse += ",";
                }
                firstFile = false;
                
                jsonResponse += "{\"name\":\"" + filename + "\",\"size\":" + String(file.size()) + "}";
            }
            
            file = root.openNextFile();
        }
        
        root.close();
    }
    jsonResponse += "]";
    
    request->send(200, "application/json", jsonResponse);
}

void WebServer::handleFileDelete(AsyncWebServerRequest *request) {
    String filename;
    if (request->hasParam("file")) {
        filename = request->getParam("file")->value();
        if (!filename.startsWith("/")) {
            filename = "/" + filename;
        }
    }
    
    if (request->hasParam("confirm") && request->getParam("confirm")->value() == "yes") {
        if (sdCard.deleteFile(filename)) {
            request->redirect("/");
        } else {
            request->send(500, "text/plain", "Delete failed");
        }
    } else {
        // Show confirmation page
        String html = generateDeleteConfirmHTML(filename);
        request->send(200, "text/html", html);
    }
}

void WebServer::handleNotFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "File Not Found");
}

String WebServer::getContentType(const String& filename) {
    if (filename.endsWith(".html")) return "text/html";
    else if (filename.endsWith(".css")) return "text/css";
    else if (filename.endsWith(".js")) return "application/javascript";
    else if (filename.endsWith(".png")) return "image/png";
    else if (filename.endsWith(".jpg") || filename.endsWith(".jpeg")) return "image/jpeg";
    return "text/plain";
}

bool WebServer::handleFileRead(AsyncWebServerRequest *request, const String& path) {
    String contentType = getContentType(path);
    String filePath = path;
    
    if (filePath.endsWith("/")) filePath += "index.html";
    
    if (SD.exists(filePath)) {
        File file = SD.open(filePath, FILE_READ);
        if (file) {
            request->send(SD, filePath, contentType);
            file.close();
            return true;
        }
    }
    return false;
}

String WebServer::generateGalleryHTML() {
    String html = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width,initial-scale=1'>";
    html += "<title>ESP32-CAM Photo Frame</title>";
    html += "<style>";
    html += "body{font-family:Arial,sans-serif;margin:0;padding:20px;background:#f0f0f0;}";
    html += "h1{color:#333;}";
    html += ".gallery{display:flex;flex-wrap:wrap;margin:0 -10px;}";
    html += ".img-container{position:relative;margin:10px;width:150px;height:150px;}";
    html += ".img-container img{width:100%;height:100%;object-fit:cover;border:1px solid #ddd;}";
    html += ".delete-btn{position:absolute;top:5px;right:5px;background:rgba(255,0,0,0.7);color:white;";
    html += "border:none;border-radius:50%;width:20px;height:20px;line-height:20px;text-align:center;cursor:pointer;}";
    html += ".upload-form{margin-bottom:20px;padding:15px;background:#fff;border-radius:5px;box-shadow:0 1px 3px rgba(0,0,0,0.1);}";
    html += "input[type=file]{margin-bottom:10px;}";
    html += "input[type=submit]{background:#4CAF50;color:white;padding:10px 15px;border:none;border-radius:4px;cursor:pointer;}";
    html += "input[type=submit]:hover{background:#45a049;}";
    html += "</style></head><body>";
    
    html += "<h1>ESP32-CAM Photo Frame</h1>";
    
    // Upload form
    html += "<div class='upload-form'>";
    html += "<form method='post' action='/upload' enctype='multipart/form-data'>";
    html += "<input type='file' name='file' accept='.jpg,.jpeg,.png'>";
    html += "<input type='submit' value='Upload'>";
    html += "</form></div>";
    
    // Image gallery (populated via JavaScript)
    html += "<div class='gallery' id='gallery'></div>";
    
    // JavaScript to load the images
    html += "<script>";
    html += "fetch('/list').then(response => response.json()).then(files => {";
    html += "  const gallery = document.getElementById('gallery');";
    html += "  files.forEach(file => {";
    html += "    const container = document.createElement('div');";
    html += "    container.className = 'img-container';";
    html += "    const img = document.createElement('img');";
    html += "    img.src = '/' + file.name;";
    html += "    container.appendChild(img);";
    html += "    const deleteBtn = document.createElement('a');";
    html += "    deleteBtn.className = 'delete-btn';";
    html += "    deleteBtn.innerHTML = 'X';";
    html += "    deleteBtn.href = '/delete?file=' + file.name;";
    html += "    container.appendChild(deleteBtn);";
    html += "    gallery.appendChild(container);";
    html += "  });";
    html += "});";
    html += "</script>";
    
    html += "</body></html>";
    return html;
}

String WebServer::generateDeleteConfirmHTML(const String& filename) {
    String html = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width,initial-scale=1'>";
    html += "<title>Confirm Delete</title>";
    html += "<style>";
    html += "body{font-family:Arial,sans-serif;margin:0;padding:20px;background:#f0f0f0;}";
    html += "h1{color:#333;}";
    html += ".container{max-width:600px;margin:0 auto;background:#fff;padding:20px;border-radius:5px;box-shadow:0 1px 3px rgba(0,0,0,0.1);}";
    html += ".preview{max-width:100%;max-height:300px;display:block;margin:20px auto;}";
    html += ".btn{display:inline-block;padding:10px 20px;margin:10px 5px;border-radius:4px;text-decoration:none;}";
    html += ".delete{background:#f44336;color:white;}";
    html += ".cancel{background:#ccc;color:black;}";
    html += "</style></head><body>";
    
    html += "<div class='container'>";
    html += "<h1>Confirm Delete</h1>";
    html += "<p>Are you sure you want to delete this image?</p>";
    html += "<img src='" + filename + "' class='preview'>";
    html += "<div>";
    html += "<a href='/delete?file=" + filename + "&confirm=yes' class='btn delete'>Delete</a>";
    html += "<a href='/' class='btn cancel'>Cancel</a>";
    html += "</div></div></body></html>";
    
    return html;
}