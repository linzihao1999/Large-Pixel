#ifndef TEMP_SCREEN_H
#define TEMP_SCREEN_H

#include "ConstNum.h"
#include <vector>
#include <iostream>

class R {
public:
    R(int y1, int x1, double k1 = 0) : y(y1), x(x1), k(k1) {}

    int y, x;
    double k;
};

class Screen {
public:
    Screen() = default;

    Screen(int argc, char **argv);

    void Init();

    void Run();

    static void SetColor(int x, int y, float r, float g, float b);

    void SetDemo();

    static void DisPlayFcn();

    static void ChangeSizeFcn(int, int);

    static void MouseFcn(int, int, int, int);

    static void MotionFcn(int, int);

    static void LineBresenham(int, int, int, int);

    static void Fill();

    static int blockSize_x, blockSize_y;
    static float blockColor[WINDOWS_SIZE_X][WINDOWS_SIZE_Y][3];
    static float tcolor[WINDOWS_SIZE_X][WINDOWS_SIZE_Y][3];
    static int NowSizex, NowSizey;
    static int mouseClickOn_x, mouseClickOn_y;
    static std::vector<R> points;
};

#endif
