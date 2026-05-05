#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "GLCamera.h"
#include "png++/png.hpp"


#include "GLSL.h"

int CheckGLErrors(const char *s)
{
    int errCount = 0;
    return errCount;
}

void addTriangle(const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2, std::vector<float> &vbo)
{
    auto push = [&](const glm::vec3 &p, const glm::vec2 &uv)
    {
        glm::vec3 n = glm::normalize(glm::cross(v1 - v0, v2 - v0));

        // position
        vbo.push_back(p.x);
        vbo.push_back(p.y);
        vbo.push_back(p.z);

        // normal
        vbo.push_back(n.x);
        vbo.push_back(n.y);
        vbo.push_back(n.z);

        //uv
        vbo.push_back(uv.x);
        vbo.push_back(uv.y);
    };

    push(v0, glm::vec2(0.0f, 0.0f));
    push(v1, glm::vec2(1.0f, 0.0f));
    push(v2, glm::vec2(0.5f, 1.0f));
}

void addTriangleSphere(const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2, std::vector<float> &vbo)
{
    auto push = [&](const glm::vec3 &p, const glm::vec2 &uv)
    {
        glm::vec3 n = glm::normalize(p); // sphere normal

        // position
        vbo.push_back(p.x);
        vbo.push_back(p.y);
        vbo.push_back(p.z);

        // normal
        vbo.push_back(n.x);
        vbo.push_back(n.y);
        vbo.push_back(n.z);

        //uv
        vbo.push_back(uv.x);
        vbo.push_back(uv.y);
    };

    push(v0, glm::vec2(0.0f, 0.0f));
    push(v1, glm::vec2(1.0f, 0.0f));
    push(v2, glm::vec2(0.5f, 1.0f));
}

void addTexturedTriangle(const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec2 &uv0, const glm::vec2 &uv1, const glm::vec2 &uv2, std::vector<float> &vbo)
{
    glm::vec3 n = glm::normalize(glm::cross(v1 - v0, v2 - v0));
    auto push = [&](const glm::vec3 &p, const glm::vec2 &uv)
    {
        
        
        // position
        vbo.push_back(p.x);
        vbo.push_back(p.y);
        vbo.push_back(p.z);

        // normal
        vbo.push_back(n.x);
        vbo.push_back(n.y);
        vbo.push_back(n.z);

        // UV
        vbo.push_back(uv.x);
        vbo.push_back(uv.y);
    };

    push(v0, uv0);
    push(v1, uv1);
    push(v2, uv2);
}

void subdivide(const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2, int depth, std::vector<float> &vbo)
{
    if (depth == 0) {
        addTriangleSphere
    (v0, v1, v2, vbo);
        return;
    }

    // Midpoints
    glm::vec3 v0v1 = glm::normalize((v0 + v1) * 0.5f);
    glm::vec3 v1v2 = glm::normalize((v1 + v2) * 0.5f);
    glm::vec3 v2v0 = glm::normalize((v2 + v0) * 0.5f);

    // Recurse
    subdivide(v0,   v0v1, v2v0, depth - 1, vbo);
    subdivide(v0v1, v1,   v1v2, depth - 1, vbo);
    subdivide(v2v0, v1v2, v2,   depth - 1, vbo);
    subdivide(v0v1, v1v2, v2v0, depth - 1, vbo);
}

