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
    
}

void Framebuffer::setPixelColor(int i, int j, color c) {
    if (i < 0 || i >= width || j < 0 || j >= height) return;
    fbStorage[j * width + i] = c;
}

void Framebuffer::setPixelColor(int index, color c) {
    if (index < 0 || index >= static_cast<int>(fbStorage.size())) return;
    fbStorage[index] = c;
}

void Framebuffer::clearToGradient( color c0, color c1 )
{
  for (auto x=0; x<width; x++) {
    for (auto y=0; y<height; y++) {
      
      float t = y / (float)height;
  
      // need to loop over and lerp here...
      color c2 = c0 * (1-t) + c1 * t;
  
      int idx = y * width + x;
      fbStorage[idx] = c2;
    }
  }
}