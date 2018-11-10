#include "Screen.h"
#include <GLUT/glut.h>
#include "ConstNum.h"
#include <cstdlib>

int Screen::blockx = 0;
int Screen::blocky = 0;
float Screen::color[WINDOWS_SIZE_X][WINDOWS_SIZE_Y][3] = {};

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
}

void Screen::DisPlay() {
    glClear(GL_COLOR_BUFFER_BIT);
    for (int x = 0; x < WINDOWS_SIZE_X; x += blockx) {
        for (int y = 0; y < WINDOWS_SIZE_Y; y += blocky) {
            //glColor3f(color[x][y][0], color[x][y][1], color[x][y][2]);
            glColor3f((double) rand() / RAND_MAX, (double) rand() / RAND_MAX, (double) rand() / RAND_MAX);
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
}

void Screen::Run() {
    glutDisplayFunc(DisPlay);
    glutReshapeFunc(ChangeSize);
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
    ChangePixel(5, 5, 0.5, 0.5, 0.5);
}

void Screen::ChangeSize(int w, int h) {
    if (h == 0)
        h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h) {
        gluOrtho2D(0.0f, 300.0f, 300.0f * h / w, 0.0f);
    } else {
        gluOrtho2D(0.0f, 300.0f * w / h, 300.0f, 0.0f);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
