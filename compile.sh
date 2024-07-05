#!/bin/bash

glslc -O --target-env=vulkan1.3 shaders/InGameShader.vert -o shaders/InGameShaderVert.spv
glslc -O --target-env=vulkan1.3 shaders/InGameShader.frag -o shaders/InGameShaderFrag.spv
glslc -O --target-env=vulkan1.3 shaders/UIShader.vert -o shaders/UIShaderVert.spv
glslc -O --target-env=vulkan1.3 shaders/UIShader.frag -o shaders/UIShaderFrag.spv
glslc -O --target-env=vulkan1.3 shaders/TextUIShader.vert -o shaders/TextUIShaderVert.spv
glslc -O --target-env=vulkan1.3 shaders/TextUIShader.frag -o shaders/TextUIShaderFrag.spv
glslc -O --target-env=vulkan1.3 shaders/TextShader.vert -o shaders/TextShaderVert.spv
glslc -O --target-env=vulkan1.3 shaders/TextShader.frag -o shaders/TextShaderFrag.spv
glslc -O --target-env=vulkan1.3 shaders/AberationShader.vert -o shaders/AberationShaderVert.spv
glslc -O --target-env=vulkan1.3 shaders/AberationShader.frag -o shaders/AberationShaderFrag.spv

# Besoin des bibliotheques: freetype2, glfw3, vulkan, glm
# Surtout bien configurer le path de freetype2 sur linux

g++ -D NDEBUG -o Varidungeon.out src/Main.cpp\
    -I Lib\
    -I src -I Zerengine\
    -Oz -s -pipe -std=c++2c\
    -Wl,-Bdynamic -lvulkan\
    -Wl,-Bdynamic -lfreetype\
    -Wl,-Bdynamic -lglfw

#-Wl,-Bdynamic -lvulkan\
#-Wall\
#-s