#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include "Framebuffer.h"
#include "PerspectiveCamera.h"
#include "ray.h"
#include "Shape.h"
#include "Sphere.h"
#include "NormalShader.h"
#include "Lambertian.h"
#include "Blinn-Phong.h"
#include "Light.h"

vec3 computeRayColor(const ray &r, const std::vector<std::shared_ptr<Shape>> &shapes, const std::vector<std::shared_ptr<PointLight>> &lights)
{
  float t_min = 0.001f;
  float t_max = std::numeric_limits<float>::max();

  hit_record closestHit;
  closestHit.t = t_max;
  bool hitAnything = false;

  // Check intersection with all shapes, find closest
  for (const auto &shape : shapes) {
    hit_record tempHit;
    if (shape->intersect(r, t_min, t_max, tempHit)) {
      if (tempHit.t < closestHit.t) {
        closestHit = tempHit;
        hitAnything = true;
        t_max = tempHit.t;
      }
    }
  }

  if (hitAnything) {
    auto shader = closestHit.shape->getShader();
    if (shader) {
      return shader->shade(closestHit, lights);
    } else {
      normalShader defaultShader;
      return defaultShader.shade(closestHit, lights);
    }
  }

  // Background color
  vec3 unit_direction = unit_vector(r.getDirection());
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
}

int main(int argc, char *argv[])
{
  int width = 800;
  int height = 800;
  Framebuffer fb(width, height);

  // Camera setup
  PerspectiveCamera cam(vec3(0, 0, 0), vec3(0, 0, -1), 1.0, 2.0, 2.0, width, height);

  // Create scene with three spheres
  std::vector<std::shared_ptr<Shape>> shapes;

  // Create shaders
  auto lambertianShader = std::make_shared<Lambertian>();
  auto blinnPhongShader = std::make_shared<BlinnPhong>();
  blinnPhongShader->setEyePosition(cam.getPosition());

  // Create lights, for now one point light only
  std::vector<std::shared_ptr<PointLight>> lights;
  lights.push_back(std::make_shared<PointLight>(vec3(2, 3, 1), vec3(1.0, 1.0, 1.0)));

  // Sphere 1: Normal Shader (left)
  shapes.push_back(std::make_shared<Sphere>(
    vec3(-1.2, 0, -2.5), 0.5f, vec3(0.8, 0.3, 0.3)));

  // Sphere 2: Lambertian Shader (center)
  shapes.push_back(std::make_shared<Sphere>(
    vec3(0, 0, -2.5), 0.5f, vec3(0.3, 0.8, 0.3), lambertianShader));

  // Sphere 3: Blinn-Phong Shader (right)
  shapes.push_back(std::make_shared<Sphere>(
    vec3(1.2, 0, -2.5), 0.5f, vec3(0.3, 0.3, 0.8), blinnPhongShader));

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      ray r = cam.generateRay(x, y);
      vec3 pixelColor = computeRayColor(r, shapes, lights);
      fb.setPixelColor(x, y, pixelColor);
    }
  }

  fb.exportAsPNG("three_shaders.png");

  return 0;
}