#include "helper_functions.h"

#include <libutils/rasserts.h>


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

cv::Mat addBackgroundInsteadOfBlackPixelsLargeBackground(cv::Mat object, cv::Mat largeBackground, int delta_rows, int delta_cols) {
    // теперь вам гарантируется что largeBackground гораздо больше - добавьте проверок этого инварианта (rassert-ов)
    rassert(object.cols <= largeBackground.cols, 341241251251351);
    rassert(object.rows <= largeBackground.rows, 341241251251351);
    // TODO реализуйте функцию так, чтобы нарисовался объект ровно по центру на данном фоне, при этом черные пиксели объекта не должны быть нарисованы

    if (delta_rows == -1 && delta_cols ==-1){
        delta_rows = (largeBackground.rows-object.rows)/2;
        delta_cols = (largeBackground.cols-object.cols)/2;
    }
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
    rassert(object.cols <= largeBackground.cols, 341241251251351);
    rassert(object.rows <= largeBackground.rows, 341241251251351);

    int delta_rows = (largeBackground.rows-object.rows)/2;
    int delta_cols = (largeBackground.cols-object.cols)/2;

    for(int i = 0; i < N; i++){

    }
    return largeBackground;
}
