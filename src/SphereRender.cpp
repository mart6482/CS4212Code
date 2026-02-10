#include "sphere.h"
#include "Framebuffer.h"
#include "PerspectiveCamera.h"
#include "triangle.h"



int main() {
    /*int width = 900;
    int height = 600;
    Framebuffer fb(width, height);

    vec3 sphereCenter = vec3(0.0f, 0.0f, -15.0f);
    float sphereRadius = 0.7f;
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
    

    fb.exportAsPNG("JapanFlagTest2.png");*/

    int width = 200;
    int height = 200;
    Framebuffer fb(width, height);
    vec3 TriangleVertexA(0.0f, 1.0f, -10.0f);
    vec3 TriangleVertexB(-1.0f, -1.0f, -10.0f);
    vec3 TriangleVertexC(1.0f, -1.0f, -10.0f); 
    Triangle myTriangle(TriangleVertexA, TriangleVertexB, TriangleVertexC);
    PerspectiveCamera defaultCam(width, height);
    for(int x = 0; x < width; ++x) {
        for(int y = 0; y < height; ++y) {
            ray r = defaultCam.generateRay(x, y);
            if(myTriangle.intersect(r)) {
                fb.setPixelColor(x, height - 1 - y, color(1.0f, 0.0f, 0.0f));
            } else {
                fb.setPixelColor(x, height - 1 - y, color(1.0f, 1.0f, 1.0f));
            }
        }
    }

    fb.exportAsPNG("TriangleTest.png");


    

    return 0;
}