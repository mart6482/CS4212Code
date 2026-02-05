#include "PerspectiveCamera.h"
#include "Framebuffer.h"

int main (){
    int width = 200;
    int height = 200;
    Framebuffer fb(width, height);
    vec3 position = vec3(3, -4, 12);
    vec3 direction = vec3( -8, -5, 10.0);
    float focalLength = 0.001f;
    float imagePlaneWidth = 0.5f;
    float imagePlaneHeight = 0.5f;

    PerspectiveCamera customCam(position, direction, focalLength, imagePlaneWidth, imagePlaneHeight, width, height);
    fb.clearToColor(color(0.0, 0.0, 0.0));
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            ray r = customCam.generateRay(i, j);
            color pixelColor = color(
                0.5f * (r.getDirection().x() + 1.0f),
                0.5f * (r.getDirection().y() + 1.0f),
                0.5f * (r.getDirection().z() + 1.0f)
            );
            fb.setPixelColor(i, j, pixelColor);
        }
    }
    fb.exportAsPNG("RayTracerTest.png");

    return 0;
}
