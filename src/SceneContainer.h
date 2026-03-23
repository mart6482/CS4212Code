#pragma once

#include <memory>
#include <vector>
#include <string>
#include "camera.h"
#include "shader.h"
#include "shape.h"
#include "Light.h"


/*class Light {
public:
  std::string type;
};

class Shape {
public:
  std::string type;
};

class Camera {
public:
  std::string type;
};

class shader {
public:
  std::string type;
  std::string name;
};*/

//placeholder for now
class Texture {
public:
  std::string type;
};


class SceneContainer {
  friend class SceneLoader; // this will allow the scene loader to
                            // manipulate the Scene

private:
  std::vector<std::shared_ptr<PointLight>> lights;
  std::vector<std::shared_ptr<Shape>> shapes;
  std::vector<std::shared_ptr<Camera>> cameras;
  std::vector<std::shared_ptr<shader>> shaders;
  std::vector<std::shared_ptr<Texture>> textures;

public:
  SceneContainer() = default;
};
