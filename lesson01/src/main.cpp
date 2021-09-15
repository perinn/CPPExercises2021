#include <iostream> // таким образом подключаются системные библиотеки (эта нужна для вывода в консоль)
#include <vector> // подключаем библиотеку для поддержки вектора (массива динамического размера)

// таким образом подключаются наши функции
#include "simple_sum.h"
#include "some_math.h"

int main() {
    // таким образом выводятся сообщения в консоль
    // std::cout = "standard console output" = поток информации в консоль
    // std::endl = "standard end of line" = конец строчки (то же что и "\n")
    std::cout << "Hello World!" << std::endl;

    int a = 10;
    std::cout << "Please enter b=";
    int b;
    std::cin >> b; // считываем из консоли переменную
    std::cout << "b=" << b << std::endl;

    // TODO 01 чтобы телепортироваться внутрь функции - попробуйте удерживая CTRL кликнуть мышкой по функции, например по sum (она засветится как портал)
    int res = sum(a, b);

    std::cout << "a+b=" << a << "+" << b << "=" << res << std::endl;

    // TODO 06 выведите в консоль чему равно fibbonachiFast(b), не забудьте что нужно добавить не хватающий инклюд - some_math.h в которой объявлена эта функция
    std::cout << "fib(b)=" << fibbonachiFast(b) << std::endl;

    std::vector<double> values;
    std::cout << "values size: " << values.size() << std::endl;
    values.push_back(10);
    std::cout << "values size after push_back: " << values.size() << std::endl;
    values.push_back(20);
    values.push_back(35);
    values.push_back(4);
    std::cout << "values size after more push_back: " << values.size() << std::endl;

    // TODO 07 выведите в консоль каждый элемент из динамического массива
    for (int i = 0; i < values.size(); ++i) {
        std::cout << values[i] << std::endl;
    }

    // TODO 08 считывайте числа из консоли (и добавляйте их в вектор) до тех пор пока не будет введен ноль, после чего просуммируйте считанные числа и выведите сумму
    while (true) {
         double x;
         std::cin >> x;
         if (x==0) {
             break;
         }
         else{
             values.push_back(x);
         }
     }

    double ans = 0;
    for(double i : values){
        ans += i;
    }

    std::cout << "sum of values = " << ans << std::endl;

    return 0;
}
