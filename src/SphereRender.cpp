#include "sphere.h"
#include "Framebuffer.h"
#include "PerspectiveCamera.h"



int main() {
    int width = 900;
    int height = 600;
    Framebuffer fb(width, height);

    vec3 sphereCenter = vec3(0.0f, 0.0f, -15.0f);
    float sphereRadius = 1.0f;
    sphere mySphere(sphereCenter, sphereRadius);
    PerspectiveCamera defaultCam(width, height);

    for(int x = 0; x < width; ++x) {
        for(int y = 0; y < height; ++y) {
            ray r = defaultCam.generateRay(x, y);
            if(mySphere.intersect(r)) {
                fb.setPixelColor(x, y, color(1.0f, 0.0f, 0.0f));
            } else {
                fb.setPixelColor(x, y, color(1.0f, 1.0f, 1.0f));
            }
        }
    }
    

    fb.exportAsPNG("JapanFlagTest2.png");

    return 0;
}