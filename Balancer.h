#pragma once

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"



void ballDetect();

cv::Mat camera();

cv::Point findCenter( cv::Mat img );

