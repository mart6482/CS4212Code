#define _USE_MATH_DEFINES
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
#include <cmath>
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
  

  //Framebuffer
  Framebuffer fb(width, height);

  // Camera 
  PerspectiveCamera cam(vec3(0, 4.0, 2.0), vec3(0, -2, -3.0), .4, 0.6, 0.6, width, height);

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
  /*
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
    vec3(1.5, 1.2, -2.5), 1.10f, vec3(0.8, 0.8, 0.8), mirrorShader));*/

  // Central mirror sphere
  vec3 center(0.0f, 1.0f, -4.0f);
  shapes.push_back(std::make_shared<Sphere>(
      center, 1.2f, vec3(0.9, 0.9, 0.9), mirrorShader));

  // Surrounding spheres in a circle
  float radiusFromCenter = 3.0f;
  float sphereRadius = 0.7f;
  std::vector<std::shared_ptr<shader>> shaderList = {
      lambertianShader,
      blinnPhongShader,
      lambertianShader,
      blinnPhongShader,
      lambertianShader,
      blinnPhongShader,
      lambertianShader,
      diffuse_redShader
  };

  std::vector<vec3> colors = {
      vec3(1,0,0),
      vec3(1,.5,0),
      vec3(1,1,0),
      vec3(0,1,0),
      vec3(0,1,.5),
      vec3(0,1,1),
      vec3(0,0,1),
      vec3(0.5,0,1)
  };

  for (int i = 0; i < 8; i++) {
      float angle = i * (2.0f * M_PI / 8.0f);

      float x = center.x() + radiusFromCenter * cos(angle);
      float z = center.z() + radiusFromCenter * sin(angle);

      vec3 pos(x, 1.0f, z);

      shapes.push_back(std::make_shared<Sphere>(
          pos,
          sphereRadius,
          colors[i],
          shaderList[i]
      ));
  }

  // Render loop
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

  fb.exportAsPNG(args.outputFileName);

  return 0;
}