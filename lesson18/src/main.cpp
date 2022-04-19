#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <set>
#include <chrono>
#include <iostream>
#include <filesystem>
#include <memory>

#include <libutils/rasserts.h>
#include <libutils/fast_random.h>


// Эта функция говорит нам правда ли пиксель отмаскирован, т.е. отмечен как "удаленный", т.е. белый
bool isPixelMasked(cv::Mat mask, int j, int i) {
    rassert(j >= 0 && j < mask.rows, 372489347280017);
    rassert(i >= 0 && i < mask.cols, 372489347280018);
    rassert(mask.type() == CV_8UC3, 2348732984792380019);
    if(mask.at<cv::Vec3b>(j,i)!=cv::Vec3b(0,0,0)){
        return true;
    }else{return false;}
}
int estimateQuality(cv::Mat image, int j, int i, int ny, int nx, int a, int b){
    int res = 0;
    for(int dx = - b/2; dx <= b/2; dx++){
        for(int dy = -a/2; dy <= a/2; dy++){
            int d0 = (image.at<cv::Vec3b>(j+dy,i+dx)[0]-image.at<cv::Vec3b>(ny+dy,nx+dx)[0]);
            int d1 = (image.at<cv::Vec3b>(j+dy,i+dx)[1]-image.at<cv::Vec3b>(ny+dy,nx+dx)[1]);
            int d2 = (image.at<cv::Vec3b>(j+dy,i+dx)[2]-image.at<cv::Vec3b>(ny+dy,nx+dx)[2]);
            res += d0*d0+d1*d1+d2*d2;
        }
    }
    return res;
}

