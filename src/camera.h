#pragma once
#include "ray.h"    

class Camera {
    public:
        Camera();
        Camera( int pixel_nx, int pixel_ny );
        Camera(vec3 position, vec3 viewDir, vec3 upDir, float focal_length, float image_plane_width, float image_plane_height, int pixel_nx, int pixel_ny);

        //virtual void generateRay(int i, int j, ray &r, int nx, int ny) = 0;
        virtual ray generateRay( int i, int j ) = 0;
        virtual ray generateRay(float i, float j) = 0;

        virtual ~Camera() {};
        vec3 getPosition() const { return pos; }
        

        

    protected:
        vec3 pos;
        vec3 U, V, W;
        float focalLength;
        float imagePlaneWidth;
        float imagePlaneHeight;
        int nx, ny;

};
        
