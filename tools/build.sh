clear
rm -rf ./build 
mkdir ./build
cp -r -v ./resources/. ./build
cd build
pwd
cmake ../src/
make -j 16
./Bombov