#include "MirrorShader.h"
#include "RayTracer.h"
#include "ray.h"
#include "vec3.h"

vec3 MirrorShader::shade(const hit_record& hit,
  const ray &r,
  const std::vector<std::shared_ptr<PointLight>> &lights,
  const std::vector<std::shared_ptr<Shape>> &shapes,
  int depth)
{

    if (depth <= 0) {
        return vec3(0, 0, 0); // Base case: no more reflections
    }
  vec3 d = unit_vector(r.getDirection());
  vec3 n = unit_vector(hit.normal);
  vec3 reflected = d - 2.0 * dot(d, n) * n;

  const double epsilon = 0.001;
  ray reflectedRay(hit.p + n * epsilon, reflected);

  return computeRayColor(reflectedRay, shapes, lights, depth - 1);
}