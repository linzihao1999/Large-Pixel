#include <iostream>
#include "Screen.h"
#include "ConstNum.h"

int main(int argc, char **argv) {
    Screen screen(argc, argv);
    screen.Init();
    for (int i = 0; i < WINDOWS_SIZE_X; i += Screen::blockSize_x) {
        for (int j = 0; j < WINDOWS_SIZE_Y; j += Screen::blockSize_y) {
            for (int k = 0; k < 3; k++)
                Screen::blockColor[i][j][k] = 1;
        }
    }
    screen.Run();
    return 0;
}