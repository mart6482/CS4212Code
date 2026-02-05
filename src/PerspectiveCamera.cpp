#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera()
  : Camera()
{
  U = vec3(1,0,0);
  V = vec3(0,1,0);
  W = vec3(0,0,1);
  l = -imagePlaneWidth/2.0;
  r = imagePlaneWidth/2.0;

  b = -imagePlaneHeight/2.0;
  t = imagePlaneHeight/2.0;
  pos = vec3(0,0,0);
}

PerspectiveCamera::PerspectiveCamera(int pixel_nx, int pixel_ny)
  : Camera(pixel_nx, pixel_ny)
{
  l = -imagePlaneWidth/2.0;
  r = imagePlaneWidth/2.0;
  U = vec3(1,0,0);
  V = vec3(0,1,0);
  W = vec3(0,0,1);
  b = -imagePlaneHeight/2.0;
  t = imagePlaneHeight/2.0;
  pos = vec3(0,0,0);
}

PerspectiveCamera::PerspectiveCamera( vec3 origin, vec3 viewdir, float focallength, float imageplaneWidth, float imageplaneHeight, int nx, int ny)
  : Camera(nx, ny)
{
  pos = origin;
  W = -normalize(viewdir);
  focalLength = focallength;
  imagePlaneHeight = imageplaneHeight;
  imagePlaneWidth = imageplaneWidth;
 
  U = cross(vec3(0,1,0), W);
  if (U.length() == 0) {
    U = cross(vec3(1,0,0), W);
  }
  U = normalize(U);
  V = normalize(cross(W,U));
  l = -imagePlaneWidth/2.0f;
  r = imagePlaneWidth/2.0f;
  b = -imagePlaneHeight/2.0f;
  t = imagePlaneHeight/2.0f;
  
}

ray PerspectiveCamera::generateRay(int i, int j)
{
    float u = l + (r-l) * (i+0.5f) / nx;
    float v = b + (t-b) * (j+0.5f) / ny;

    vec3 dir = -W * focalLength + U * u + V * v;
    dir = normalize(dir);

    return ray(pos, dir);
}
