//#pragma once
#include <vector>
#include <string>
#include "vec3.h"

using color = vec3;

class Framebuffer{
    public:
        Framebuffer(); 
        Framebuffer(int w, int h);
        void clearToColor(color c);
        void setPixelColor(int i, int j, color c);
        void setPixelColor(int index, color c);
        void exportAsPNG(std::string filename);
        
    
        private:
        int width;
        int height;
        std::vector<color> fbStorage;

};