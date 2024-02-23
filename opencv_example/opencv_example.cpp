#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include "opencv2/opencv.hpp"
#include "midas.h"

int main()
{
    const char *model_path = "models/midasModel.tflite";
    MidasDepthEstimator depth;
    depth.initializeModel(model_path, 3);

    cv::VideoCapture cap(1);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 320);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 240);

    cap.set(cv::CAP_PROP_FPS, 5);
    if (!cap.isOpened())
    {
        std::cerr << "Error: Could not open the camera." << std::endl;
        return -1;
    }
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    // Check if the camera settings were successfully applied
    if (!cap.set(cv::CAP_PROP_FRAME_WIDTH, 640) || !cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480))
    {
        std::cerr << "Error: Unable to set camera resolution." << std::endl;
        return -1;
    }
    // cv::namedWindow("Camera Feed", cv::WINDOW_NORMAL);
    cv::Mat frame;

    int depthThreshold = 200.0;
    int max = 255;

    std::chrono::steady_clock::time_point startTime, endTime;
    int frameCount = 0;

    while (true)
    {
        startTime = std::chrono::steady_clock::now();
        cap >> frame;

        cv::Mat depth_im = depth.estimateDepth(frame);

        object_detection(depth_im, depthThreshold, max);
        // std::thread t(&cv::imshow,"Camera Feed", depth_im);
        cv::imshow("Camera Feed", depth_im);

        endTime = std::chrono::steady_clock::now();
        std::chrono::duration<double> frameDuration = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime);
        frameCount++;

        if (frameDuration.count() >= 1.0)
        {
            double fps = static_cast<double>(frameCount) / frameDuration.count();
            std::cout << "FPS: " << fps << std::endl;
            frameCount = 0;
            startTime = std::chrono::steady_clock::now();
        }

        if (cv::waitKey(1) == 'q')
        {
            break;
        }
    }
    cap.release();
    // cv::destroyWindow("Camera Feed");

    return 0;
}
