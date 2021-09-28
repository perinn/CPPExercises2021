#pragma once

#include <opencv2/highgui.hpp> // подключили часть библиотеки OpenCV, теперь мы можем работать с картинками (знаем про тип cv::Mat)

cv::Mat makeAllBlackPixelsBlue(cv::Mat image);

cv::Mat invertImageColors(cv::Mat image);

cv::Mat addBackgroundInsteadOfBlackPixels(cv::Mat object, cv::Mat background);

cv::Mat addBackgroundInsteadOfBlackPixelsLargeBackground(cv::Mat object, cv::Mat largeBackground,  int J, int I);

cv::Mat addBackgroundInsteadOfBlackPixelsLargeBackground_N_times(cv::Mat object, cv::Mat largeBackground, int N);

cv::Mat f6(cv::Mat object, cv::Mat largeBackground);

cv::Mat f20(cv::Mat object);

cv::Mat f_4_0(cv::Mat object, cv::Mat background);
cv::Mat f_4_1(cv::Mat object, cv::Mat background, cv::Vec3b color);