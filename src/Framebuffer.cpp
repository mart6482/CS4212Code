#include "Framebuffer.h"
#include "vec3.h"
#include "color.h"

Framebuffer::Framebuffer():width(100), height(100), fbStorage(width*height){}

Framebuffer::Framebuffer(int x, int y): width(x), height(y), fbStorage(width*height){}

void Framebuffer::clearToColor(color c){
    for(auto idx=0u; idx<fbStorage.size(); ++idx){
        fbStorage[idx] = c;
    }
}

void Framebuffer::exportAsPNG(std::string filename){
    //write this later
}

void Framebuffer::setPixelColor(int i, int j, color c){
    //placeholder
}

