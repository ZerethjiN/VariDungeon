@echo off

glslc -O --target-env=vulkan1.2 shaders/InGameShader.vert -o shaders/InGameShaderVert.spv
glslc -O --target-env=vulkan1.2 shaders/InGameShader.frag -o shaders/InGameShaderFrag.spv
glslc -O --target-env=vulkan1.2 shaders/UIShader.vert -o shaders/UIShaderVert.spv
glslc -O --target-env=vulkan1.2 shaders/UIShader.frag -o shaders/UIShaderFrag.spv
glslc -O --target-env=vulkan1.2 shaders/AberationShader.vert -o shaders/AberationShaderVert.spv
glslc -O --target-env=vulkan1.2 shaders/AberationShader.frag -o shaders/AberationShaderFrag.spv
glslc -O --target-env=vulkan1.2 shaders/BackgroundShader.vert -o shaders/BackgroundShaderVert.spv
glslc -O --target-env=vulkan1.2 shaders/BackgroundShader.frag -o shaders/BackgroundShaderFrag.spv
glslc -O --target-env=vulkan1.2 shaders/LightBatchShader.vert -o shaders/LightBatchShaderVert.spv
glslc -O --target-env=vulkan1.2 shaders/LightBatchShader.frag -o shaders/LightBatchShaderFrag.spv

clang++ -D NDEBUG -o VariDungeon.exe src/Main.cpp^
    Lib/freetype-2.13.2/objs/freetype.a^
    -I C:\VulkanSDK\1.3.296.0\Include -I Lib/glfw-3.4.bin.WIN64/include -I Lib/freetype-2.13.2/include -I Lib/freetype-2.13.2/include/freetype -I Lib/glm-1.0.1 -I Lib^
    -I src -I Zerengine^
    -fno-exceptions^
    -O3 -s -pipe -std=c++2c^
    -m64 -march=x86-64-v3^
    -L Lib/glfw-3.4.bin.WIN64/lib-static-ucrt -L C:\VulkanSDK\1.3.296.0\Lib^
    -lglfw3 -lvulkan-1

:: -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wunused -Woverloaded-virtual -Wformat=2 -Wnull-dereference -Wpedantic^

::-llegacy_stdio_definitions

::-llibcpmt -llibvcruntime -llibucrt
::-march=native
::-Wdouble-promotion -Wconversion -Wsign-conversion
::-Wduplicated-cond -Wduplicated-branches -Wlogical -op -Wuseless-cast -Wold-style-cast -Wcast-align