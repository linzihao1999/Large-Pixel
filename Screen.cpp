#include "Screen.h"
#include <GLUT/glut.h>
#include "ConstNum.h"
#include <cstdlib>
#include <iostream>

int Screen::blockx = 0;
int Screen::blocky = 0;
float Screen::color[WINDOWS_SIZE_X][WINDOWS_SIZE_Y][3] = {};
int Screen::NowSizex = 0;
int Screen::NowSizey = 0;
float Screen::ChangeRate = 0;

Screen::Screen(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(WINDOWS_POSITION_X, WINDOWS_SIZE_Y);
    glutInitWindowSize(WINDOWS_SIZE_X, WINDOWS_SIZE_Y);
    glutCreateWindow("Example");
}

void Screen::Init() {
    glClearColor(1.0, 1.0, 1.0, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, WINDOWS_SIZE_X, 0.0, WINDOWS_SIZE_Y);
    blockx = WINDOWS_SIZE_X / N;
    blocky = WINDOWS_SIZE_Y / M;
    NowSizex = WINDOWS_SIZE_X;
    NowSizey = WINDOWS_SIZE_Y;
}

void Screen::DisPlay() {
    glClear(GL_COLOR_BUFFER_BIT);
    for (int x = 0; x < WINDOWS_SIZE_X; x += blockx) {
        for (int y = 0; y < WINDOWS_SIZE_Y; y += blocky) {
            glColor3f(color[x][y][0], color[x][y][1], color[x][y][2]);
            //glColor3f((double) rand() / RAND_MAX, (double) rand() / RAND_MAX, (double) rand() / RAND_MAX);
            //glColor3f(1, 1, 1);
            glBegin(GL_POLYGON);
            glVertex2i(x, y);
            glVertex2i(x, y + blocky);
            glVertex2i(x + blockx, y + blocky);
            glVertex2i(x + blockx, y);
            glEnd();
        }
    }
    for (int x = 0; x < WINDOWS_SIZE_X; x += blockx) {
        for (int y = 0; y < WINDOWS_SIZE_Y; y += blocky) {
            glColor3f(0.0, 0.0, 0.0);
            glBegin(GL_LINE_LOOP);
            glVertex2i(x, y);
            glVertex2i(x, y + blocky);
            glVertex2i(x + blockx, y + blocky);
            glVertex2i(x + blockx, y);
            glEnd();
        }
    }
    glFlush();
    //glutPostRedisplay();
}

void Screen::Run() {
    glutDisplayFunc(DisPlay);
    glutReshapeFunc(ChangeSize);
    glutMouseFunc(MouseFcn);
    glutMainLoop();
}

void Screen::ChangePixel(int x, int y, float r, float g, float b) {
    x--;
    y--;
    color[x * blockx][y * blocky][0] = r;
    color[x * blockx][y * blocky][1] = g;
    color[x * blockx][y * blocky][2] = b;
}

void Screen::SetDemo() {
    int flag = 1;
    for (int i = 0; i < WINDOWS_SIZE_X; i += blockx) {
        flag ^= 1;
        for (int j = 0; j < WINDOWS_SIZE_Y; j += blocky) {
            if (flag) {
                color[i][j][0] = 0;
                color[i][j][1] = 0;
                color[i][j][2] = 1;
            } else {
                color[i][j][0] = 0;
                color[i][j][1] = 1;
                color[i][j][2] = 0;
            }
            flag ^= 1;
        }
    }
    ChangePixel(3, 2, 0.5, 0.5, 0.5);
}

void Screen::ChangeSize(int w, int h) {
    NowSizex = w;
    NowSizey = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (h == 0)
        h = 1;
    if (w > h) {
        gluOrtho2D(0.0, 1.0 * WINDOWS_SIZE_X * w / h, 0.0, WINDOWS_SIZE_Y);
    } else {
        gluOrtho2D(0.0, WINDOWS_SIZE_X, 0.0, 1.0 * WINDOWS_SIZE_Y * h / w);
    }
}

void Screen::MouseFcn(int button, int action, int xmouse, int ymouse) {
    float nowblock = (float) WINDOWS_SIZE_X / std::min(NowSizex, NowSizey) * blockx;
    if (action == GLUT_DOWN) {
        ymouse = NowSizey - ymouse;
        int changex = xmouse / nowblock, changey = ymouse / nowblock;
        ChangePixel(changex+1, changey+1, 0, 0, 0);
    }
    glutPostRedisplay();
}