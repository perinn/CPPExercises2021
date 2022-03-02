#include <vector>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include <libutils/rasserts.h>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/types.hpp>


struct Edge {
    int u, v; // номера вершин которые это ребро соединяет
    int w; // длина ребра (т.е. насколько длинный путь предстоит преодолеть переходя по этому ребру между вершинами)

    Edge(int u, int v, int w) : u(u), v(v), w(w)
    {}
};

const int INF = std::numeric_limits<int>::max();

// Эта биективная функция по координате пикселя (строчка и столбик) + размерам картинки = выдает номер вершины
int encodeVertex(int row, int column, int nrows, int ncolumns) {
    rassert(row < nrows, 348723894723980017);
    rassert(column < ncolumns, 347823974239870018);
    int vertexId = row * ncolumns + column;
    return vertexId;
}

// Эта биективная функция по номеру вершины говорит какой пиксель этой вершине соовтетствует (эта функция должна быть симметрична предыдущей!)
cv::Point2i decodeVertex(int vertexId, int nrows, int ncolumns) {

    // TODO: придумайте как найти номер строки и столбика пикселю по номеру вершины (просто поймите предыдущую функцию и эта функция не будет казаться сложной)
    int row = vertexId/ncolumns;
    int column = vertexId%ncolumns;

    // сверим что функция симметрично сработала:
    rassert(encodeVertex(row, column, nrows, ncolumns) == vertexId, 34782974923035);

    rassert(row < nrows, 34723894720027);
    rassert(column < ncolumns, 3824598237592030);
    return cv::Point2i(column, row);
}

