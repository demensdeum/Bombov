clear
rm -rf ./build 
mkdir ./build
testShader=0
if [ $testShader -eq 1 ]; then
    glslc src/test-shaders/VulkanVertexShader.vert -o build/VulkanVertexShader.spv
else
    glslc src/VulkanVertexShader.vert -o build/VulkanVertexShader.spv
fi
if [ $? -eq 0 ]; then
    echo "Vertex shader compile success"
else
    exit 1
fi
if [ $testShader -eq 1 ]; then
    glslc src/test-shaders/VulkanFragmentShader.frag -o build/VulkanFragmentShader.spv
else
    glslc src/VulkanFragmentShader.frag -o build/VulkanFragmentShader.spv
fi
if [ $? -eq 0 ]; then
    echo "Fragment shader compile success"
else
    exit 2
fi
cp -r -v ./resources/. ./build
cd build
pwd
cmake ../src/
make -j$(nproc)
./Bombov