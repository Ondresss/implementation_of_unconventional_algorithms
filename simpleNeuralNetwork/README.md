mkdir build
cd build
cmake .. -DBUILD_EXAMPLES=OFF -DBUILD_TESTS=OFF
cmake --build . --parallel