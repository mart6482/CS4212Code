#pragma once

#include "Camera.h"

class PerspectiveCamera : public Camera
{
public:
  PerspectiveCamera();
  PerspectiveCamera(int pixel_nx, int pixel_ny);

  
  PerspectiveCamera( vec3 origin, vec3 viewdir, float focallength, float imageplaneWidth, float imageplaneHeight, int nx, int ny);

  ray generateRay( int i, int j ) override;
  

private:
  float l, r, b, t;
};