rm -r build/

mkdir build && cd build
cmake -DANDROID_PLATFORM=30 \
        -DCMAKE_TOOLCHAIN_FILE=$HOME/Library/Android/sdk/ndk/26.1.10909125/build/cmake/android.toolchain.cmake \
        -DANDROID_ABI=arm64-v8a ..
make