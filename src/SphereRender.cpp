#include "sphere.h"
#include "Framebuffer.h"
#include "PerspectiveCamera.h"
#include "Triangle.h"
#include "Lambertian.h"
#include "Blinn-Phong.h"



int main() {
    
    //std::shared_ptr<shape> myTriangle = std::make_shared<Triangle>(vec3(0.0f, 1.0f, -10.0f), vec3(-1.0f, -1.0f, -10.0f), vec3(1.0f, -1.0f, -10.0f));
    int width = 900;
    int height = 600;
    Framebuffer fb(width, height);

    vec3 sphereCenter = vec3(0.0f, 0.0f, -15.0f);
    float sphereRadius = 0.7f;
    sphere mySphere(sphereCenter, sphereRadius);
    sphere mysphere2 (vec3(1.0f, 0.0f, -10.0f), 0.7f);
    sphere mysphere3 (vec3(-1.0f, 0.0f, -10.0f), 0.7f);
    //std::shared_ptr<shape> mySphere = std::make_shared<sphere>(mySphere, mysphere2, mysphere3);
    PerspectiveCamera defaultCam(width, height);
    hit_record rec;
    Lambertian lambertianShader;
    BlinnPhong blinnPhongShader;

    for(int x = 0; x < width; ++x) {
        for(int y = 0; y < height; ++y) {
            ray r = defaultCam.generateRay(x, y);
            if(mySphere.intersect(r, 0.001f, 100.0f, rec)) {
                color c = lambertianShader.shade(rec) * color(1.0f, 0.0f, 0.0f);
                fb.setPixelColor(x, y, c);
            } else if (mysphere2.intersect(r, 0.001f, 100.0f, rec)) {
                color c = lambertianShader.shade(rec) * color(0.0f, 1.0f, 0.0f);
                fb.setPixelColor(x, y, c);
            } else if (mysphere3.intersect(r, 0.001f, 100.0f, rec)) {
                color c = lambertianShader.shade(rec) * color(0.0f, 0.0f, 1.0f);
                fb.setPixelColor(x, y, c);
            } else {
                color c = lambertianShader.shade(rec) * color(0.2f, 0.2f, 0.2f);
                fb.setPixelColor(x, y, c);
            }
        }
    }
    

    fb.exportAsPNG("SphereShaderTest.png");

    fb.clearToColor(color(0.0f, 0.0f, 0.0f));
    for(int x = 0; x < width; ++x) {
        for(int y = 0; y < height; ++y) {
            ray r = defaultCam.generateRay(x, y);
            if(mySphere.intersect(r, 0.001f, 100.0f, rec)) {
                color c = blinnPhongShader.shade(rec) * color(1.0f, 1.0f, 1.0f);
                fb.setPixelColor(x, y, c);
            } else {
                fb.setPixelColor(x, y, color(0.0f, 1.0f, 0.0f));
            }
        }
    }
    fb.exportAsPNG("SphereBlinnPhongTest.png");

    width = 200;
    height = 200;
    vec3 TriangleVertexA(0.0f, 1.0f, -10.0f);
    vec3 TriangleVertexB(-1.0f, -1.0f, -10.0f);
    vec3 TriangleVertexC(1.0f, -1.0f, -10.0f); 
    Triangle myTriangle(TriangleVertexA, TriangleVertexB, TriangleVertexC);
    fb = Framebuffer(width, height);
    for(int x = 0; x < width; ++x) {
        for(int y = 0; y < height; ++y) {
            ray r = defaultCam.generateRay(x, y);
            if(myTriangle.intersect(r, 0.001f, 100.0f, rec)) {
                color c = lambertianShader.shade(rec);
                fb.setPixelColor(x, height - 1 - y, c);
            } else {
                fb.setPixelColor(x, height - 1 - y, color(1.0f, 0.0f, 0.0f));
            }
        }
    }

    fb.exportAsPNG("TriangleShaderTest.png");


    

    return 0;
}