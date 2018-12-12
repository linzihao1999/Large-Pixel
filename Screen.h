#ifndef TEMP_SCREEN_H
#define TEMP_SCREEN_H

#include "ConstNum.h"

class Screen {
public:
    Screen(int argc, char **argv);

    void Init();

    void Run();

    static void SetColor(int x, int y, float r, float g, float b);

    void SetDemo();

    static void DisPlayFcn();

    static void ChangeSizeFcn(int, int);

    static void MouseFcn(int, int, int, int);

    static void MotionFcn(int, int);

    static void LineBresenham(int, int);

    static void Ellips(int, int);

    static int blockSize_x, blockSize_y;
    static float blockColor[WINDOWS_SIZE_X][WINDOWS_SIZE_Y][3];
    static float tcolor[WINDOWS_SIZE_X][WINDOWS_SIZE_Y][3];
    static int NowSizex, NowSizey;
    static int mouseClickOn_x, mouseClickOn_y;
};


#endif
