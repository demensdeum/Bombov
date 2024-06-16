clear
rm -rf ./build 
mkdir ./build
cd build
pwd
cmake ../src/
make -j 8
./Bombov