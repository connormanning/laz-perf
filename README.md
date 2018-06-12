```
mkdir build && cd build
cmake -DEMSCRIPTEN=1 \
    -DCMAKE_TOOLCHAIN_FILE=~/code/emsdk/emscripten/1.38.5/cmake/Modules/Platform/Emscripten.cmake
make

cd ..
```

```
$ node merge.js && node combined.js
XYZ[0] -195608 335044 -3627
RGB[0] 15616 20224 13312

XYZ[1] -195096 476622 8194
RGB[1] 1 161 155

XYZ[2] 67560 306732 -10090
RGB[2] 1 94 102
```

```
$ g++ -std=c++11 cpp.cpp -I laz-perf && ./a.out
XYZ[0]: -195608 335044 -3627
RGB[0]: 15616 20224 13312

XYZ[1]: -195096 476622 8194
RGB[1]: 41216 39680 38400

XYZ[2]: 67560 306732 -10090
RGB[2]: 24064 26112 25600
```

```
$ pdal info wide-color.laz -p 0
      "X": 348647.392,
      "Y": 3068495.044,
      "Z": 1360.373,
      "Red": 15616,
      "Green": 20224,
      "Blue": 13312
      ...

$ pdal info wide-color.laz -p 0
      "X": 348647.904,
      "Y": 3068636.622,
      "Z": 1372.194,
      "Red": 41216,
      "Green": 39680,
      "Blue": 38400,
      ...
```

