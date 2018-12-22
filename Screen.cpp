#include "Screen.h"
#include <GLUT/glut.h>
#include "ConstNum.h"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>

int Screen::blockSize_x = 0;
int Screen::blockSize_y = 0;
float Screen::blockColor[WINDOWS_SIZE_X][WINDOWS_SIZE_Y][3] = {};
float Screen::tcolor[WINDOWS_SIZE_X][WINDOWS_SIZE_Y][3] = {};
int Screen::NowSizex = 0;
int Screen::NowSizey = 0;
int Screen::mouseClickOn_x = 0, Screen::mouseClickOn_y = 0;
std::vector<R> Screen::points = {};

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
    blockSize_x = WINDOWS_SIZE_X / N;
    blockSize_y = WINDOWS_SIZE_Y / M;
    NowSizex = WINDOWS_SIZE_X;
    NowSizey = WINDOWS_SIZE_Y;
}

void Screen::DisPlayFcn() {
    glClear(GL_COLOR_BUFFER_BIT);
    for (int x = 0; x < WINDOWS_SIZE_X; x += blockSize_x) {
        for (int y = 0; y < WINDOWS_SIZE_Y; y += blockSize_y) {
            glColor3f(blockColor[x][y][0], blockColor[x][y][1], blockColor[x][y][2]);
            //glColor3f((double) rand() / RAND_MAX, (double) rand() / RAND_MAX, (double) rand() / RAND_MAX);
            //glColor3f(1, 1, 1);
            glBegin(GL_POLYGON);
            glVertex2i(x, y);
            glVertex2i(x, y + blockSize_y);
            glVertex2i(x + blockSize_x, y + blockSize_y);
            glVertex2i(x + blockSize_x, y);
            glEnd();
        }
    }
    for (int x = 0; x < WINDOWS_SIZE_X; x += blockSize_x) {
        for (int y = 0; y < WINDOWS_SIZE_Y; y += blockSize_y) {
            glColor3f(0.0, 0.0, 0.0);
            glBegin(GL_LINE_LOOP);
            glVertex2i(x, y);
            glVertex2i(x, y + blockSize_y);
            glVertex2i(x + blockSize_x, y + blockSize_y);
            glVertex2i(x + blockSize_x, y);
            glEnd();
        }
    }
    glFlush();
    //glutPostRedisplay();
}

void Screen::Run() {
    glutDisplayFunc(DisPlayFcn);
    glutReshapeFunc(ChangeSizeFcn);
    glutMouseFunc(MouseFcn);
    //glutMotionFunc(MotionFcn);
    glutMainLoop();
}

void Screen::SetColor(int x, int y, float r, float g, float b) {
    x--;
    y--;
    blockColor[x * blockSize_x][y * blockSize_y][0] = r;
    blockColor[x * blockSize_x][y * blockSize_y][1] = g;
    blockColor[x * blockSize_x][y * blockSize_y][2] = b;
}

void Screen::SetDemo() {
    int flag = 1;
    for (int i = 0; i < WINDOWS_SIZE_X; i += blockSize_x) {
        flag ^= 1;
        for (int j = 0; j < WINDOWS_SIZE_Y; j += blockSize_y) {
            if (flag) {
                blockColor[i][j][0] = 1;
                blockColor[i][j][1] = 1;
                blockColor[i][j][2] = 1;
            } else {
                blockColor[i][j][0] = 1;
                blockColor[i][j][1] = 1;
                blockColor[i][j][2] = 1;
            }
            flag ^= 1;
        }
    }
    SetColor(3, 2, 0.5, 0.5, 0.5);
}

void Screen::ChangeSizeFcn(int w, int h) {
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
    float nowblock = (float) WINDOWS_SIZE_X / std::min(NowSizex, NowSizey) * blockSize_x;
    if (action == GLUT_DOWN) {
        for (int i = 0; i < WINDOWS_SIZE_X; i += blockSize_x)
            for (int j = 0; j < WINDOWS_SIZE_Y; j += blockSize_y)
                for (int k = 0; k < 3; k++)
                    blockColor[i][j][k] = 1;
        ymouse = NowSizey - ymouse;
        int changex = int(xmouse / nowblock) + 1, changey = int(ymouse / nowblock) + 1;
        points.emplace_back(changex, changey);
        Fill();
    }
    glutPostRedisplay();
}

