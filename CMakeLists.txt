cmake_minimum_required(VERSION 3.6)
project(SlotMachine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread -pedantic")

set(LIB_GLEW_DIRECTORY "lib/glew")
set(LIB_GLFW_DIRECTORY "lib/glfw/lib-mingw-w64")
set(LIB_SOIL_DIRECTORY "lib/soil/lib")
set(LIB_GLM_DIRECTORY "lib/glm")
set(LIB_FREETYPE_DIRECTORY "lib/freetype/lib")

include_directories(${LIB_GLEW_DIRECTORY}/include)
include_directories(${LIB_GLFW_DIRECTORY}/../include)
include_directories(${LIB_SOIL_DIRECTORY}/../src)
include_directories(${LIB_GLM_DIRECTORY})
include_directories(${LIB_FREETYPE_DIRECTORY}/../include)
include_directories(${LIB_FREETYPE_DIRECTORY}/../include/freetype2)

link_directories(${LIB_GLFW_DIRECTORY})
link_directories(${LIB_SOIL_DIRECTORY})
link_directories(${LIB_FREETYPE_DIRECTORY})

add_subdirectory(${LIB_GLEW_DIRECTORY})

set(SOURCE_FILES src/main.cpp
                 src/SlotMachineEngine.cpp
                 src/GLFWWrapper.cpp
                 src/Shader.cpp
                 src/ResourceManager.cpp
                 src/Texture.cpp
                 src/SpriteRenderer.cpp
                 src/TimeManager.cpp
                 src/Scene.cpp
                 src/SceneObject.cpp
                 src/TextRenderer.cpp
                 src/RenderToTexture.cpp)

add_executable(SlotMachine ${SOURCE_FILES})

target_link_libraries(SlotMachine SOIL.a
                                  freetype
                                  opengl32
                                  glew
                                  glfw3)