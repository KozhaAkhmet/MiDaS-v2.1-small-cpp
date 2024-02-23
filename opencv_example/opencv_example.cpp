#include <chrono>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

#include "midas.h"
#include "opencv2/opencv.hpp"

// Function for requesting a state of the async.
template <typename R>
bool is_ready(std::future<R> const& f) {
  return f.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
}

int main() {
  // Preparing the model
  const char* model_path = "models/midasModel.tflite";
  MidasDepthEstimator depth;
  int thread_num = 3;
  depth.initializeModel(model_path, thread_num);

  cv::VideoCapture cap(0);
  // Setiing the camera resolution
  cap.set(cv::CAP_PROP_FRAME_WIDTH, 320);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT, 240);

  // Limiting the buffer and fps to sync with real time.
  cap.set(cv::CAP_PROP_FPS, 5);
  cap.set(cv::CAP_PROP_BUFFERSIZE, 2);

  if (!cap.isOpened()) {
    std::cerr << "Error: Could not open the camera." << std::endl;
    return -1;
  }

  cv::namedWindow("Camera Feed", cv::WINDOW_NORMAL);
  cv::Mat frame;
  cv::Mat depth_img;

  // Bounding the depth class with its function for async.
  auto boundFunction = std::bind(&MidasDepthEstimator::estimateDepth, &depth,
                                 std::placeholders::_1);
  bool fut_status = true;
  std::future<cv::Mat> fut;

  while (true) {
    cap >> frame;
    // Executing image processing in another thread asyncronously.
    if (fut_status) {
      fut = std::async(std::launch::async, boundFunction, std::ref(frame));
      fut_status = false;
    }
    if (is_ready(fut)) {
      fut_status = true;
      depth_img = fut.get();
      cv::imshow("Camera Feed", depth_img);
    }

    if (cv::waitKey(1) == 'q') {
      break;
    }
  }
  cap.release();

  return 0;
