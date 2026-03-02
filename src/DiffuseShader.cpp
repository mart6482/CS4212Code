#include "DiffuseShader.h"
#include "RayTracer.h"
#include "HitStructure.h"
#include "ray.h"
#include "vec3.h"
#include "Shape.h"
#include "Random.h"
#include <memory>

vec3 DiffuseShader::random_in_unit_sphere() const
{
  static sivelab::Random rand;
  vec3 randomDir;
  while (true) {
    randomDir = vec3(
      2.0 * rand.uniform() - 1.0,
      2.0 * rand.uniform() - 1.0,
      2.0 * rand.uniform() - 1.0
    );
    if (randomDir.length() < 1.0) break;
  }
  return unit_vector(randomDir);
}

vec3 DiffuseShader::shade(const hit_record& hit,
  const ray &r,
  const std::vector<std::shared_ptr<PointLight>> &lights,
  const std::vector<std::shared_ptr<Shape>> &shapes,
  int depth)
{
  if (depth <= 0) {
    return vec3(0, 0, 0);
  }

  vec3 randomDir = random_in_unit_sphere();

  vec3 scatterDirection = hit.normal + randomDir;

  if (scatterDirection.length_squared() < 1e-8) {
    scatterDirection = hit.normal;
  }

  ray scatteredRay(hit.p, scatterDirection);

  vec3 scatteredColor = computeRayColor(scatteredRay, shapes, lights, depth - 1);

  return diffuseReflectanceColor * scatteredColor;
}

