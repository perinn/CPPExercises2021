#include "hough.h"

#include <libutils/rasserts.h>
#include <opencv2/imgproc.hpp>

double toRadians(double degrees)
{
    const double PI = 3.14159265358979323846264338327950288;
    return degrees * PI / 180.0;
}

double estimateR(double x0, double y0, double theta0radians)
{
    double r0 = x0 * cos(theta0radians) + y0 * sin(theta0radians);
    return r0;
}

//cv::Mat buildHough(cv::Mat sobel) {// единственный аргумент - это результат свертки Собелем изначальной картинки
//    // проверяем что входная картинка - одноканальная и вещественная:
//    rassert(sobel.type() == CV_32FC1, 237128273918006);
//
//    // TODO
//    // Эта функция по картинке с силами градиентов (после свертки оператором Собеля) строит пространство Хафа
//    // Вы можете либо взять свою реализацию из прошлого задания, либо взять эту заготовку:
//
//    int width = sobel.cols;
//    int height = sobel.rows;
//
//    // решаем какое максимальное значение у параметра theta в нашем пространстве прямых
//    int max_theta = 360;
//
//    // решаем какое максимальное значение у параметра r в нашем пространстве прямых:
//    int max_r = sqrtf(width*width + height*height);
//
//    // создаем картинку-аккумулятор, в которой мы будем накапливать суммарные голоса за прямые
//    // так же известна как пространство Хафа
//    cv::Mat accumulator(max_r, max_theta, CV_32FC1, 0.0f); // зануление аккумулятора через указание значения по умолчанию в конструкторе
//
//    // проходим по всем пикселям нашей картинки (уже свернутой оператором Собеля)
//    for (int y0 = 0; y0 < height; ++y0) {
//        for (int x0 = 0; x0 < width; ++x0) {
//            // смотрим на пиксель с координатами (x0, y0)
//            float strength = sobel.at<float>(y0, x0);
//
//            // теперь для текущего пикселя надо найти все возможные прямые которые через него проходят
//            // переберем параметр theta по всему возможному диапазону (в градусах):
//            for (int theta0 = 0; theta0 < max_theta; ++theta0) {
//
//                double theta0radians = toRadians(theta0);
//                int r0 = (int) round(estimateR(x0, y0, theta0radians)); // оцениваем r0 и округляем его до целого числа
//                if (r0 < 0 || r0 >= max_r)continue;
//
//                // TODO надо определить в какие пиксели i,j надо внести наш голос с учетом проблемы "Почему два экстремума?" обозначенной на странице:
//                // https://www.polarnick.com/blogs/239/2021/school239_11_2021_2022/2021/11/09/lesson9-hough2-interpolation-extremum-detection.html
//
//                // чтобы проверить не вышли ли мы за пределы картинки-аккумулятора - давайте явно это проверим
//                rassert(x0 >= 0, 237891731289044);
//                rassert(x0 < accumulator.cols, 237891731289045);
//                rassert(y0 >= 0, 237891731289046);
//                rassert(y0 < accumulator.rows, 237891731289047);
//                // теперь легко отладить случай выхода за пределы картинки
//                // просто поставьте точку остановки внутри rassert:
//                // нажмите Ctrl+Shift+N -> rasserts.cpp
//                // и поставьте точку остановки на 8 строке: "return line;"
//
//                // и добоавляем в картинку-аккумулятор наш голос с весом strength (взятый из картинки свернутой Собелем)
//                accumulator.at<float>(y0, x0) += strength;
//            }
//        }
//    }
//
//    return accumulator;
//}

