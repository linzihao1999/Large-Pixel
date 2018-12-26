#ifndef TEMP_SCREEN_H
#define TEMP_SCREEN_H

#include "ConstNum.h"
#include <vector>
#include <iostream>
#include <set>

class R {
public:
    R(double x1, int y1, double k1) : startx(x1), maxy(y1), dm(k1) {}

    R(int x1, int y1) : x(x1), y(y1) {}

    double startx;
    int maxy;
    int x, y;
    double dm;

    bool operator<(const R &r) const {
        if (startx == r.startx)return maxy < r.maxy;
        return startx < r.startx;
    }
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

    void FillMode(bool f) {
        this->FILLMODE = f;
    }

    static int blockSize_x, blockSize_y;
    static float blockColor[WINDOWS_SIZE_X][WINDOWS_SIZE_Y][3];
    static float tColor[WINDOWS_SIZE_X][WINDOWS_SIZE_Y][3];
    static int nowSizex, nowSizey;
    static std::vector<R> points;
    static std::set<R> list;
private:
    bool FILLMODE;
};

#endif
