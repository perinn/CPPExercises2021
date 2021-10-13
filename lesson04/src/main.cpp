#include <iostream>
#include <filesystem>
#include <libutils/rasserts.h>

#include "disjoint_set.h"
#include "morphology.h"

#include <opencv2/highgui.hpp>

// TODO 100 реализуйте систему непересекающихся множеств - см. файлы disjoint_set.h и disjoint_set.cpp
// чтобы их потестировать - постарайтесь дописать сюда много разных интересных случаев:
void testingMyDisjointSets() {
    DisjointSet set(5);
    rassert(set.count_differents() == 5, 2378923791);
    for (int element = 0; element < 5; ++element) {
        rassert(set.get_set(element) == element, 23892803643);
        rassert(set.get_set_size(element) == 1, 238928031);
    }
    set.union_sets(0,1);
    rassert(set.count_differents() == 4, 123141253)
    rassert(set.get_set_size(0) == 2, 123141253)
    set.union_sets(0,2);
    set.union_sets(0,3);
    set.union_sets(0,4);
    rassert(set.count_differents() == 1, 123141253)
    rassert(set.get_set_size(0) == 5, 123141253)
    DisjointSet set1(10000000);
    for (int element = 0; element < 10000000; ++element) {
        if (element%100 == 0){
            set1.union_sets(0,element+1);
        }
    }
    // TODO 100 по мере реализации DisjointSet - добавьте здесь каких-то вызовов операции "объединение двух множеств", сразу после этого проверяя через rassert что после этого результат такой как вы ожидаете
    // TODO 100 затем попробуйте создать СНМ размера 10.000.000 - и пообъединяйте какие-нибудь элементы (в цикле), быстро ли работает? а если при подвешивании одного корня множества к другому мы не будем учитывать ранк (высоту дерева) - как быстро будет работать?
    // TODO 100 попробуйте скомпилировать программу с оптимизациями и посмотреть ускорится ли программа - File->Settings->CMake->Плюсик над Debug->и переключите его в RelWithDebInfo (чтобы были хоть какие-то отладочные символы)
}

// TODO 200 перенесите сюда основную часть кода из прошлого задания про вычитание фона по первому кадру, но:
// 1) добавьте сохранение на диск визуализации картинок:
// 1.1) картинка эталонного фона
// 1.2) картинка текущего кадра
// 1.3) картинка визуализирующая маску "похож ли пиксель текущего кадра на эталонный фон"
// 1.4) картинка визуализирующая эту маску после применения волшебства морфологии
// 1.5) картинка визуализирующая эту маску после применения волшебства СНМ (системы непересекающихся множеств)
// 2) сохраняйте эти картинки визуализации только для тех кадров, когда пользователем был нажат пробел (код 32)
// 3) попробуйте добавить с помощью нажатия каких то двух кнопок "усиление/ослабление подавления фона"
// 4) попробуйте поменять местами морфологию и СНМ
// 5) попробуйте добавить настройку параметров морфологии и СНМ по нажатию кнопок (и выводите их значения в консоль)

struct MyVideoContent {
//    MyVideoContent() {
//
//    }

    MyVideoContent(int a) : set(set) {
        DisjointSet set(a);
    }

    std::vector<std::vector<int>> pix;
    cv::Mat frame;
    cv::Mat ans;
    cv::Mat fon;
    cv::Mat frame1;
    cv::Mat mat;
    DisjointSet set;
    std::vector<std::vector<int>> mas;
    std::vector<std::vector<int>> vasya;
    std::vector<std::vector<int>> snm;
    int lastClickX = 0;
    int lastClickY = 0;
    int ret = 10, r = 10;
    bool kaka = false;
    bool pack = false, dil = false, er = false, diller = false, elrond = false;

    void Set(int a){
        switch (a) {
            case 3:
                dil = true, er = false, diller = false, elrond = false;
                break;
            case 4:
                dil = false, er = true, diller = false, elrond = false;
                break;
            case 5:
                dil = false, er = false, diller = true, elrond = false;
                break;
            case 6:
                dil = false, er = false, diller = false, elrond = true;
                break;
            case 7:
                dil = false, er = false, diller = false, elrond = false;
                break;
            default:
                rassert(true, "error")
        }
    }

    void Click(int x, int y){
        lastClickX = x;
        lastClickY = y;
    }

    void setF(cv::Mat qwerty){
        frame1 = qwerty;
    }

    void SetFon(cv::Mat fon1){
        fon = fon1;
    }

    cv::Mat Paint(std::vector<std::vector<int>> q){
        for (int i = 0; i < q.size(); ++i) {
            if (kaka) {
                frame.at<cv::Vec3b>(q[i][1], q[i][0]) = cv::Vec3b(255, 255, 0);
            }
            else{
                frame.at<cv::Vec3b>(q[i][1], q[i][0]) = cv::Vec3b(0, 0, 255);
            }
        }
        if (kaka){
            return invertImageColors(frame);
        }
        else{
            return frame;
        }
    }