cv::Mat buildHough(cv::Mat sobel) {// единственный аргумент - это результат свертки Собелем изначальной картинки
    // проверяем что входная картинка - одноканальная и вещественная:
    rassert(sobel.type() == CV_32FC1, 237128273918006);

    int width = sobel.cols;
    int height = sobel.rows;

    // решаем какое максимальное значение у параметра theta в нашем пространстве прямых
    int max_theta = 360;

    // решаем какое максимальное значение у параметра r в нашем пространстве прямых:
    int max_r = sqrt(height*height+width*width); // TODO замените это число так как вам кажется правильным (отталкиваясь от разрешения картинки - ее ширины и высоты)

    // создаем картинку-аккумулятор, в которой мы будем накапливать суммарные голоса за прямые
    // так же известна как пространство Хафа
    cv::Mat accumulator(max_r, 360, CV_32FC1, 0.0f); // TODO подумайте какого разрешения она должна быть и поправьте ее размер

    // TODO не забудьте заполнить эту матрицу-картинку-аккумулятор нулями (очистить)

    // проходим по всем пикселям нашей картинки (уже свернутой оператором Собеля)
    for (int y0 = 0; y0 < height; ++y0) {
        for (int x0 = 0; x0 < width; ++x0) {
            // смотрим на пиксель с координатами (x0, y0)
            float strength = sobel.at<float>(y0, x0);// TODO считайте его "силу градиента" из картинки sobel

            // теперь для текущего пикселя надо найти все возможные прямые которые через него проходят
            // переберем параметр theta по всему возможному диапазону (в градусах):
            for (int theta0 = 0; theta0 < max_theta; ++theta0) {
                // TODO рассчитайте на базе информации о том какие координаты у пикселя - (x0, y0) и какой параметр theta0 мы сейчас рассматриваем
                // TODO обратите внимание что функции sin/cos принимают углы в радианах, поэтому сначала нужно пересчитать theta0 в радианы (воспользуйтесь константой PI)
                const double PI = 3.14159265358979323846264338327950288;
                float r0 = x0*cos(theta0*(2*PI/360))+y0*sin(theta0*(2*PI/360));

                int i = theta0;
                int j = r0;

                if( r0<0){
                    j = x0*cos((theta0+180)*(2*PI/360))+y0*sin((theta0+180)*(2*PI/360));
                    i = (theta0+180)%360;
                }

                // TODO теперь рассчитайте координаты пикслея в пространстве Хафа (в картинке-аккумуляторе) соответсвующего параметрам theta0, r0


                // чтобы проверить не вышли ли мы за пределы картинки-аккумулятора - давайте явно это проверим:
                rassert(i >= 0, 237891731289044);
                rassert(i < accumulator.cols, 237891731289045);
                rassert(j >= 0, 237891731289046);
                rassert(j < accumulator.rows, 237891731289047);
                // теперь легко отладить случай выхода за пределы картинки
                // TODO просто поставьте точку остановки внутри rassert:
                // нажмите Ctrl+Shift+N -> rasserts.cpp
                // и поставьте точку остановки на 8 строке: "return line;"

                // TODO и добавьте в картинку-аккумулятор наш голос с весом strength (взятый из картинки свернутой Собелем)
                accumulator.at<float>(j, i) += strength;
            }
        }
    }

    return accumulator;
}

std::vector<PolarLineExtremum> findLocalExtremums(cv::Mat houghSpace)
{
    rassert(houghSpace.type() == CV_32FC1, 234827498237080);

    const int max_theta = 360;
    rassert(houghSpace.cols == max_theta, 233892742893082);
    const int max_r = houghSpace.rows;

    std::vector<PolarLineExtremum> winners;

    for (int theta = 0; theta < max_theta; ++theta) {
        for (int r = 0; r < max_r; ++r) {
            // TODO
            // ...
            // if (ok) {
            //     PolarLineExtremum line(theta, r, votes);
            //     winners.push_back(line);
            // }
            bool aboba = true;
            for( int i = -1; i <=1; i++){
                for( int j = -1; j<=1 ; j++){
                    if(i+theta < max_theta && i+theta >= 0 && j+r < max_r && j+r >=0 && i!=0 && j !=0){
                        if(houghSpace.at<float>(j+r, i+theta) >= houghSpace.at<float>(r, theta)){
                            aboba = false;
                        }
                    }
                }
            }
            if(aboba){
                PolarLineExtremum line = PolarLineExtremum((double)theta, (double)r, (double)houghSpace.at<float>(r,theta));
                winners.push_back(line);
            }
        }
    }

    return winners;
}

std::vector<PolarLineExtremum> filterStrongLines(std::vector<PolarLineExtremum> allLines, double thresholdFromWinner)
{
    std::vector<PolarLineExtremum> strongLines;

    // Эта функция по множеству всех найденных локальных экстремумов (прямых) находит самую популярную прямую
    // и возвращает только вектор из тех прямых, что не сильно ее хуже (набрали хотя бы thresholdFromWinner голосов от победителя, т.е. например половину)

    // TODO

    PolarLineExtremum max_line = PolarLineExtremum(0.0,0.0,0.0);
    for(PolarLineExtremum i : allLines){
        if(i.votes > max_line.votes) {
            max_line.theta = i.theta;
            max_line.r = i.r;
            max_line.votes = i.votes;
        }
    }

    for(PolarLineExtremum i : allLines){
        if(i.votes >= (double)thresholdFromWinner*max_line.votes) {
            strongLines.push_back(i);
        }
    }


    return strongLines;
}

std::vector<PolarLineExtremum> CutLines(std::vector<PolarLineExtremum> arr0, cv::Mat img){
    std::vector<PolarLineExtremum> arr1;
    std::vector<int> isdeleted;
    bool a = false;
    for(int i = 0; i < arr0.size(); i++){
        for(int j = 0; j < arr0.size(); j++){
            if (fabs(arr0[i].theta-arr0[j].theta)<5 && fabs(arr0[i].r - arr0[j].r)<0.1*fmin(img.cols, img.rows) && std::find(isdeleted.begin(), isdeleted.end(), i) == isdeleted.end() && std::find(isdeleted.begin(), isdeleted.end(), j) == isdeleted.end() ){
                    a = true;
                    double theta0 = (arr0[i].theta+arr0[j].theta)/2;
                    double r0 = (arr0[i].r+arr0[j].r)/2;
                    double votes0 = (arr0[i].votes+arr0[j].votes)/2;

                    isdeleted.push_back(i);
                    isdeleted.push_back(j);

                    arr1.push_back(PolarLineExtremum(theta0, r0, votes0));
                }
        }
    }

    if(a){
        return CutLines(arr1, img);
    }else{
        return arr1;
    }
}
