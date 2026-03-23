#pragma once

#include "ISceneLoader.h"
#include "SceneContainer.h"
#include "Shader.h"
#include "Lambertian.h"
#include "Blinn-Phong.h"
#include "MirrorShader.h"
#include "DiffuseShader.h"
#include "shape.h"
#include "sphere.h"
#include "Triangle.h"
#include "Camera.h"
#include "PerspectiveCamera.h"
#include "Light.h"
#include <iostream>
#include <unordered_map>

class SceneLoader : public ISceneLoader {
private:
  SceneContainer &m_targetScene; // Reference to the external scene
  std::unordered_map<std::string, std::shared_ptr<shader>> shaderLookup;

public:
  // The caller provides the scene to be filled
  SceneLoader(SceneContainer &sceneToPopulate)
      : m_targetScene(sceneToPopulate), numShaders(0), numTextures(0) {}

  void reserveCameras(size_t count) override {
    // makes sure the vector has enough space
    m_targetScene.cameras.reserve(count);
  }
  void reserveLights(size_t count) override {
    m_targetScene.lights.reserve(count);
  }
  void reserveShapes(size_t count) override {
    m_targetScene.shapes.reserve(count);
  }
  void reserveShaders(size_t count) override { numShaders = count; }
  void reserveTextures(size_t count) override { numTextures = count; }

  void setSceneParams(const SceneParams &sparams) override {
    std::cout << "Setting scene params." << std::endl;
  }

  void addCamera(const std::string &name, const std::string &type,
                 const ISceneLoader::vec &pos, const ISceneLoader::vec &viewDir,
                 float focalLength, float imagePlaneWidth) override {

    std::cout << "Creating camera: " << name << ", type:" << type << std::endl;

    if(type == "perspective"){
      auto cam = std::make_shared<PerspectiveCamera>(
          vec3(pos.x, pos.y, pos.z), vec3(viewDir.x, viewDir.y, viewDir.z),
          focalLength, imagePlaneWidth, imagePlaneWidth, 800, 600
        );

      m_targetScene.cameras.push_back(cam);
    }
  }

  void addPointLight(const ISceneLoader::vec &pos,
                     const ISceneLoader::vec &intensity) override {
    std::cout << "Creating point light." << std::endl;
    auto light = std::make_shared<PointLight>(
        vec3(pos.x, pos.y, pos.z), vec3(intensity.x, intensity.y, intensity.z)
    );
    m_targetScene.lights.push_back(light);
  }
  void addAreaLight(const ISceneLoader::vec &pos,
                    const ISceneLoader::vec &color,
                    const ISceneLoader::vec &normal, float width,
                    float length) override {
    std::cout << "Creating area light." << std::endl;
  }
  void addShader(const ISceneLoader::ShaderDesc &shaderDesc) override {
    std::cout << "Creating shader: type=" << shaderDesc.type << std::endl;
    std::shared_ptr<shader> newShader;
    if(shaderDesc.type == "Lambertian"){
      newShader = std::make_shared<Lambertian>();
    }
    else if(shaderDesc.type == "Blinn-Phong"){
      newShader = std::make_shared<BlinnPhong>(shaderDesc.diffuse.data, shaderDesc.specular.data, shaderDesc.phongExp);
    }
    else if(shaderDesc.type == "Mirror"){
      newShader = std::make_shared<MirrorShader>(shaderDesc.mirrorCoef);
    }
    else if(shaderDesc.type == "Diffuse"){
      newShader = std::make_shared<DiffuseShader>(
        vec3(shaderDesc.diffuse.data.x, shaderDesc.diffuse.data.y, shaderDesc.diffuse.data.z)
      );
    }else {
      std::cout << "Unknown shader type: " << shaderDesc.type << std::endl;
      return;
    }
    shaderLookup[shaderDesc.name] = newShader;
    m_targetScene.shaders.push_back(newShader);
  }
  void addShape(const ISceneLoader::ShapeDesc &shapeDesc) override {
    std::cout << "Creating shape: type=" << shapeDesc.type << std::endl;
    std::shared_ptr<Shape> newShape;
    if (shapeDesc.type == "sphere") {

      newShape = std::make_shared<Sphere>(
          vec3(shapeDesc.center.x, shapeDesc.center.y, shapeDesc.center.z),
          shapeDesc.radius, 
          vec3(1.0f, 1.0f, 1.0f), // default color
          shaderLookup[shapeDesc.shaderNameReference]);

    } else if (shapeDesc.type == "triangle") {

      newShape = std::make_shared<Triangle>(
          vec3(shapeDesc.v0.x, shapeDesc.v0.y, shapeDesc.v0.z),
          vec3(shapeDesc.v1.x, shapeDesc.v1.y, shapeDesc.v1.z),
          vec3(shapeDesc.v2.x, shapeDesc.v2.y, shapeDesc.v2.z),
          vec3(1.0f, 1.0f, 1.0f), // default color
          shaderLookup[shapeDesc.shaderNameReference]);

    } else {
      std::cout << "Unknown shape type: " << shapeDesc.type << std::endl;
      return;
    }
    m_targetScene.shapes.push_back(newShape);
  }
  void addTexture(const std::string &type, const std::string &name,
                  const std::string &sourceFile) override {
    std::cout << "Creating texture: type=" << type << ", name=" << name
              << ", sourceFile=" << sourceFile << std::endl;
  }

public:
  int numShaders;
  int numTextures;
};
