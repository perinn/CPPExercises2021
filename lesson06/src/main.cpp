#include <filesystem>
#include <iostream>
#include <libutils/rasserts.h>

#include "blur.h" // TODO реализуйте функцию блюра с произвольной силой размытия в файле blur.cpp

void testSomeBlur(std::string name, double sigma) {
    // TODO выберите любую картинку и любую силу сглаживания - проверьте что результат - чуть размытая картинка
    // Входные картинки для тестирования возьмите из предыдущего урока (т.е. по пути lesson05/data/*).
    // Результирующие картинки сохарняйте в эту папку (т.е. по пути lesson06/resultsData/*).


    cv::Mat img = cv::imread("lesson05/data/" + name + ".jpg");
    std::string resultsDir = "lesson06/resultsData/";
    if (!std::filesystem::exists(resultsDir)) { // если папка еще не создана
        std::filesystem::create_directory(resultsDir); // то создаем ее
    }

    cv::Mat res_img = blur(img, sigma);
    cv::imwrite("lesson06/resultsData/" + name + "_" + std::to_string(sigma) + ".jpg", res_img);


}

void testManySigmas() {
    // TODO возьмите ту же самую картинку но теперь в цикле проведите сглаживание для нескольких разных сигм
    // при этом результирующую картинку сохраняйте с указанием какая сигма использовалась:
    // для того чтобы в название файла добавить значение этой переменной -
    // воспользуйтесь функцией преобразующей числа в строчки - std::to_string(sigma)
}

int main() {
    try {
        for(int sigma = 1; sigma <=10; sigma++){
            for (int i = 1; i <= 4; ++i) {
                testSomeBlur("line0" + std::to_string(i), sigma);
            }

            for (int i = 11; i <= 14; ++i) {
                // TODO сделайте вызов тестирования картинок line11.jpg - line14.jpg
                testSomeBlur("line" + std::to_string(i), sigma);
            }

            testSomeBlur("line21_water_horizont", sigma);
            testSomeBlur("multiline1_paper_on_table", sigma);
            testSomeBlur("multiline2_paper_on_table", sigma);

            testSomeBlur("valve", sigma);
        }
//        testManySigmas();

        return 0;
    } catch (const std::exception &e) {
        std::cout << "Exception! " << e.what() << std::endl;
        return 1;
    }
}

