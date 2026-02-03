#pragma once
#include "ray.h"    

class Camera {
    public:
        Camera();
        Camera( int pixel_nx, int pixel_ny );

        //virtual void generateRay(int i, int j, ray &r, int nx, int ny) = 0;
        virtual ray generateRay( int i, int j ) = 0;

        virtual ~Camera() {};
        

        //fix/implement these later
        //virtual ray generateRay(int i, int j) = 0;
        //virtual void generate(float i, float j, ray &r) = 0;
        //virtual void generate(float i, float j) = 0;

    protected:
        vec3 pos;
        vec3 U, V, W;
        float focalLength;
        float imagePlaneWidth;
        float imagePlaneHeight;
        int nx, ny;

};
        
