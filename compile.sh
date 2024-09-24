#!/bin/bash

glslc -O --target-env=vulkan1.3 shaders/InGameShader.vert -o shaders/InGameShaderVert.spv
glslc -O --target-env=vulkan1.3 shaders/InGameShader.frag -o shaders/InGameShaderFrag.spv
glslc -O --target-env=vulkan1.3 shaders/UIShader.vert -o shaders/UIShaderVert.spv
glslc -O --target-env=vulkan1.3 shaders/UIShader.frag -o shaders/UIShaderFrag.spv
glslc -O --target-env=vulkan1.3 shaders/AberationShader.vert -o shaders/AberationShaderVert.spv
glslc -O --target-env=vulkan1.3 shaders/AberationShader.frag -o shaders/AberationShaderFrag.spv
glslc -O --target-env=vulkan1.3 shaders/BackgroundShader.vert -o shaders/BackgroundShaderVert.spv
glslc -O --target-env=vulkan1.3 shaders/BackgroundShader.frag -o shaders/BackgroundShaderFrag.spv
glslc -O --target-env=vulkan1.3 shaders/LightBatchShader.vert -o shaders/LightBatchShaderVert.spv
glslc -O --target-env=vulkan1.3 shaders/LightBatchShader.frag -o shaders/LightBatchShaderFrag.spv

# Besoin des bibliotheques: freetype2, glfw3, vulkan, glm
# Surtout bien configurer le path de freetype2 sur linux

# Utilisation d'x86_64v3: AVX2 dispo sur Intel (haswell) 4000 et AMD (Excavatore) 15h gen 4

clang++ -D NDEBUG -o VariDungeon.out src/Main.cpp\
    -I Lib -I src -I Zerengine\
    -I /usr/include/freetype2\
    -O0 -pipe -std=c++2c\
    -fno-exceptions\
    -lvulkan\
    -lfreetype\
    -lglfw
    # -static-libgcc\
    # -static-libstdc++\
    # -m64 -march=x86-64-v3\

#-fsanitize=address -fsanitize-address-use-after-scope -fsanitize=leak -fsanitize=undefined\
#-Wl,-Bdynamic -lvulkan\
#-Wall\
#-s
