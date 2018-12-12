#include <iostream>
#include "Screen.h"
#include "ConstNum.h"

int main(int argc, char **argv) {
    Screen screen(argc, argv);
    screen.Init();
    /*for (int i = 0; i < WINDOWS_SIZE_X; i += Screen::blockx) {
        for (int j = 0; j < WINDOWS_SIZE_Y; j += Screen::blocky) {
            for (int k = 0; k < 3; k++)
                Screen::color[i][j][k] = 1;
        }
    }*/
    screen.SetDemo();
    screen.Run();
    return 0;
}