    cv::Mat Paint1(){
        rassert(!frame1.empty(), 123);
        for (int i = 0; i < pix.size(); ++i) {
            if (kaka) {
                frame = rast1(frame.clone(),frame1.clone(),pix[i]);
            }
        }
        return frame;
    }

    cv::Mat Paint2(){
        rassert(!frame1.empty(), 123);
        rassert(!fon.empty(), 123);
        frame = rast2(frame,frame1,fon);
        return frame;
    }

    cv::Mat Paint3(){
        rassert(!frame1.empty(), 123);
        rassert(!fon.empty(), 123);
        rassert(mat.rows == frame.rows, "123431234314")
        rassert(mat.cols == frame.cols, "ПАРАПАПАРА2")
        return ans;
    }

    cv::Mat Paint4(){

    }
    void Dudu(){
        cv::Vec3b color = frame.at<cv::Vec3b>(13, 5);
        cv::Vec3b colorf = fon.at<cv::Vec3b>(13, 5);
        for (int i = 0; i < mas.size(); ++i) {
            for (int j = 0; j < mas[i].size(); j++) {
                color = frame.at<cv::Vec3b>(j, i);
                colorf = fon.at<cv::Vec3b>(j, i);
                if (((int) color[0] < (int)colorf[0]+ret && (int) color[1] < (int)colorf[1]+ret && (int) color[2] < (int)colorf[2]+ret)&&((int) color[0] > (int)colorf[0]-ret && (int) color[1] > (int)colorf[1]-ret && (int) color[2] > (int)colorf[2]-ret)){
                    mas[i][j] = 1;
                }
            }
        }
        int n = 0;
        for (int i = 0; i < mas.size(); ++i) {
            for (int j = 0; j < mas[i].size(); j++) {
                n = j%mat.rows + i * mat.cols;
                if (i < mas.size()-1){
                    if (j < mas[i].size()-1){
                        if (mas[i][j] == mas[i+1][j]){
                            set.union_sets(n,n+1);
                        }
                        if (mas[i][j] == mas[i][j+1]){
                            set.union_sets(n,j%mat.rows + (i+1) * mat.cols);
                        }
                    }
                }
            }
        }
        vasya = mas;
        ans = frame.clone();
        if (dil){
            mas = Dilate(mas, r);
        }
        if (er){
            mas = Erode(mas, r);
        }
        if (diller){
            mas = Dilate(mas, r);
            mas = Erode(mas, r);
        }
        if (elrond){
            mas = Erode(mas, r);
            mas = Dilate(mas, r);
        }
//        std::cout << 1;
        for (int i = 0; i < mas.size(); ++i) {
            for (int j = 0; j < mas[i].size(); j++) {
                if (mas[i][j] == 1){
                    ans.at<cv::Vec3b>(j,i) = frame1.at<cv::Vec3b>(j,i);
                    mas[i][j] = 0;
                    snm[i][j] = j%mat.rows + i * mat.cols;
                }
            }
        }
    }

    void Mat(){
        std::vector<int> q;
        q.resize(mat.rows);
//        std::cout << q.size() <<  std::endl;
        for (int i = 0; i < mat.cols; ++i) {
            for (int j = 0; j < mat.rows; j++) {
                q[j] = 0;
            }
            mas.push_back(q);
        }
//        std::cout << mas.size() << " _ " << mat.cols << " _ " << frame.cols <<  std::endl;
    }

    std::vector<int> Get(){
        std::vector<int> a;
//        std::cout << "Left click at x=" << lastClickX << ", y=" << lastClickY << std::endl;
        a.push_back(lastClickX);
        a.push_back(lastClickY);
        return a;
    }

    void Dpix(std::vector<int> a){
        pix.push_back(a);
    }

    void Dokaka(){
        if (kaka){
            kaka = false;
        }
        else{
            kaka = true;
        }
    }

    cv::Mat Vis(){
        bool a = false;
        for (int i = 0; i < mat.cols; ++i) {
            for (int j = 0; j < mat.rows; j++) {
                if (vasya[i][j] == 1){
                    a = true;
                    mat.at<cv::Vec3b>(j,i) = cv::Vec3b(255, 255, 255);
                }
                else{
                    mat.at<cv::Vec3b>(j,i) = cv::Vec3b(0, 0, 0);
                }
            }
        }
        if (a){
            std::cout << 1;
        }
        return mat;
    }

    void Setset() {
        set = DisjointSet(frame.rows * frame.cols);
    }
};