std::vector<float> buildIcosahedron(int depth){
    std::vector<float> vbo;
    float t = (1.0f + sqrt(5.0f)) / 2.0f;
    std::vector<glm::vec3> verts = {
        {-1,  t,  0}, { 1,  t,  0}, {-1, -t,  0}, { 1, -t,  0},
        { 0, -1,  t}, { 0,  1,  t}, { 0, -1, -t}, { 0,  1, -t},
        { t,  0, -1}, { t,  0,  1}, {-t,  0, -1}, {-t,  0,  1}
    };
    // Normalize
    for (auto &v : verts){
        v = glm::normalize(v);
    }
    // 20 triangles
    std::vector<unsigned int> indices = {
        0,11,5,  0,5,1,  0,1,7,  0,7,10, 0,10,11,
        1,5,9,   5,11,4, 11,10,2,10,7,6,  7,1,8,
        3,9,4,   3,4,2,  3,2,6,  3,6,8,   3,8,9,
        4,9,5,   2,4,11, 6,2,10, 8,6,7,   9,8,1
    };
    
    for (int i = 0; i < indices.size(); i += 3){
        glm::vec3 v0 = verts[indices[i]];
        glm::vec3 v1 = verts[indices[i+1]];
        glm::vec3 v2 = verts[indices[i+2]];

        subdivide(v0, v1, v2, depth, vbo);
    }

    return vbo;
}
GLCamera* camPTR = nullptr;
double lastX = 500, lastY = 500;
bool firstMouse = true;
float sensitivity = 0.1f;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (!camPTR) return;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camPTR->yaw   += xoffset;
    camPTR->pitch += yoffset;

    if (camPTR->pitch > 89.0f) camPTR->pitch = 89.0f;
    if (camPTR->pitch < -89.0f) camPTR->pitch = -89.0f;

    camPTR->updateFromAngles();
}


