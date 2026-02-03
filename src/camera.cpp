#include "Camera.h"

Camera::Camera()
  : pos(0,0,0), U(1,0,0), V(0,1,0), W(0,0,1),
    focalLength(1.0), imagePlaneWidth(0.25), imagePlaneHeight(0.25),
    nx(100), ny(100)
{
}

Camera::Camera( int pixel_nx, int pixel_ny )
  : pos(0,0,0), U(1,0,0), V(0,1,0), W(0,0,1),
    focalLength(1.0), imagePlaneWidth(0.25), imagePlaneHeight(0.25),
    nx(pixel_nx), ny(pixel_ny)
{
}