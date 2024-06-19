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
cp -r -v ./resources/. ./build
cd build
pwd
cmake ../src/
make -j 16
./Bombov