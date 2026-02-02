#include <iostream>

#include "Framebuffer.h"

int main(int argc, char* argv[])
{
  Framebuffer fb1;

  color c(1.0, 0.0, 0.0);
  fb1.clearToColor(c);
  
  fb1.exportAsPNG("ShouldBeRed.png");
}