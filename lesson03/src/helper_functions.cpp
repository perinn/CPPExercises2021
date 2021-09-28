#include "helper_functions.h"

#include <libutils/rasserts.h>
#include <iostream>


cv::Mat makeAllBlackPixelsBlue(cv::Mat image) {
    // TODO реализуйте функцию которая каждый черный пиксель картинки сделает синим

    // ниже приведен пример как узнать цвет отдельного пикселя - состоящий из тройки чисел BGR (Blue Green Red)
    // чем больше значение одного из трех чисел - тем насыщеннее его оттенок
    // всего их диапазон значений - от 0 до 255 включительно
    // т.е. один байт, поэтому мы используем ниже тип unsigned char - целое однобайтовое неотрицательное число

    //    cv::Vec3b color = image.at<cv::Vec3b>(13, 5); // взяли и узнали что за цвет в пикселе в 14-ом ряду (т.к. индексация с нуля) и 6-ой колонке
    //    unsigned char blue = color[0]; // если это число равно 255 - в пикселе много синего, если равно 0 - в пикселе нет синего
    //    unsigned char green = color[1];
    //    unsigned char red = color[2];

    // как получить белый цвет? как получить черный цвет? как получить желтый цвет?
    // поэкспериментируйте! например можете всю картинку заполнить каким-то одним цветом

    // пример как заменить цвет по тем же координатам
    //red = 255;
    // запустите эту версию функции и посмотрите на получившуюся картинку - lesson03/resultsData/01_blue_unicorn.jpg
    // какой пиксель изменился? почему он не чисто красный?
    //image.at<cv::Vec3b>(13, 5) = cv::Vec3b(blue, green, red);

    for( int i = 0; i < image.cols; i++){
        for( int j = 0; j < image.rows; j++){
            cv::Vec3b color = image.at<cv::Vec3b>(j, i);
            unsigned char blue = color[0];
            unsigned char green = color[1];
            unsigned char red = color[2];

            if(blue == 0 && green == 0 && red == 0){
                image.at<cv::Vec3b>(j, i) = cv::Vec3b(255, green, red);
            }

        }
    }
    return image;
}

cv::Mat invertImageColors(cv::Mat image) {
    // TODO реализуйте функцию которая каждый цвет картинки инвертирует:
    // т.е. пусть ночь станет днем, а сумрак рассеется
    // иначе говоря замените каждое значение яркости x на (255-x) (т.к находится в диапазоне от 0 до 255)
    for( int i = 0; i < image.cols; i++){
        for( int j = 0; j < image.rows; j++){
            cv::Vec3b color = image.at<cv::Vec3b>(j, i);
            unsigned char blue = color[0];
            unsigned char green = color[1];
            unsigned char red = color[2];


            image.at<cv::Vec3b>(j, i) = cv::Vec3b(255 - blue, 255- green, 255-red);


        }
    }
    return image;
}

cv::Mat addBackgroundInsteadOfBlackPixels(cv::Mat object, cv::Mat background) {
    // TODO реализуйте функцию которая все черные пиксели картинки-объекта заменяет на пиксели с картинки-фона
    // т.е. что-то вроде накладного фона получится

    // гарантируется что размеры картинок совпадают - проверьте это через rassert, вот например сверка ширины:
    rassert(object.cols == background.cols, 341241251251351);
    rassert(object.rows == background.rows, 341241251251351);

    for( int i = 0; i < object.cols; i++){
        for( int j = 0; j < object.rows; j++){
            cv::Vec3b color_object = object.at<cv::Vec3b>(j, i);


            if(color_object[0] == 0 && color_object[1] == 0 && color_object[2] == 0){
                object.at<cv::Vec3b>(j, i) = background.at<cv::Vec3b>(j, i);
            }


        }
    }

    return object;
}

cv::Mat addBackgroundInsteadOfBlackPixelsLargeBackground(cv::Mat object, cv::Mat largeBackground, int J, int I) {

    int delta_rows = J - object.rows/2;
    int delta_cols = I - object.cols/2;

    for(int i = delta_cols; i < object.cols + delta_cols; i++){
        for(int j = delta_rows; j < object.rows + delta_rows; j++){
            cv::Vec3b color_object = object.at<cv::Vec3b>(j - delta_rows, i - delta_cols);

            if(color_object[0] != 0 && color_object[1] != 0 && color_object[2] != 0){
                largeBackground.at<cv::Vec3b>(j, i) = object.at<cv::Vec3b>(j - delta_rows, i - delta_cols);
            }
        }
    }
    return largeBackground;
}

cv::Mat addBackgroundInsteadOfBlackPixelsLargeBackground_N_times(cv::Mat object, cv::Mat largeBackground, int N){

    for(int i = 0; i < N; i++){
        int X = rand() % (largeBackground.cols - object.cols) + object.cols/2;
        int Y = rand() % (largeBackground.rows - object.rows) + object.rows/2;
        largeBackground = addBackgroundInsteadOfBlackPixelsLargeBackground(object, largeBackground, Y, X);
    }

    return largeBackground;
}

cv::Mat f6(cv::Mat object,cv::Mat largeBackground){
    double J_scale = (double)largeBackground.rows/(double)object.rows;
    double I_scale = (double)largeBackground.cols/(double)object.cols;

    for(int i = 0; i < largeBackground.cols; i++){
        for(int j = 0; j < largeBackground.rows; j++){
            cv::Vec3b color_object = object.at<cv::Vec3b>((double)j/J_scale, (double)i/I_scale);
            if(color_object[0] != 0 && color_object[1] != 0 && color_object[2] != 0){
                largeBackground.at<cv::Vec3b>(j, i) = object.at<cv::Vec3b>((double)j/J_scale, (double)i/I_scale);
            }
        }
    }
    return largeBackground;
}

cv::Mat f20(cv::Mat object){
    for( int i = 0; i < object.cols; i++){
        for( int j = 0; j < object.rows; j++){
            cv::Vec3b color_object = object.at<cv::Vec3b>(j, i);


            if(color_object[0] == 0 && color_object[1] == 0 && color_object[2] == 0){
                object.at<cv::Vec3b>(j, i) = cv::Vec3b(rand()%255, rand()%255, rand()%255);
            }


        }
    }




    return object;
}

cv::Mat f_4_0(cv::Mat object, cv::Mat background){
    double J_scale = (double)background.rows/(double)object.rows;
    double I_scale = (double)background.cols/(double)object.cols;
    for(int i = 0; i < background. cols; i++){
        for(int j = 0; j < background.rows; i++){
            background.at<cv::Vec3b>(j, i) = object.at<cv::Vec3b>((double)j/J_scale, (double)i/I_scale);
        }
    }
    return background;
}

cv::Mat f_4_1(cv::Mat object, cv::Mat background, cv::Vec3b color) {

    for( int i = 0; i < object.cols; i++){
        for( int j = 0; j < object.rows; j++){
            cv::Vec3b color_object = object.at<cv::Vec3b>(j, i);
            cv::Vec3b color_background = background.at<cv::Vec3b>(j, i);

            if((int)color_object[0] == (int)color[0] && (int)color_object[1] == (int)color[1] && (int)color_object[2] == (int)color[2]){
                std::cout << "serega 1";
                object.at<cv::Vec3b>(j, i) = cv::Vec3b((int)color_background[0],(int)color_background[1],(int)color_background[2]);

            }


        }
    }

    return object;
}
