#include "Camera.h"

Camera::Camera()
  : pos(0,0,0), U(1,0,0), V(0,1,0), W(0,0,1),
    focalLength(1.0), imagePlaneWidth(0.25), imagePlaneHeight(0.25),
    nx(100), ny(100)
{
}

Camera::Camera( int pixel_nx, int pixel_ny )
  : pos(0,0,0), U(1,0,0), V(0,1,0), W(0,0,1),
    focalLength(1.0), 
    nx(pixel_nx), ny(pixel_ny)
{
    imagePlaneWidth = 0.25;
    float aspectRatio = static_cast<float>(pixel_nx) / static_cast<float>(pixel_ny);
    imagePlaneHeight = imagePlaneWidth / aspectRatio;
}

Camera::Camera(vec3 position, vec3 viewDir, vec3 upDir, float focal_length, float image_plane_width, float image_plane_height, int pixel_nx, int pixel_ny)
: pos(position),
   focalLength(focal_length),
   imagePlaneWidth(image_plane_width),
   imagePlaneHeight(image_plane_height),
   nx(pixel_nx),
   ny(pixel_ny)
{
    W = -unit_vector(viewDir);
    
    vec3 t = upDir;

    // If the up direction is parallel to the view direction, we need to choose a different up vector to avoid a degenerate camera basis.
    if (std::abs(dot(unit_vector(t), W)) > 0.999f) {
        t = vec3(0, 0, 1); // Choose a different up vector
    }

    U = unit_vector(cross(t, W));
    V = cross(W, U);
}