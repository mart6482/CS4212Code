include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable (glfwExample
  glfwExample.cpp 
  GLSL.cpp GLSL.h
  GLCamera.h
)

add_executable (glfwTexture
  glfwTexture.cpp 
  GLSL.cpp GLSL.h
  GLCamera.h
)

add_executable (glfwAtlas
  glfwAtlas.cpp 
  GLSL.cpp GLSL.h
  GLCamera.h
)

add_executable(glfwExample2
  glfwExample2.cpp
  GLSL.cpp GLSL.h
  GLCamera.h
)

target_link_libraries (glfwExample PRIVATE GLEW::GLEW)
target_link_libraries (glfwExample PRIVATE glfw)

if(APPLE)
    target_link_libraries(glfwExample PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else()
    target_link_libraries(glfwExample PRIVATE OpenGL::GL)
endif()

target_link_libraries (glfwExample PRIVATE PNG::PNG)
target_link_libraries (glfwExample PRIVATE ZLIB::ZLIB)

target_link_libraries (glfwTexture PRIVATE GLEW::GLEW)
target_link_libraries (glfwTexture PRIVATE glfw)

if(APPLE)
    target_link_libraries(glfwTexture PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else()
    target_link_libraries(glfwTexture PRIVATE OpenGL::GL)
endif()

target_link_libraries (glfwTexture PRIVATE PNG::PNG)
target_link_libraries (glfwTexture PRIVATE ZLIB::ZLIB)

target_link_libraries (glfwAtlas PRIVATE GLEW::GLEW)
target_link_libraries (glfwAtlas PRIVATE glfw)

if(APPLE)
    target_link_libraries(glfwAtlas PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else()
    target_link_libraries(glfwAtlas PRIVATE OpenGL::GL)
endif()

target_link_libraries (glfwAtlas PRIVATE PNG::PNG)
target_link_libraries (glfwAtlas PRIVATE ZLIB::ZLIB)

target_link_libraries (glfwExample2 PRIVATE GLEW::GLEW)
target_link_libraries (glfwExample2 PRIVATE glfw)
if(APPLE)
    target_link_libraries(glfwExample2 PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else()
    target_link_libraries(glfwExample2 PRIVATE OpenGL::GL)
endif()

target_link_libraries (glfwExample2 PRIVATE PNG::PNG)
target_link_libraries (glfwExample2 PRIVATE ZLIB::ZLIB)