int main(void)
{
    /* Initialize the library */
    if (!glfwInit()) {
        exit (-1);
    }
    // throw std::runtime_error("Error! initialization of glfw failed!");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    int winWidth = 1000;
    float aspectRatio = 1.0; // 16.0 / 9.0; // winWidth / (float)winHeight;
    int winHeight = winWidth / aspectRatio;
    
    
    GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "GLFW Example", NULL, NULL);
    if (!window) {
        std::cerr << "GLFW did not create a window!" << std::endl;
        
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum err=glewInit();
    if(err != GLEW_OK) {
        std::cerr <<"GLEW Error! glewInit failed, exiting."<< std::endl;
        exit(EXIT_FAILURE);
    }

    const GLubyte* renderer = glGetString (GL_RENDERER);
    const GLubyte* version = glGetString (GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported: " << version << std::endl;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.0, 0.2, 0.2, 0.2);

    int fb_width, fb_height;
    glfwGetFramebufferSize(window, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);

    // Need to set a projection matrix that fits the aspect ratio set
    // by the window frame.
    //
    // The ortho parameters, in order: left, right, bottom, top, zNear, zFar
    float halfWidth = 15.0 / 2.0;
    float halfHeight = halfWidth / aspectRatio;
    float left = -halfWidth;
    float right = halfWidth;

    float bottom = -halfHeight;
    float top = halfHeight;

    float near = 5.0f;
    float far = -5.0f;

    glm::mat4 PerspectiveMatrix = glm::perspective(3.14159f/4.0f, 1.0f, 0.1f, 100.0f);
    //glm::mat4 M_ortho = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, near, far);
    //glm::mat4 projectionMatrix = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, -10.0f, 10.0f);

    GLint major_version;
    glGetIntegerv(GL_MAJOR_VERSION, &major_version);
    std::cout << "GL_MAJOR_VERSION: " << major_version << std::endl;

    //initialize all my data and get it on the GPU
    //load the scene file
    //get shapes into the scene

    //Load a Triangle
    // create a Vertex Array Buffer to hold our triangle data                                               
    
    GLuint m_triangleVBO[1], m_VAO;
    sivelab::GLSLObject shader;

    glGenBuffers(1, m_triangleVBO); 
    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO[0]);

    std::vector<float> host_VertexBuffer = buildIcosahedron(4);
    int vertexCount = host_VertexBuffer.size() / 8;
    int numBytes = host_VertexBuffer.size() * sizeof(float);
    glBufferData(GL_ARRAY_BUFFER , numBytes , host_VertexBuffer.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO[0]);

    // once copied, we no longer need the data on the host                                                  
    host_VertexBuffer.clear();


    std::string textFilename = "Skybox.png";
    std::cout << "Loading texture from file: " << textFilename << std::endl;
    png::image<png::rgb_pixel> texPNGImage;
    texPNGImage.read(textFilename);

    int pngWidth = texPNGImage.get_width();
    int pngHeight = texPNGImage.get_height();

    std::vector<float> texData(pngWidth * pngHeight * 3);

    size_t idx = 0;
    for (size_t row = 0; row < pngHeight; ++row) {
        for (size_t col = 0; col < pngWidth; ++col) {
            png::rgb_pixel pixel = texPNGImage[pngHeight - row - 1][col];
            texData[idx++] = pixel.red / 255.0f;
            texData[idx++] = pixel.green / 255.0f;
            texData[idx++] = pixel.blue / 255.0f;
        }
    }

    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 
                pngWidth, pngHeight, 
                0, GL_RGB, GL_FLOAT, texData.data());
    glBindTexture(GL_TEXTURE_2D, 0);


    std::vector<glm::vec3> spherePositions;

    // central sphere position
    glm::vec3 center(0.0f, 1.0f, -2.0f);

    // ring parameters (same as raytracer)
    float radiusFromCenter = 2.0f;
    int count = 8;
    for (int i = 0; i < count; i++) {
        float angle = i * (2.0f * 3.14159265358979323846f / count);

        float x = center.x + radiusFromCenter * cos(angle);
        float z = center.z + radiusFromCenter * sin(angle);

        spherePositions.push_back(glm::vec3(x, 1.0f, z));
    }

    std::vector<glm::vec3> rainbow = {
        {1.0f, 0.0f, 0.0f},
        {1.0f, 0.5f, 0.0f},
        {1.0f, 1.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 1.0f, 0.5f},
        {0.0f, 1.0f, 1.0f},
        {0.0f, 0.0f, 1.0f},
        {0.5f, 0.0f, 1.0f}
    };


    //Texture Square
    std::vector<float> triangle;
    glm::vec3 topLeft = glm::vec3(-1, 1, 1);
    glm::vec3 topRight = glm::vec3(1, 1, 1);
    glm::vec3 bottomLeft = glm::vec3(-1, -1, 1);
    glm::vec3 bottomRight = glm::vec3(1, -1, 1);
    addTexturedTriangle(topLeft, bottomLeft, bottomRight, glm::vec2(0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), triangle);
    addTexturedTriangle(topLeft, bottomRight, topRight, glm::vec2(0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), triangle);
    GLuint triangleVBO, triangleVAO;
    glGenBuffers(1, &triangleVBO);
    glGenVertexArrays(1, &triangleVAO);
    glBindVertexArray(triangleVAO);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
    glBufferData(GL_ARRAY_BUFFER, triangle.size() * sizeof(float), triangle.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindVertexArray(0);

    //Room Cube
    std::vector<float> cube;
    float roomSize = 50.0f;
    glm::vec3 c0(-roomSize, -roomSize, -roomSize);
    glm::vec3 c1(roomSize, -roomSize, -roomSize);
    glm::vec3 c2(roomSize, roomSize, -roomSize);
    glm::vec3 c3(-roomSize, roomSize, -roomSize);
    glm::vec3 c4(-roomSize, -roomSize, roomSize);
    glm::vec3 c5(roomSize, -roomSize, roomSize);
    glm::vec3 c6(roomSize, roomSize, roomSize);
    glm::vec3 c7(-roomSize, roomSize, roomSize);
    //back face
    addTexturedTriangle(c0, c1, c2,
        {0.75f, 0.3333f}, {1.00f, 0.3333f}, {1.00f, 0.6666f}, cube);

    addTexturedTriangle(c0, c2, c3,
        {0.75f, 0.3333f}, {1.00f, 0.6666f}, {0.75f, 0.6666f}, cube);
        
    //front face
    addTexturedTriangle(c5, c4, c7,
        {0.25f, 0.3333f}, {0.50f, 0.3333f}, {0.50f, 0.6666f}, cube);

    addTexturedTriangle(c5, c7, c6,
        {0.25f, 0.3333f}, {0.50f, 0.6666f}, {0.25f, 0.6666f}, cube);

    //left face
    addTexturedTriangle(c4, c0, c3,
        {0.00f, 0.3333f}, {0.25f, 0.3333f}, {0.25f, 0.6666f}, cube);

    addTexturedTriangle(c4, c3, c7,
        {0.00f, 0.3333f}, {0.25f, 0.6666f}, {0.00f, 0.6666f}, cube);
    
    //right face
    addTexturedTriangle(c1, c5, c6,
        {0.50f, 0.3333f}, {0.75f, 0.3333f}, {0.75f, 0.6666f}, cube);

    addTexturedTriangle(c1, c6, c2,
        {0.50f, 0.3333f}, {0.75f, 0.6666f}, {0.50f, 0.6666f}, cube);
        
    //top face
    addTexturedTriangle(c3, c2, c6,
        {0.25f, 0.6666f}, {0.50f, 0.6666f}, {0.50f, 1.000f}, cube);

    addTexturedTriangle(c3, c6, c7,
        {0.25f, 0.6666f}, {0.50f, 1.000f}, {0.25f, 1.000f}, cube);
    
    //bottom face
    addTexturedTriangle(c4, c5, c1,
        {0.25f, 0.0000f}, {0.50f, 0.0000f}, {0.50f, 0.3333f}, cube);

    addTexturedTriangle(c4, c1, c0,
        {0.25f, 0.0000f}, {0.50f, 0.3333f}, {0.25f, 0.3333f}, cube);

    GLuint cubeVBO, cubeVAO;
    glGenBuffers(1, &cubeVBO);
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, cube.size() * sizeof(float), cube.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindVertexArray(0);

    //floor
    std::vector<float> floor;
    float floorSize = 100.0f;
    float floorY = -14.0f;
    glm::vec3 v0(-floorSize, floorY, -floorSize);
    glm::vec3 v1(floorSize, floorY, -floorSize);
    glm::vec3 v2(floorSize, floorY, floorSize);
    glm::vec3 v3(-floorSize, floorY, floorSize);
    addTriangle(v0, v1, v2, floor);
    addTriangle(v0, v2, v3, floor);

    GLuint floorVBO, floorVAO;
    glGenBuffers(1, &floorVBO);
    glGenVertexArrays(1, &floorVAO);
    glBindVertexArray(floorVAO);

    glBindBuffer(GL_ARRAY_BUFFER, floorVBO);
    glBufferData(GL_ARRAY_BUFFER, floor.size() * sizeof(float), floor.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindVertexArray(0);

    //VAO for the VBO
    // create a vertex array object that will map the attributes in                                         
    // our vertex buffer to different location attributes for our                                           
    // shaders                                                                                              
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    // VAO details here - we only have 1 attribute or location                                              
    // (Position of the vertex)                                                                             
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO[0]);
    glVertexAttribPointer (0, 3, GL_FLOAT , GL_FALSE , 8 * sizeof(float), (void*)0);
    
    glEnableVertexAttribArray (1);
    glVertexAttribPointer (1, 3, GL_FLOAT , GL_FALSE , 8 * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray (2);
    glVertexAttribPointer (2, 2, GL_FLOAT , GL_FALSE , 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindVertexArray(0);



    // Create a shader using my GLSLObject class                                                            
    sivelab::GLSLObject Shader;
    Shader.addShader( "vertexShader_Texture.glsl", sivelab::GLSLObject::VERTEX_SHADER );
    Shader.addShader( "fragmentShader_Texture.glsl", sivelab::GLSLObject::FRAGMENT_SHADER );
    Shader.createProgram();

    sivelab::GLSLObject normalShader;
    normalShader.addShader( "vertexShader_Texture.glsl", sivelab::GLSLObject::VERTEX_SHADER );
    normalShader.addShader( "fragmentShader_Normal.glsl", sivelab::GLSLObject::FRAGMENT_SHADER );
    normalShader.createProgram();

    sivelab::GLSLObject* currentShader = &Shader;
    //build uniform variables
    GLuint projMatrixID, viewMatrixID, modelMatrixID, normalMatrixID, lightPosID, diffuseComponentID, specularComponentID, shininessID, cameraPosID, shadingModeID, useFlatColorID, flatColorID, texUnitID, useTextureID;
    projMatrixID = Shader.createUniform( "projMatrix" );
    viewMatrixID = Shader.createUniform( "viewMatrix" );
    modelMatrixID = Shader.createUniform( "modelMatrix" );
    normalMatrixID = Shader.createUniform( "normalMatrix" );
    lightPosID = Shader.createUniform( "lightPosWorld" );
    diffuseComponentID = Shader.createUniform( "diffuseComponent" );
    specularComponentID = Shader.createUniform( "specularComponent" );
    shininessID = Shader.createUniform( "PhongExponent" );
    cameraPosID = Shader.createUniform( "cameraPos" );
    shadingModeID = Shader.createUniform( "shadingMode" );
    useFlatColorID = Shader.createUniform( "useFlatColor" );
    flatColorID = Shader.createUniform( "flatColor" );
    texUnitID = Shader.createUniform("textureSampler");
    useTextureID = Shader.createUniform("useTexture");

    

    glm::vec3 m_pos(0,1.5,3.5), m_viewDir(0,0,-1);
    glm::vec3 m_U(1,0,0), m_V(0,1,0), m_W(0,0,1);
    GLCamera cam(m_pos, m_viewDir, m_U, m_V, m_W);
    camPTR = &cam;
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    double timeDiff = 0.0, startFrameTime = 0.0, endFrameTime = 0.0;
    float rotationAngle = 0.0f;
    float rotationSpeed = 1.0f;
    int shadingMode = 1;
    glm::vec4 lights[2]{
        glm::vec4(3.0f, 3.0f, 4.0f, 1.0f),
        glm::vec4(-3.0f, 3.0f, 4.0f, 1.0f)
    };

    
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        endFrameTime = glfwGetTime();
        timeDiff = endFrameTime - startFrameTime;
        startFrameTime = glfwGetTime();

        // Clear the window's buffer (or clear the screen to our
        // background color)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 M_view = glm::lookAt(cam.getPosition(), cam.getPosition() + cam.getViewDirection(), glm::vec3(0,1,0));
        /* Render your objects here */
        currentShader->activate();
    
        
        //rotationAngle += rotationSpeed * timeDiff;
        glm::mat4 modelTransform = glm::mat4(1.0f);
        //modelTransform = glm::rotate(modelTransform, rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));

        //glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelTransform));
        glUniformMatrix4fv(projMatrixID, 1, GL_FALSE, glm::value_ptr(PerspectiveMatrix));
        glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, glm::value_ptr( M_view ));
        glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelTransform));
        glUniformMatrix4fv(normalMatrixID, 1, GL_FALSE, glm::value_ptr(normalMatrix));

        // Set the light position in world space
        /*glm::vec4 lightPosWorld(3.0f, 5.0f, 2.0f, 1.0f);
        glUniform4fv(lightPosID, 1, glm::value_ptr(lightPosWorld));*/

        glUniform4fv(lightPosID, 2, glm::value_ptr(lights[0]));

        // Set the diffuse color for the triangle
        glm::vec3 diffuseComponent(1.0f, 0.0f, 0.5f);
        glUniform3fv(diffuseComponentID, 1, glm::value_ptr(diffuseComponent));

        // Set the specular color for the triangle
        glm::vec3 specularComponent(1.0f, 1.0f, 1.0f);
        glUniform3fv(specularComponentID, 1, glm::value_ptr(specularComponent));

        // Set the shininess (Phong exponent) for the triangle
        float shininess = 256.0f;
        glUniform1f(shininessID, shininess);
        glUniform1i(shadingModeID, shadingMode); 

        glUniform1i(useFlatColorID, 0); // not using flat color
        
        // Set the camera position in world space
        glUniform3fv(cameraPosID, 1, glm::value_ptr(cam.getPosition()));
        
        
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texID);
        glUniform1i(texUnitID, 0);
        glUniform1i(useTextureID, 1);

        //triangle rendering
        /*glBindVertexArray(triangleVAO);
        glUniform3fv(diffuseComponentID, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
        glm::mat4 triangleModel = glm::mat4(1.0f);
        triangleModel = glm::translate(triangleModel, glm::vec3(0.0f, 2.0f, -2.0f));
        triangleModel = glm::scale(triangleModel, glm::vec3(4.0f, 4.0f, 4.0f));
        glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(triangleModel));
        glDrawArrays(GL_TRIANGLES, 0, triangle.size() / 8);
        glBindVertexArray(0);*/

        glUniform1i(useTextureID, 0); 

        //floor rendering
        /*glUniform1i(useFlatColorID, 1); // use flat color for floor
        glUniform3fv(flatColorID, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f))); // set flat color to gray
        glBindVertexArray(floorVAO);
        glm::mat4 floorModel = glm::mat4(1.0f);
        glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(floorModel));
        glDrawArrays(GL_TRIANGLES, 0, floor.size() / 8);
        glBindVertexArray(0);
        glUniform1i(useFlatColorID, 0);*/ // reset to not using flat color for spheres
        
        //room rendering
        glUniform1i(shininessID, 64.0f); 
        glUniform1i(useTextureID, 1);
        glm::vec3 roomColor(0.4f, 0.4f, 0.4f);
        glUniform3fv(diffuseComponentID, 1, glm::value_ptr(roomColor));
        glm::vec3 specularRoom(0.1f, 0.1f, 0.1f);
        glUniform3fv(specularComponentID, 1, glm::value_ptr(specularRoom));
        glBindVertexArray(cubeVAO);
        glm::mat4 roomModel = glm::mat4(1.0f);
        glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(roomModel));
        glDrawArrays(GL_TRIANGLES, 0, cube.size() / 8);
        glBindVertexArray(0);
        glUniform1i(shininessID, 256.0f); 

        glUniform1i(useTextureID, 0);
        

        //sphere rendering
        glBindVertexArray(m_VAO);
        //render middle sphere
        glUniform3fv(diffuseComponentID, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, center);
        model = glm::scale(model, glm::vec3(0.8f));
        glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);


        //render ring of spheres
        for(int i = 0; i<spherePositions.size(); i++){
            //set color
            glm::vec3 color = rainbow[i % rainbow.size()] * 0.7f; 
            glUniform3fv(diffuseComponentID, 1, glm::value_ptr(color));
            //set up values for sphere orbiting animation
            float angle = glfwGetTime() * 1.0f + i * (2.0f * 3.14159265358979323846f / spherePositions.size());
            float x = center.x + radiusFromCenter * cos(angle);
            float z = center.z + radiusFromCenter * sin(angle);
            //set up height for bouncing animation
            float height = 0.5f * sin(glfwGetTime() * 2.0f + angle - glfwGetTime());

            glm::vec3 animatedPos = glm::vec3(x, center.y + height, z);
            //transform the sphere and draw it
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, animatedPos);
            model = glm::scale(model, glm::vec3(0.5f));

            glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        }
        glBindVertexArray(0);

        currentShader->deactivate();

        // Swap the front and back buffers
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        float moveRatePerFrame = 0.005;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cam.setPosition(cam.getPosition() + -cam.getW() * moveRatePerFrame);
        }
        else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cam.setPosition(cam.getPosition() - cam.getU() * moveRatePerFrame);
        }
        else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cam.setPosition(cam.getPosition() + cam.getW() * moveRatePerFrame);
        }
        else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cam.setPosition(cam.getPosition() + cam.getU() * moveRatePerFrame);
        }
        /*else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            rotationSpeed += 0.01f;
        }
        else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            rotationSpeed -= 0.01f;
        }*/
        else if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
            shadingMode = 2;
        }else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
            shadingMode = 0; 
        }else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
            shadingMode = 1;
        }
        
        if (glfwGetKey( window, GLFW_KEY_T ) == GLFW_PRESS) {
            std::cout << "fps: " << 1.0/timeDiff << std::endl;
        }
        if (glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, 1);
        }
    }
  
    glfwTerminate();
    return 0;
}
