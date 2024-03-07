# MiDaS-v2.1-small-cpp

## Table Of Contents

1. About
2. Results
3. Installation
4. References

## 1. About the Project

 A Monocular depth estimation with MiDAS, TensorFlow Lite and OpenCV on The Raspberry Pi 4. All in C++.

Here I used the v2.1 small MiDAS model which is the best in performance. [See MiDAS Source Code](https://github.com/isl-org/MiDaS).

 This is a part of my bachelor's graduation project ["Making an Autonomous Car with Depth Estimation"](https://github.com/KozhaAkhmet/depth-car).  

## 2. Results

This project is tested on Raspberry Pi 4 Model B with 4 GB RAM with the 64-bit Ubuntu 22.04. Used a 3A power supply and without overclocking. Here are the results:

| Device         | RAM  | OS     | Multithread(All) Performance | Single Thread Performance |
| -------------- | ---- | ------ | ---------------------------- | ------------------------- |
| Raspberry Pi 4 | 4 GB | Ubuntu | ~ 2.14 FPS                   | ~ 0.91 FPS                |
#
![](media/ExampleImage.png)
![](media/ExampleImage2.png)

## 3. Installation and Execution

| Library         | Version |
| --------------- | ------- |
| TensorFlow Lite | v2.12.0 |
| OpenCV          | v4.6.0  |

Here how the directory tree should look like:

```
.
├── CMakeLists.txt
├── lib
│   ├── flatbuffers_include
│   │   └── flatbuffers
│   │       └── ...
│   ├── midas_cpp
│   │   ├── CMakeLists.txt
│   │   ├── midas.cpp
│   │   └── midas.h
│   ├── tensorflow_include
│   │   └── ...
│   └── tensorflow_src
│       └── ...
├── opencv_example
│   ├── CMakeLists.txt
│   ├── models
│   │   └── midasModel.tflite
│   └── opencv_example.cpp
└── README.md
```
## TensorFlow Lite
Trained model importer to run interference of MiDaS.

The library can be included by compiling it from the source. The steps are available at [Source File](https://github.com/tensorflow/tensorflow). 
The library provides build tool solutions with CMake and Bazel. For more information check out the official [documentation](https://www.tensorflow.org/lite/guide).

**The compilation on the device is not recommended due to its low power. Prefer compiling with cross-compilation through a more powerful machine.**

The CMake installation may cause some problems, use Bazel in such cases. There is also a docker image available to provide a simpler development at [here](https://hub.docker.com/r/tensorflow/tensorflow/).  The image includes Bazel and Tensorflow source code. 

After compilation, move the directory to your device and include CMake as a shared library. For more information check out the [the cross-compilation documentation](https://www.tensorflow.org/lite/guide/build_cmake_arm).

### Preparing Headers for The TensorFlow Lite

>You can find a shared library in `bazel-bin/tensorflow lite/libtensorflowlite.so`.
>
>Currently, there is no straightforward way to extract all header files needed, so you must include all header files in `tensorflow/lite/` from the TensorFlow repository. Additionally, you will need header files from FlatBuffers and Abseil. *[ From  TensorFlow Lite for ARM boards](https://www.tensorflow.org/lite/guide/build_arm)*

A script is available [here](source2include.sh) to automate header file extraction from the source.

Clone the flatbuffer repository to include their header files. 
```bash
$ git clone https://github.com/google/flatbuffers.git # FlatBuffer Repository
```
Place the include directory alongside the project.

## OpenCV

OpenCV provides features such as camera capture and image processing.  The library is available at most Debian-based distributions through apt as of December 2023.

```bash
$ sudo apt install libopencv-dev
```
The library is also available as a source. Check out the [documentation](https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html) to compile from the source.
### Compile and Execute

Make the build directory

```
$ mkdir build
$ cd build
```

Compile 

```
$ cmake ..
$ make
$ cd ..
```

 Make the binary executable

```
$ sudo chmod +x build/opencv_example/opencv_example
```

Now execute

```bash
$ sudo ./build/opencv_example/opencv_example # Here you should use sudo to able to access the camera.
```

