cmake_minimum_required(VERSION 2.8)
project( midas_opencv )

find_package( OpenCV REQUIRED ) # Dynamic include

set(TENSORFLOW_LIBRARY_DIR "./lib/tensorflow_src/bazel-bin/tensorflow/lite/libtensorflowlite.so" ) 
set(TENSORFLOW_INCLUDE_DIR "./lib/tensorflow_include")
set(FLATBUFFERS_INCLUDE_DIR "./lib/flatbuffers_include")

include_directories( ${OpenCV_INCLUDE_DIRS} ${TENSORFLOW_INCLUDE_DIR} ${FLATBUFFERS_INCLUDE_DIR})

add_subdirectory(./lib/midas_cpp)
add_executable( midas_opencv opencv_example.cpp )

target_link_libraries( midas_opencv ${OpenCV_LIBS}  ${TENSORFLOW_LIBRARY_DIR} midas)

link_libraries(${OpenCV_LIBS})

