#include "some_math.h"
#include <limits.h>
#include <float.h>
#include <math.h>


int fibbonachiRecursive(int n) {
    if (n==0){
        return 0;
    }
    if(n==1){
        return 1;
    }
    else{
        return fibbonachiRecursive(n-1)+ fibbonachiRecursive(n-2);
    }
    // TODO 03 реализуйте функцию которая считает числа Фибоначчи - https://ru.wikipedia.org/wiki/%D0%A7%D0%B8%D1%81%D0%BB%D0%B0_%D0%A4%D0%B8%D0%B1%D0%BE%D0%BD%D0%B0%D1%87%D1%87%D0%B8
    return 0;
}

int fibbonachiFast(int n) {
    std::vector<int> xs;
    xs.push_back(0);
    xs.push_back(1);
    if(n==0){
        return xs[0];
    }
    if(n==1){
        return xs[2];
    }
    else{
        for(int i =2; i <= n; i++){
            xs.push_back(xs[i-1]+xs[i-2]);
        }
    }
    return xs[n];

    // TODO 04 реализуйте быструю функцию Фибоначчи с использованием std::vector
    return 0;
}

double solveLinearAXB(double a, double b) {
    // TODO 10 решите линейное уравнение a*x+b=0 а если решения нет - верните наибольшее значение double - найдите как это сделать в интернете по запросу "so cpp double max value" (so = stackoverflow = сайт где часто можно найти ответы на такие простые запросы), главное НЕ КОПИРУЙТЕ ПРОСТО ЧИСЛО, ПОЖАЛУЙСТААаа
    // если решений сколь угодно много - верните максимальное значение со знаком минус
    if(a==0){
        if(b==0){
            return -1*DBL_MAX;
        }
        else{
            return DBL_MAX;
        }
    }

    else{
        return -b/a;
    }

    return 0;
}

std::vector<double> solveSquare(double a, double b, double c) {
    // TODO 20 решите квадратное уравнение вида a*x^2+b*x+c=0
    // если корня два - они должны быть упорядочены по возрастанию
    std::vector<double> results;
    // чтобы добавить в вектор элемент - нужно вызвать у него метод push_back:
    if(a!=0) {
        double D = b * b - 4 * a * c;
        if (D == 0) {
            results.push_back((-b) / (2 * a));
        }
        if (D > 0) {
            results.push_back((-b - sqrt(D)) / (2 * a));
            results.push_back((-b + sqrt(D)) / (2 * a));
        }
    }
    else{
        results.push_back(solveLinearAXB(b,c));
    }
    return results;
}