void Screen::MotionFcn(int x, int y) {
    for (int i = 0; i < WINDOWS_SIZE_X; i++)
        for (int j = 0; j < WINDOWS_SIZE_Y; j++)
            for (int k = 0; k < 3; k++)
                blockColor[i][j][k] = tcolor[i][j][k];
    float nowblock = (float) WINDOWS_SIZE_X / std::min(NowSizex, NowSizey) * blockSize_x;
    y = NowSizey - y;
    int changex = int(x / nowblock) + 1, changey = int(y / nowblock) + 1;
    //std::cout << "L" << std::endl;
    //LineBresenham(changex, changey);
    //SetColor(changex + 1, changey + 1, 0, 0, 0);
    glutPostRedisplay();
}

void Screen::LineBresenham(int x0, int y0, int x1, int y1) {
    int x = x0, y = y0;
    if (x == x1) {
        if (y <= y1)while (y <= y1)SetColor(x, y++, 0, 0, 0);
        else while (y1 <= y)SetColor(x, y1++, 0, 0, 0);
        return;
    }
    if (y == y1) {
        if (x <= x1)while (x <= x1)SetColor(x++, y, 0, 0, 0);
        else while (x1 <= x)SetColor(x1++, y, 0, 0, 0);
        return;
    }
    if (x > x1) {
        std::swap(x, x1);
        std::swap(y, y1);
    }
    int dx = abs(x1 - x);
    int dy = abs(y1 - y);
    int twoDx = 2 * dx;
    int twoDy = 2 * dy;
    int twoDyMinusDx = 2 * (dy - dx);
    int twoDxMinusDy = 2 * (dx - dy);
    int p;
    double k = (double) (y1 - y) / (double) (x1 - x);
    if (fabs(k) <= 1) {
        SetColor(x, y, 0, 0, 0);
        p = 2 * dy - dx;
        while (x < x1) {
            if (p < 0) {
                p += twoDy;
            } else {
                if (k >= 0)
                    y++;
                else
                    y--;
                p += twoDyMinusDx;
            }
            SetColor(++x, y, 0, 0, 0);
        }
    } else {
        p = 2 * dx - dy;
        if (y > y1) {
            std::swap(y, y1);
            std::swap(x, x1);
        }
        SetColor(x, y, 0, 0, 0);
        while (y < y1) {
            if (p < 0) {
                p += twoDx;
            } else {
                if (k >= 0)
                    x++;
                else
                    x--;
                p += twoDxMinusDy;
            }
            SetColor(x, ++y, 0, 0, 0);
        }
    }
}

void Screen::Fill() {
    //std::cout << points[0].x << ' ' << points[0].y << std::endl;
    if (points.size() == 1) {
        SetColor(points[0].x, points[0].y, 0, 0, 0);
        return;
    }
    for (int i = 1; i < points.size(); i++) {
        LineBresenham(points[i - 1].x, points[i - 1].y,
                      points[i].x, points[i].y);
    }
    LineBresenham(points[points.size() - 1].x, points[points.size() - 1].y,
                  points[0].x, points[0].y);
    std::vector<R> edge[WINDOWS_SIZE_X];
    for (int i = 0; i < points.size(); i++) {
        auto last = points[i == 0 ? points.size() - 1 : i - 1];
        auto push = [&]() -> void {
            edge[points[i].y].emplace_back(last.y, points[i].x,
                                           (double) (last.x - points[i].x) / last.y - points[i].y);
        };
        if (points[i].x < last.x) push();
        last = points[i == points.size() - 1 ? 0 : i + 1];
        if (points[i].x < last.x) push();
    }
    std::set<R> list;
    for (int i = 0; i < WINDOWS_SIZE_X; i++) {
        if (edge[i].size() != 0) {
            std::sort(edge[i].begin(), edge[i].end(),
                      [](R A, R B) -> bool { return A.y < B.y; });
        }
        if (list.size() != 0) {
            int p = 0;
            auto last = list.begin(), it = list.begin();
            for (; it != list.begin(); ++it) {
                for (int j = last->x; j < it->x; j++) {
                    //SetColor();
                }
                last = it;
            }
        }
    }
}
