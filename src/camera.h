#include "ray.h"    

class Camera {
    public:
        Camera() : pos(0,0,0), u(1,0,0), v(0,1,0), w(0,0,1), focalLength(1.0f), imageplaneWidth(0.25), 
        imageplaneHeight(0.25), nx(100), ny(100){}
        virtual void generateRay(int i, int j, ray &r, int nx, int ny) = 0;

        virtual ~Camera() {};
        

        //fix/implement these later
        //virtual rat generateRay(int i, int j) = 0;
        //virtual void generate(float i, float j, ray &r) = 0;
        //virtual void generate(float i, float j) = 0;

    protected:
        point3 pos;
        vec3 u, v, w;
        float focalLength;
        float imageplaneWidth;
        float imageplaneHeight;
        int nx, ny;
        
};