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

4. If there is an error accessing shader files, copy vertexShader_passthrough.glsl and fragmentShader_passthrough.glsl into .\BuildVCPkg\