void onMouseClick(int event, int x, int y, int flags, void *pointerToMyVideoContent) {
    MyVideoContent &content = *((MyVideoContent*) pointerToMyVideoContent);
    // не обращайте внимание на предыдущую строку, главное что важно заметить:
    // content.frame - доступ к тому кадру что был только что отображен на экране
    // content.lastClickX - переменная которая вам тоже наверняка пригодится
    // вы можете добавить своих переменных в структурку выше (считайте что это описание объекта из ООП, т.к. почти полноценный класс)

    cv::Vec3b color;
    std::vector<int> b;
    b.push_back(0);
    b.push_back(0);
    b.push_back(0);
    if (event == cv::EVENT_LBUTTONDOWN) { // если нажата левая кнопка мыши
//        std::cout << "Left click at x=" << x << ", y=" << y << std::endl;
        content.pack = true;
        std::vector<int> a = content.Get();
        color = content.frame.at<cv::Vec3b>(a[1],a[0]);
        b[0] = (int)color[0];
        b[1] = (int)color[1];
        b[2] = (int)color[2];
//        std::cout << b[0] << " " << b[1] << " " << b[2] << std::endl;
        content.Dpix(b);
        content.Click(x,y);
    }

    if (event == cv::EVENT_RBUTTONDOWN){
        content.Dokaka();
    }
}

void backgroundMagickStreaming() {
    bool big = false, small = false, a = false;
    cv::VideoCapture video(0);
    rassert(video.isOpened(), 3423948392481);

    MyVideoContent content(5);
    std::vector<std::vector<int>> mas;
    cv::Mat Foto;
    int q = 0;
    bool isSuccess = false;
    while (true) {
        isSuccess = video.read(content.frame);
        cv::imshow("video", content.frame);
        int k = cv::waitKey(10);
        if (k == 32 || k == 27) {
            content.SetFon(content.frame.clone());
            break;
        }
    }
    while (true) {
        isSuccess = video.read(content.frame);

        rassert(isSuccess, 348792347819);
        rassert(!content.frame.empty(), 3452314124643);

        if (q == 0) {
            content.setF(baba(cv::imread("lesson03/data/castle_large.jpg"), content.frame.clone()));
            q++;
            content.mat = content.frame;
            content.Mat();
            content.snm = content.mas;
            for (int i = 0; i < content.mat.cols; ++i) {
                for (int j = 0; j < content.mat.rows; j++) {
                    content.snm[i][j] = j%content.mat.rows + i * content.mat.cols;
                }
            }
            content.Setset();
            DisjointSet set1(content.frame.rows*content.frame.cols);
            content.set = set1;
        }
        content.Dudu();

        if (big) {
            cv::imshow("video", content.frame1); // покаызваем очередной кадр в окошке
        } else if (small) {
            cv::imshow("video", content.Paint2()); // покаызваем очередной кадр в окошке
        } else if (a) {
            cv::imshow("video", content.Paint3()); // покаызваем очередной кадр в окошке
        } else {
            cv::imshow("video", content.Paint1()); // покаызваем очередной кадр в окошке
        }
        cv::setMouseCallback("video", onMouseClick, &content); // делаем так чтобы функция выше (onMouseClick) получала оповещение при каждом клике мышкой
        int key = cv::waitKey(10);
        std::string resultsDir = "lesson04/resultsData/";
        if (key == 0) {
            if (big) {
                big = false;
            } else {
                big = true;
            }
        }else if (key == 32){
            if (!std::filesystem::exists(resultsDir)) { // если папка еще не создана
                std::filesystem::create_directory(resultsDir); // то создаем ее
            }
            cv::imwrite(resultsDir + "01_Fon.jpg", content.fon);
            cv::imwrite(resultsDir + "02_Cum.jpg", content.frame);
            cv::imwrite(resultsDir + "03_Mask.jpg", content.Vis());
            content.vasya = Dilate(content.vasya, content.r);
            content.vasya = Erode(content.vasya, content.r);
            cv::imwrite(resultsDir + "04_Eelon.jpg", content.Vis());
        }else if (key == 49) {
            if (small) {
                small = false;
            } else {
                small = true;
            }
        } else if (key == 50) {
            if (a) {
                a = false;
            } else {
                a = true;
            }
        } else if (key > 50 && key < 56) {
            content.Set(key - 48);
        } else if (key == 61) {
            content.r++;
        } else if (key == 45) {
            content.r--;
        } else if (key == 48) {
            content.ret++;
        } else if (key == 57) {
            content.ret--;
        }
        if (key == 27) {
            break;
        }
    }
}



int main() {
    try {
//        testingMyDisjointSets();
        backgroundMagickStreaming();
        return 0;
    } catch (const std::exception &e) {
        std::cout << "Exception! " << e.what() << std::endl;
        return 1;
    }
}