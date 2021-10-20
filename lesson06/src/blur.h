#pragma once

#include <opencv2/highgui.hpp>

cv::Mat blur(cv::Mat img, double sigma);

double Gauss(int x, int y, double sigma);