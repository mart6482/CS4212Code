#include "sphere.h"
#include "Framebuffer.h"
#include "PerspectiveCamera.h"
#include "Triangle.h"
#include "Lambertian.h"
#include "Blinn-Phong.h"
#include <random>

float randomFloat() {
    static std::mt19937 generator;
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    return distribution(generator);
}



int main() {
    
    //std::shared_ptr<shape> myTriangle = std::make_shared<Triangle>(vec3(0.0f, 1.0f, -10.0f), vec3(-1.0f, -1.0f, -10.0f), vec3(1.0f, -1.0f, -10.0f));
    //std::shared_ptr<shape> mySphere = std::make_shared<sphere>(mySphere, mysphere2, mysphere3);
    int width = 900;
    int height = 600;
    Framebuffer fb(width, height);

    vec3 sphereCenter = vec3(0.0f, 0.0f, -15.0f);
    float sphereRadius = 0.5f;
    sphere mySphere(sphereCenter, sphereRadius);
    sphere mysphere2 (vec3(1.3f, 0.0f, -15.0f), 0.5f);
    sphere mysphere3 (vec3(-1.3f, 0.0f, -15.0f), 0.5f);
    Triangle floor (vec3(-50.0f, 1.0f, 5.0f), vec3(50.0f, 1.0f, 5.0f), vec3(0.0f, 1.0f, -50.0f));
    PerspectiveCamera defaultCam(width, height);
    hit_record rec;
    Lambertian lambertianShader;
    BlinnPhong blinnPhongShader;
    int rpp_NSquare = 4;
    for(int x = 0; x < width; ++x) {
        for(int y = 0; y < height; ++y) {
            color c = color(0.0f, 0.0f, 0.0f);
            
            for(int p = 0; p<rpp_NSquare; p++){
                for(int q = 0; q<rpp_NSquare; q++){
                    float tmin = 0.0001f;
                    float tmax = std::numeric_limits<float>::infinity();

                    float pOffset = (p + randomFloat())/rpp_NSquare;
                    float qOffset = (q + randomFloat())/rpp_NSquare;
                    ray r = defaultCam.generateRay(x + pOffset, y + qOffset);
                    float closest_t = tmax;
                    bool hitAnything = false;
                    color hitColor;

                    if (mySphere.intersect(r, tmin, closest_t, rec)) {
                        hitAnything = true;
                        closest_t = rec.t;
                        
                        // Compute reflected ray and trace it
                        vec3 reflected_dir = r.getDirection() - 2.0f * dot(r.getDirection(), rec.normal) * rec.normal;
                        normalize(reflected_dir);
                        ray reflected_ray(rec.p + 0.001f * rec.normal, reflected_dir);
                        
                        hit_record reflected_hit;
                        if (mysphere2.intersect(reflected_ray, 0.001f, std::numeric_limits<float>::infinity(), reflected_hit)) {
                            hitColor = lambertianShader.shade(reflected_hit) * color(0, 1, 0);
                        } else if (mysphere3.intersect(reflected_ray, 0.001f, std::numeric_limits<float>::infinity(), reflected_hit)) {
                            hitColor = lambertianShader.shade(reflected_hit) * color(0, 0, 1);
                        } else if (floor.intersect(reflected_ray, 0.001f, std::numeric_limits<float>::infinity(), reflected_hit)) {
                            hitColor = lambertianShader.shade(reflected_hit) * color(0.1, 0.5, 0.23);
                        } else {
                            hitColor = color(0.4f, 0.4f, 0.4f); // Reflective environment
                        }
                    }

                    if (mysphere2.intersect(r, tmin, closest_t, rec)) {
                        hitAnything = true;
                        closest_t = rec.t;
                        hitColor = lambertianShader.shade(rec) * color(0,1,0);
                    }

                    if (mysphere3.intersect(r, tmin, closest_t, rec)) {
                        hitAnything = true;
                        closest_t = rec.t;
                        hitColor = lambertianShader.shade(rec) * color(0,0,1);
                    }

                    if (floor.intersect(r, tmin, closest_t, rec)) {
                        hitAnything = true;
                        closest_t = rec.t;
                        hitColor = color(0.1, 0.5, 0.23);
                    }

                    if (hitAnything)
                        c += hitColor;
                    else
                        c += color(0.2f, 0.2f, 0.2f);
                }
            }

            c = c / (rpp_NSquare * rpp_NSquare);
            fb.setPixelColor(x, y, c);
        }
    }
    fb.exportAsPNG("AntiAliasing.png");

    fb.clearToColor(color(0.0f, 0.0f, 0.0f));
    for(int x = 0; x < width; ++x) {
        for(int y = 0; y < height; ++y) {
            color c = color(0.0f, 0.0f, 0.0f);
                float tmin = 1.0f;
                float tmax = std::numeric_limits<float>::infinity();
                ray r = defaultCam.generateRay(x , y);
                if(mySphere.intersect(r, tmin, tmax, rec)) {
                    c = lambertianShader.shade(rec) * color(1.0f, 0.0f, 0.0f);
                }else {
                    c = color(0.2f, 0.2f, 0.2f);
                }
            fb.setPixelColor(x, y, c);
        }
    };


    fb.exportAsPNG("SphereShaderNoAliasing.png");



    fb.clearToColor(color(0.0f, 0.0f, 0.0f));
    float imagePlaneWidth = 0.5f;
    float imagePlaneHeight = imagePlaneWidth * (float)height / (float)width;
    PerspectiveCamera cam(vec3(0.0f, 3.0f, 4.0f), vec3(0.0f, -1.5f, -3.0f), 0.4f, imagePlaneWidth, imagePlaneHeight, width, height);
    Triangle LargeTri(vec3(-1000.0f, 0.0f, 0.0f), vec3(1000.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1000.0f));
    sphere RedSphere(vec3(-1.2f, 1.0f, -3.0f), 1.0f);
    sphere mirrorSphere(vec3(1.2f, 1.10f, -4.0f), 1.10f);
    for(int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            ray r = cam.generateRay(x, y);
            color c = color(0.0f, 0.0f, 0.0f);
            hit_record rec;
            if (RedSphere.intersect(r, 0.001f, std::numeric_limits<float>::infinity(), rec)) {
                c = blinnPhongShader.shade(rec) * color(1.0f, 0.0f, 0.0f);
            } else if (mirrorSphere.intersect(r, 0.001f, std::numeric_limits<float>::infinity(), rec)) {
                vec3 reflected_dir = r.getDirection() - 2.0f * dot(r.getDirection(), rec.normal) * rec.normal;
                normalize(reflected_dir);
                ray reflected_ray(rec.p + 0.001f * rec.normal, reflected_dir);
                
                hit_record reflected_hit;
                if (RedSphere.intersect(reflected_ray, 0.001f, std::numeric_limits<float>::infinity(), reflected_hit)) {
                    c = blinnPhongShader.shade(reflected_hit) * color(1, 0, 0);
                } else if (LargeTri.intersect(reflected_ray, 0.001f, std::numeric_limits<float>::infinity(), reflected_hit)) {
                    c = lambertianShader.shade(reflected_hit) * color(0.8f, 0.8f, 0.8f);
                } else {
                    c = color(0.1f, 0.1f, 0.5f); // Reflective environment
                }
            } else if (LargeTri.intersect(r, 0.001f, std::numeric_limits<float>::infinity(), rec)) {
                c = lambertianShader.shade(rec) * color(0.1f, 0.1f, 0.1f);
            } else {
                c = color(0.1f, 0.1f, 0.3f);
            }
            fb.setPixelColor(width-1-x, height-1-y, c);
        }
    }
    fb.exportAsPNG("ReflectionTest.png");



    /*fb.clearToColor(color(0.0f, 0.0f, 0.0f));
    for(int x = 0; x < width; ++x) {
        for(int y = 0; y < height; ++y) {
            ray r = defaultCam.generateRay(x, y);
            if(mySphere.intersect(r, 0.001f, 100.0f, rec)) {
                color c = blinnPhongShader.shade(rec) * color(1.0f, 0.0f, 0.0f);
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

    fb.exportAsPNG("TriangleShaderTest.png");*/


    

    return 0;
}