@echo off

@REM glslc -O --target-env=vulkan1.3 shaders/InGameShader.vert -o shaders/InGameShaderVert.spv
@REM glslc -O --target-env=vulkan1.3 shaders/InGameShader.frag -o shaders/InGameShaderFrag.spv
@REM glslc -O --target-env=vulkan1.3 shaders/UIShader.vert -o shaders/UIShaderVert.spv
@REM glslc -O --target-env=vulkan1.3 shaders/UIShader.frag -o shaders/UIShaderFrag.spv
@REM glslc -O --target-env=vulkan1.3 shaders/TextUIShader.vert -o shaders/TextUIShaderVert.spv
@REM glslc -O --target-env=vulkan1.3 shaders/TextUIShader.frag -o shaders/TextUIShaderFrag.spv
@REM glslc -O --target-env=vulkan1.3 shaders/TextShader.vert -o shaders/TextShaderVert.spv
@REM glslc -O --target-env=vulkan1.3 shaders/TextShader.frag -o shaders/TextShaderFrag.spv
@REM glslc -O --target-env=vulkan1.3 shaders/AberationShader.vert -o shaders/AberationShaderVert.spv
@REM glslc -O --target-env=vulkan1.3 shaders/AberationShader.frag -o shaders/AberationShaderFrag.spv

clang++ -D DEBUG -o Varidungeon.exe src/Main.cpp^
    Lib/freetype-2.13.2/objs/freetype.a^
    -I C:\VulkanSDK\1.3.280.0\Include -I Lib/glfw-3.3.9.bin.WIN64/include -I Lib/freetype-2.13.2/include -I Lib/freetype-2.13.2/include/freetype -I Lib/glm-0.9.9.8/glm -I Lib^
    -I src -I Zerengine^
    -O0 -pipe -std=c++2c^
    -L Lib/glfw-3.3.9.bin.WIN64/lib-static-ucrt -L C:\VulkanSDK\1.3.280.0\Lib^
    -lglfw3 -lvulkan-1

:: -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wunused -Woverloaded-virtual -Wformat=2 -Wnull-dereference -Wpedantic^

::-llegacy_stdio_definitions

::-llibcpmt -llibvcruntime -llibucrt
::-march=native
::-Wdouble-promotion -Wconversion -Wsign-conversion
::-Wduplicated-cond -Wduplicated-branches -Wlogical -op -Wuseless-cast -Wold-style-cast -Wcast-align