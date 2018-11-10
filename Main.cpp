#include <iostream>
#include "Screen.h"
#include "ConstNum.h"

int main(int argc, char **argv) {
    Screen a(argc, argv);
    a.Init();
    a.SetDemo();
    a.Run();
    return 0;
}