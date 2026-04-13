How to compile and run this project:

1. cd into .\buildVCPkg\


2. run cmake --build .

3. 
    Running .\src\Debug\fbMain.exe will execute the program.

    Args:
    -w (int): changes the width of the image 
    
    -h (int): changes the height of the image
    
    -r (int): changes the rays sampled per pixel
    
    -k (int): changes the recursion depth used in mirror calculations
    
    -o (string): changes the name of the output file


How to compile and run the OpenGL files:

1. cd into .\buildVCPkg\

2. run cmake --build .

3. run .\OpenGL\Debug\glfwExample.exe

4. If there is an error accessing shader files, copy the vertex and fragmentshaders from the OpenGL folder into .\BuildVCPkg\

Controls:
WASD - move camera
Mouse - rotate camera
N - swap to normal shader
B - swap to Blinn-Phong shader
L - swap to Lambertian shader

Silver Level Programming Skill Dev Assignment - Side-By-Side Comparison Analysis

Differences not due to the rendering method:
No mirror shader, so the middle sphere is just white
All of the spheres are Blinn-Phong shaded in the rasterizer, while the Raytracer has a variety of shading techniques on different spheres
Purple sphere in the rasterizer is a matte red sphere in the raytracer

Differences from the rendering method:
Blinn-phong highlights look similar, but not exactly the same
No shadows in the rasterizer render
Rasterizer render looks more obviously computer generated/fake (no shadows really contributes to this in my opinion)
Ground color looks a lot more flat and it is hard to tell exactly where the spheres are in relation to the ground