void run(int caseNumber, std::string caseName) {
    std::cout << "_________Case #" << caseNumber << ": " <<  caseName << "_________" << std::endl;

    cv::Mat original = cv::imread("lesson18/data/" + std::to_string(caseNumber) + "_" + caseName + "/" + std::to_string(caseNumber) + "_original.jpg");
    cv::Mat mask = cv::imread("lesson18/data/" + std::to_string(caseNumber) + "_" + caseName + "/" + std::to_string(caseNumber) + "_mask.png");
    rassert(!original.empty(), 324789374290018);
    rassert(!mask.empty(), 378957298420019);

    // TODO напишите rassert сверяющий разрешение картинки и маски
    rassert(original.cols==mask.cols&&original.rows==mask.rows, 85648756487564875);
    // TODO выведите в консоль это разрешение картинки
     std::cout << "Image resolution: " << original.cols << "x" << original.rows << std::endl;

    // создаем папку в которую будем сохранять результаты - lesson18/resultsData/ИМЯ_НАБОРА/
    std::string resultsDir = "lesson18/resultsData/";
    if (!std::filesystem::exists(resultsDir)) { // если папка еще не создана
        std::filesystem::create_directory(resultsDir); // то создаем ее
    }
    resultsDir += std::to_string(caseNumber) + "_" + caseName + "/";
    if (!std::filesystem::exists(resultsDir)) { // если папка еще не создана
        std::filesystem::create_directory(resultsDir); // то создаем ее
    }

    // сохраняем в папку с результатами оригинальную картинку и маску
    cv::imwrite(resultsDir + "0original.png", original);
    cv::imwrite(resultsDir + "1mask.png", mask);

    // TODO замените белым цветом все пиксели в оригинальной картинке которые покрыты маской
    int n = 0;
    cv::Mat original_cleaned = original.clone();
    for(int i = 0 ; i < original_cleaned.cols; i++){
        for(int j = 0; j < original_cleaned.rows; j++){
            if(isPixelMasked(mask, j, i)){
                original_cleaned.at<cv::Vec3b>(j,i)=cv::Vec3b (255,255,255);
                n++;
            }
        }
    }
    // TODO сохраните в папку с результатами то что получилось под названием "2_original_cleaned.png"
    cv::imwrite(resultsDir + "2_original_cleaned.png", original_cleaned);
    // TODO посчитайте и выведите число отмаскированных пикселей (числом и в процентах) - в таком формате:
    std::cout << "Number of masked pixels: " <<  n << "/" << mask.cols*mask.rows <<" = "<< 100*(float)n/((float)mask.cols*(float)mask.rows) << "%" << std::endl;

    FastRandom random(32542341); // этот объект поможет вам генерировать случайные гипотезы

    // TODO 10 создайте картинку хранящую относительные смещения - откуда брать донора для заплатки, см. подсказки про то как с нею работать на сайте
    cv::Mat shifts = cv::Mat(mask.rows, mask.cols,CV_32SC2, cv::Scalar(0, 0));
    for(int times = 1; times <=1000; times++){
        // TODO 11 во всех отмаскированных пикселях: заполните эту картинку с относительными смещениями - случайными смещениями (но чтобы они и их окрестность 5х5 не выходила за пределы картинки)
        cv::Mat res = original_cleaned.clone();

        for(int i = 0 ; i < shifts.cols; i++){
            for(int j = 0 ; j < shifts.rows; j++){
                if(isPixelMasked(mask, j, i)){
//                    shifts.at<cv::Vec2i>(j, i) = cv::Vec2i (random.next(5, shifts.rows-5), random.next(5, shifts.cols-5));
                    cv::Vec2i dxy = shifts.at<cv::Vec2i>(j,i);
                    int nx = i+dxy[1];
                    int ny = j+dxy[0];
                    int currentQuality = estimateQuality(res, j, i, ny, nx, 5, 5);

                    int rx = random.next(5, res.cols-5);
                    int ry = random.next(5, res.rows-5);
                    int randomQuality = estimateQuality(res, j, i, j+ry, i+rx, 5, 5);

                    if(randomQuality<currentQuality){
                        shifts.at<cv::Vec2i>(j,i) = cv::Vec2i()
                    }
                }
            }
        }


        // TODO 12 во всех отмаскированных пикселях: замените цвет пиксела А на цвет пикселя Б на который указывает относительное смещение пикселя А

        for(int i = 0 ; i < res.cols; i++){
            for(int j = 0 ; j < res.rows; j++){
                if(isPixelMasked(mask, j, i)){
                    res.at<cv::Vec3b>(j,i) = original_cleaned.at<cv::Vec3b>(shifts.at<cv::Vec2i>(j,i)[0], shifts.at<cv::Vec2i>(j,i)[1]);
                }
            }
        }
        // TODO 13 сохраните получившуюся картинку на диск
        if(times % 10==0){
            cv::imwrite(resultsDir + "3_result" + "_" + std::to_string(times)+".png", res);
            std::cout << "progress: " << times/10<< "%" << std::endl;
        }
    }
    // TODO 14 выполняйте эти шаги 11-13 много раз, например 1000 раз (оберните просто в цикл, сохраняйте картинку на диск только на каждой десятой или сотой итерации)
    // TODO 15 теперь давайте заменять значение относительного смещения на новой только если новая случайная гипотеза - лучше старой, добавьте оценку "насколько смещенный патч 5х5 похож на патч вокруг пикселя если их наложить"
    //
    // Ориентировочный псевдокод-подсказка получившегося алгоритма:
    // cv::Mat shifts(...); // матрица хранящая смещения, изначально заполнена парами нулей
    // cv::Mat image = original; // текущая картинка
    // for (100 раз) {
    //     for (пробегаем по всем пикселям j,i) {
    //         if (если этот пиксель не отмаскирован)
    //             continue; // пропускаем т.к. его менять не надо
    //         cv::Vec2i dxy = смотрим какое сейчас смещение для этого пикселя в матрице смещения
    //         int (nx, ny) = (i + dxy.x, j + dxy.y); // ЭТО НЕ КОРРЕКТНЫЙ КОД, но он иллюстрирует как рассчитать координаты пикселя-донора из которого мы хотим брать цвет
    //         currentQuality = estimateQuality(image, j, i, ny, nx, 5, 5); // эта функция (создайте ее) считает насколько похож квадрат 5х5 приложенный центром к (i, j)
    //                                                                                                                        на квадрат 5х5 приложенный центром к (nx, ny)
    //
    //         int (rx, ry) = random.... // создаем случайное смещение относительно нашего пикселя, воспользуйтесь функцией random.next(...);
    //                                      (окрестность вокруг пикселя на который укажет смещение - не должна выходить за пределы картинки и не должна быть отмаскирована)
    //         randomQuality = estimateQuality(image, j, i, j+ry, i+rx, 5, 5); // оцениваем насколько похоже будет если мы приложим эту случайную гипотезу которую только что выбрали
    //
    //         if (если новое качество случайной угадайки оказалось лучше старого) {
    //             то сохраняем (rx,ry) в картинку смещений
    //             и в текущем пикселе кладем цвет из пикселя на которого только что смотрели (цент окрестности по смещению)
    //             (т.е. мы не весь патч сюда кладем, а только его центральный пиксель)
    //         } else {
    //             а что делать если новая случайная гипотеза хуже чем то что у нас уже есть?
    //         }
    //     }
    //     не забываем сохранить на диск текущую картинку
    //     а как численно оценить насколько уже хорошую картинку мы смогли построить? выведите в консоль это число
    // }
}


int main() {
    try {
        run(1, "mic");
        // TODO протестируйте остальные случаи:
//        run(2, "flowers");
//        run(3, "baloons");
//        run(4, "brickwall");
//        run(5, "old_photo");
//        run(6, "your_data"); // TODO придумайте свой случай для тестирования (рекомендуется не очень большое разрешение, например 300х300)

        return 0;
    } catch (const std::exception &e) {
        std::cout << "Exception! " << e.what() << std::endl;
        return 1;
    }
}
