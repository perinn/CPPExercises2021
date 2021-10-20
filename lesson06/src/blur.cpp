#include "blur.h"

#include <libutils/rasserts.h>

double pi = 3.14159265359;
double exp0 = 2.71828182845904;

double Gauss(int x, int y, double sigma){
    return (1/(2*pi*sigma*sigma))*pow(exp0, -(x*x+y*y)/(2*sigma*sigma));
}

cv::Mat blur(cv::Mat img, int sigma) {
    cv::Mat res_img(img.rows, img.cols, CV_32FC3);

    std::vector<std::vector<double>> GaussKoef(2*sigma+1, std::vector<double>(2*sigma+1));

    for(int i = 0; i < 2*sigma+1; i++){
        for(int j = 0; j < 2*sigma+1; j++){
            GaussKoef[i][j] = Gauss(i-(sigma+1),j-(sigma+1),sigma);
        }
    }
    for(int i = 0; i < img.cols; i++){
        for(int j = 0; j < img.rows; j++){

            double SumKoef = 0;

            double C0 = 0;
            double C1 = 0;
            double C2 = 0;

            for(int x = -sigma; x <= sigma; x++){
                for(int y = -sigma; y <= sigma; y++){
                    if(i+x>=0 && i+x<img.cols && j+y>=0 && j+y<img.rows){
                        double Koef = GaussKoef[x][y];
                        SumKoef += Koef;
                        C0 += Koef*img.at<cv::Vec3b>(j+y,i+x)[0];
                        C1 += Koef*img.at<cv::Vec3b>(j+y,i+x)[1];
                        C2 += Koef*img.at<cv::Vec3b>(j+y,i+x)[2];
                    }
                }
            }

            C0 /= SumKoef;
            C1 /= SumKoef;
            C2 /= SumKoef;

            res_img.at<cv::Vec3b>(j,i) = cv::Vec3b(C0,C1,C2);
        }
    }
    return res_img;
}
