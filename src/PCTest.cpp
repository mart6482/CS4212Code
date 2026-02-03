#include "PerspectiveCamera.h"
#include "Framebuffer.h"

int main (){
    int width = 200;
    int height = 200;
    Framebuffer fb(width, height);
    PerspectiveCamera cam(width, height);
    fb.clearToColor(color(0.0, 0.0, 0.0));
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            ray r = cam.generateRay(i, j);
            // For testing, we color pixels based on the ray direction
            color pixelColor = color(
                0.5 * (r.getDirection().x() + 1.0),
                0.5 * (r.getDirection().y() + 1.0),
                0.5 * (r.getDirection().z() + 1.0)
            );
            fb.setPixelColor(i, j, pixelColor);
        }
    }
    fb.exportAsPNG("PCTestOutput.png");


    return 0;
}