void run(int mazeNumber) {
    cv::Mat maze = cv::imread("lesson15/data/mazesImages/maze" + std::to_string(mazeNumber) + ".png");
    rassert(!maze.empty(), 324783479230019);
    rassert(maze.type() == CV_8UC3, 3447928472389020);
    std::cout << "Maze resolution: " << maze.cols << "x" << maze.rows << std::endl;

    int nvertices = maze.rows*maze.cols; // TODO

    std::vector<std::vector<Edge>> edges_by_vertex(nvertices);
    for (int j = 0; j < maze.rows; ++j) {
        for (int i = 0; i < maze.cols; ++i) {
            cv::Vec3b color = maze.at<cv::Vec3b>(j, i);
            unsigned char blue = color[0];
            unsigned char green = color[1];
            unsigned char red = color[2];

            int u = encodeVertex(j,i,maze.rows, maze.cols);
            int w = 1;
            if(j+1<maze.rows){
                int v = encodeVertex(j+1,i,maze.rows, maze.cols);
                cv::Vec3b color1 = maze.at<cv::Vec3b>(j+1, i);
                unsigned char blue1 = color1[0];
                unsigned char green1 = color1[1];
                unsigned char red1 = color1[2];
                w+=abs(blue-blue1)+abs(green-green1)+abs(red-red1);
                if(w>=42*3){w=INF;}
                else{w=1;}
                edges_by_vertex[u].push_back(Edge(u,v, w));
            }
            if(j-1>=0){
                int v = encodeVertex(j-1,i,maze.rows, maze.cols);
                cv::Vec3b color1 = maze.at<cv::Vec3b>(j-1, i);
                unsigned char blue1 = color1[0];
                unsigned char green1 = color1[1];
                unsigned char red1 = color1[2];
                w+=abs(blue-blue1)+abs(green-green1)+abs(red-red1);
                if(w>=42*3){w=INF;}
                else{w=1;}
                edges_by_vertex[u].push_back(Edge(u,v, w));
            }
            if(i+1<maze.cols){
                int v = encodeVertex(j,i+1,maze.rows, maze.cols);
                cv::Vec3b color1 = maze.at<cv::Vec3b>(j, i+1);
                unsigned char blue1 = color1[0];
                unsigned char green1 = color1[1];
                unsigned char red1 = color1[2];
                w+=abs(blue-blue1)+abs(green-green1)+abs(red-red1);
                if(w>=42*3){w=INF;}
                else{w=1;}
                edges_by_vertex[u].push_back(Edge(u,v, w));
            }
            if(i-1>=0){
                int v = encodeVertex(j,i-1,maze.rows, maze.cols);
                cv::Vec3b color1 = maze.at<cv::Vec3b>(j, i-1);
                unsigned char blue1 = color1[0];
                unsigned char green1 = color1[1];
                unsigned char red1 = color1[2];
                w+=abs(blue-blue1)+abs(green-green1)+abs(red-red1);
                if(w>=42*3){w=INF;}
                else{w=1;}
                edges_by_vertex[u].push_back(Edge(u,v, w));
            }

            // TODO добавьте соотвтетсвующие этому пикселю ребра
        }
    }

    int start, finish;
    if (mazeNumber >= 1 && mazeNumber <= 3) { // Первые три лабиринта очень похожи но кое чем отличаются...
        start = encodeVertex(300, 300, maze.rows, maze.cols);
        finish = encodeVertex(0, 305, maze.rows, maze.cols);
    } else if (mazeNumber == 4) {
        start = encodeVertex(154, 312, maze.rows, maze.cols);
        finish = encodeVertex(477, 312, maze.rows, maze.cols);
    } else if (mazeNumber == 5) { // Лабиринт в большом разрешении, добровольный (на случай если вы реализовали быструю Дейкстру с приоритетной очередью)
        start = encodeVertex(1200, 1200, maze.rows, maze.cols);
        finish = encodeVertex(1200, 1200, maze.rows, maze.cols);
    } else {
        rassert(false, 324289347238920081);
    }



    cv::Mat window = maze.clone(); // на этой картинке будем визуализировать до куда сейчас дошла прокладка маршрута

    std::vector<int> distances(nvertices, INF);
    distances[start] = 0;

    std::vector<bool> prg (nvertices, false);
    std::vector<int> back_step (nvertices, -1);

    int progress = 0;
    while (true) {

        int a = -1;
        int b = INF;
        for(int x = 0; x <= nvertices-1; x++){
            if(distances[x]<b && !prg[x]){
                a = x;
                b = distances[x];
            }
        }
        if(b == INF || a==finish){break;}

        for(int j = 0; j < edges_by_vertex[a].size(); j++){
            if(edges_by_vertex[a][j].w==INF){continue;}
            if(distances[edges_by_vertex[a][j].v] > distances[a]+edges_by_vertex[a][j].w){
                distances[edges_by_vertex[a][j].v] = distances[a]+edges_by_vertex[a][j].w;
                back_step[edges_by_vertex[a][j].v] = a;
            }
        }
        prg[a] = true;
        progress++;
        cv::Point2i p = decodeVertex(a, maze.rows, maze.cols);

        window.at<cv::Vec3b>(p.y, p.x) = cv::Vec3b(0, 255, 0);
        if(progress%100==0) {
            cv::imshow("Maze", window);
            cv::waitKey(1);
//            std::cout << (float)100*progress/prg.size()<<"%" <<std::endl;
        }

    }

    if (distances[finish]!=INF) {
        std::cout << "aboba!" << std::endl;
        int back_step0 = finish;
        std::vector<int> ans;
        while (back_step0 != -1) {
            cv::Point2i p = decodeVertex(back_step0, maze.rows, maze.cols);
            window.at<cv::Vec3b>(p.y, p.x) = cv::Vec3b(0, 0, 255);
            back_step0 = back_step[back_step0];
            cv::imshow("Maze", window);
            cv::waitKey(1);
        }
        cv::imwrite("lesson15/data/mazesImages/maze" + std::to_string(mazeNumber) + "_res00.png", window);
    }

    // TODO СКОПИРУЙТЕ СЮДА ДЕЙКСТРУ ИЗ ПРЕДЫДУЩЕГО ИСХОДНИКА

    // TODO в момент когда вершина становится обработанной - красьте ее на картинке window в зеленый цвет и показывайте картинку:
    //    cv::Point2i p = decodeVertex(the_chosen_one, maze.rows, maze.cols);
    //    window.at<cv::Vec3b>(p.y, p.x) = cv::Vec3b(0, 255, 0);
    //    cv::imshow("Maze", window);
    //    cv::waitKey(1);
    // TODO это может тормозить, в таком случае показывайте window только после обработки каждой сотой вершины

    // TODO обозначьте найденный маршрут красными пикселями

    // TODO сохраните картинку window на диск

    std::cout << "Finished!" << std::endl;

    // Показываем результат пока пользователь не насладиться до конца и не нажмет Escape
    while (cv::waitKey(10) != 27) {
        cv::imshow("Maze", window);
    }
}

int main() {
    try {
        int mazeNumber = 3;
        run(mazeNumber);

        return 0;
    } catch (const std::exception &e) {
        std::cout << "Exception! " << e.what() << std::endl;
        return 1;
    }
}
