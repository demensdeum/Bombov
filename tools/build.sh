clear
rm -rf ./build 
mkdir ./build

glslc src/VulkanVertexShader.vert -o build/VulkanVertexShader.spv

if [ $? -eq 0 ]; then
    echo "Vertex shader compile success"
else
    exit 1
fi

glslc src/VulkanFragmentShader.frag -o build/VulkanFragmentShader.spv

if [ $? -eq 0 ]; then
    echo "Fragment shader compile success"
else
    exit 2
fi

shaderc -f src/BgfxVertexShader.vs -o build/BgfxVertexShader.spirv --type v -p spirv

if [ $? -eq 0 ]; then
    echo "Vertex shader compile success"
else
    exit 1
fi

shaderc -f src/BgfxFragmentShader.fs -o build/BgfxFragmentShader.spirv --type f -p spirv

if [ $? -eq 0 ]; then
    echo "Fragment shader compile success"
else
    exit 1
fi

shaderc -f src/BgfxVertexShader.vs -o build/BgfxVertexShader.glsl --type v -p 440

if [ $? -eq 0 ]; then
    echo "Vertex shader compile success"
else
    exit 1
fi

shaderc -f src/BgfxFragmentShader.fs -o build/BgfxFragmentShader.glsl --type f -p 440

if [ $? -eq 0 ]; then
    echo "Fragment shader compile success"
else
    exit 1
fi

cp -r -v ./resources/. ./build
cd build
pwd
cmake ../src/
make -j$(nproc)
./Bombov