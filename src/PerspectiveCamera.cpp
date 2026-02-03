#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera()
  : Camera()
{
  l = -imagePlaneWidth/2.0;
  r = imagePlaneWidth/2.0;

  b = -imagePlaneHeight/2.0;
  t = imagePlaneHeight/2.0;
}

PerspectiveCamera::PerspectiveCamera(int pixel_nx, int pixel_ny)
  : Camera(pixel_nx, pixel_ny)
{
  l = -imagePlaneWidth/2.0;
  r = imagePlaneWidth/2.0;

  b = -imagePlaneHeight/2.0;
  t = imagePlaneHeight/2.0;
}

PerspectiveCamera::PerspectiveCamera( vec3 origin, vec3 viewdir, float focallength, float imageplaneWidth, float imageplaneHeight, int nx, int ny)
  : Camera(nx, ny)
{
  pos = origin;
  W = -viewdir;
 
  U = cross(vec3(0,1,0), W);
  if (U.length() == 0) {
    U = cross(vec3(1,0,0), W);
  }
 
  V = cross(W,U);

  l = -imagePlaneWidth/2.0;
  r = imagePlaneWidth/2.0;
  b = -imagePlaneHeight/2.0;
  t = imagePlaneHeight/2.0;
}

ray PerspectiveCamera::generateRay( int i, int j )
{
    float u, v;
    u = l + (r-l) * (i+0.5)/(float)nx;
    v = b + (t-b) * (j+0.5)/(float)ny;
    
    ray tempRay( pos, -W*focalLength + U*u + V*v );
    return tempRay;
  }
