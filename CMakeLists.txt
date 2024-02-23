cmake_minimum_required(VERSION 2.8)
project( midas_cpp_examples )

find_package( OpenCV REQUIRED )

set(TENSORFLOW_LIBRARY_DIR "/home/pi/cpp_project/tensorflow_src/bazel-bin/tensorflow/lite/libtensorflowlite.so" )
set(TENSORFLOW_INCLUDE_DIR "/home/pi/cpp_project/tensorflow_include")
set(FLATBUFFERS_INCLUDE_DIR "/home/pi/cpp_project/flatbuffers_include")

include_directories( ${OpenCV_INCLUDE_DIRS} ${TENSORFLOW_INCLUDE_DIR} ${FLATBUFFERS_INCLUDE_DIR})

add_subdirectory(midas_cpp)
add_subdirectory(opencv_example)


link_libraries(${OpenCV_LIBS})

