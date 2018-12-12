#ifndef TEMP_SCREEN_H
#define TEMP_SCREEN_H

#include "ConstNum.h"
#include <iostream>

class Screen {
public:
    Screen(int argc, char **argv);

    void Init();

    void Run();

    static void ChangePixel(int x, int y, float r, float g, float b);

    void SetDemo();

    static void DisPlay();

    static void ChangeSize(int, int);

    static void MouseFcn(int, int, int, int);

    static void MotionFcn(int, int);

    static void LineBresenham(int, int);

    static int blockx, blocky;
    static float color[WINDOWS_SIZE_X][WINDOWS_SIZE_Y][3];
    static float tcolor[WINDOWS_SIZE_X][WINDOWS_SIZE_Y][3];
    static int NowSizex, NowSizey;
    static int mousex, mousey;
    std::pair<int, int> src_pos[N][M];
};


#endif
