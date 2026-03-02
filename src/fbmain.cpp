#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include "handleGraphicsArgs.h"
#include "ArgumentParsing.h"
#include "Framebuffer.h"
#include "camera.h"
#include "PerspectiveCamera.h"
#include "ray.h"
#include "Shape.h"
#include "Sphere.h"
#include "Triangle.h"
#include "NormalShader.h"
#include "Lambertian.h"
#include "Blinn-Phong.h"
#include "Light.h"
#include "RayTracer.h"
#include "MirrorShader.h"
#include "DiffuseShader.h"
#include <random>




float randomOffset()
{
  static std::uniform_real_distribution<float> distribution(0.0, 1.0);
  static std::mt19937 generator;
  return distribution(generator);
}

int main(int argc, char *argv[])
{
  //process args
  sivelab::GraphicsArgs args;
  args.process(argc, argv);

  int width = args.width;
  int height = args.height;
  int maxDepth = args.recursionDepth;
  int rpp_NSquare = args.rpp;

  //debug print out args
  /*std::cout << "Argc = " << argc << std::endl;
  std::cout << "Width: " << args.width << std::endl;
  std::cout << "Height: " << args.height << std::endl;
  std::cout << "rpp: " << args.rpp << std::endl;
  std::cout << "Recursion Depth: " << args.recursionDepth << std::endl;*/



  //Framebuffer
  Framebuffer fb(width, height);

  // Camera 
  PerspectiveCamera cam(vec3(0, 3.0, 2.0), vec3(0, -1.5, -3.0), .4, 0.6, 0.6, width, height);

  std::vector<std::shared_ptr<Shape>> shapes;

  //shaders
  auto lambertianShader = std::make_shared<Lambertian>();
  auto blinnPhongShader = std::make_shared<BlinnPhong>();
  blinnPhongShader->setEyePosition(cam.getPosition());
  auto mirrorShader = std::make_shared<MirrorShader>();
  auto diffuseGroundShader = std::make_shared<DiffuseShader>(vec3(0.8, 0.8, 0.8));
  auto diffuse_redShader = std::make_shared<DiffuseShader>(vec3(1.0, 0.0, 0.0));


  //lights
  std::vector<std::shared_ptr<PointLight>> lights;
  lights.push_back(std::make_shared<PointLight>(vec3(3, 5, 2), vec3(1.0, 1.0, 1.0)));
  lights.push_back(std::make_shared<PointLight>(vec3(-3, 5, 2), vec3(1.0, 1.0, 1.0)));

  //objects
  // Ground plane: Diffuse shader
  shapes.push_back(std::make_shared<Triangle>(
    vec3(0, 0, 5), vec3(200, 0, -200), vec3(-200, 0, -200), vec3(0.8, 0.8, 0.8), diffuseGroundShader));
    
  // Blue sphere: Lambertian shader
  shapes.push_back(std::make_shared<Sphere>(
    vec3(-2.5, 1.0, -4.0), 1.0f, vec3(0.0, 0.0, 1.0), lambertianShader));

  // Green sphere: Blinn-Phong shader
  shapes.push_back(std::make_shared<Sphere>(
    vec3(0, 1.0, -5.0), 1.0f, vec3(0.0, 1.0, 0.0), blinnPhongShader));

  // Red sphere: Diffuse shader
  shapes.push_back(std::make_shared<Sphere>(
    vec3(-1.3, 0.8, -1), 0.8f, vec3(1.0, 0.0, 0.0), diffuse_redShader));

  // Mirror sphere: Mirror shader
  shapes.push_back(std::make_shared<Sphere>(
    vec3(1.5, 1.2, -2.5), 1.10f, vec3(0.8, 0.8, 0.8), mirrorShader));

  
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      vec3 accumulatedColor(0, 0, 0);
      
      for(int p = 0; p < rpp_NSquare; p++){
        for(int q = 0; q < rpp_NSquare; q++){
          float pOffset = (p + randomOffset()) / rpp_NSquare;
          float qOffset = (q + randomOffset()) / rpp_NSquare;

          ray r = cam.generateRay(x + pOffset, y + qOffset);
          accumulatedColor += computeRayColor(r, shapes, lights, maxDepth);
        }
      }

      vec3 pixelColor = accumulatedColor / (float)(rpp_NSquare * rpp_NSquare);
      fb.setPixelColor(x, height - y - 1, pixelColor);
    }
  }

  fb.exportAsPNG("ALL_shaders.png");

  return 0;
}