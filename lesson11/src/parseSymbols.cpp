#include <opencv2/imgproc.hpp>
#include "parseSymbols.h"
#include <filesystem>
#include <iostream>
#include <libutils/rasserts.h>

#include "parseSymbols.h"

#include <opencv2/imgproc.hpp>


std::vector<cv::Mat> splitSymbols(cv::Mat img)
{
    std::vector<cv::Mat> symbols;
    cv::Mat img1 = cv::adaptiveThreshold(img, 255.0, 'BORDER_REPLICATE' ,'THRESH_BINARY', 64, 1.0);
    // TODO 101: чтобы извлечь кусок картинки (для каждого прямоугольника cv::Rect вокруг символа) - загуглите "opencv how to extract subimage"
    return symbols;
}
