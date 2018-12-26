#include <iostream>
#include "Screen.h"
#include "ConstNum.h"

int main(int argc, char **argv) {
    Screen screen(argc, argv);
    screen.Init();
    screen.FillMode(true);
    screen.Run();
    return 0;
}