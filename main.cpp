#include <GL/glut.h>
#include <cmath>
#include <stdlib.h>
#include <iostream>
//#include <GLUT/glut.h>

using namespace std;

void render(void);

void keyboard(unsigned char c, int x, int y);

void mouse(int button, int state, int x, int y);

const float r = 1.0;
const float g = 1.0;
const float b = 1.0;

const float dragon_r = 0.0;
const float dragon_g = 0.5;
const float dragon_b = 0.0;

const float border_r = 1.0;
const float border_g = 0.0;
const float border_b = 0.0;

const float breath_r = 1.0;
const float breath_g = 0.0;
const float breath_b = 0.0;

const float DEG2RAD = 3.14159/180;
const float scaleconst  = 0.002;

bool first = true;

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
}

void DrawFullCircle(float cx, float cy, float r, int num_segments, int begindraw, int enddraw, bool isBreath) {
    glBegin(GL_TRIANGLE_FAN);
    if (isBreath) {
        glColor3f(breath_r, breath_g, breath_b);
    } else {
        glColor3f(r, g, b);
    }
    for(int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0 * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(border_r, border_g, border_b);
    for(int ii = begindraw; ii < min(num_segments, enddraw); ii++)
    {
        float theta = 2.0 * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();
}

void DrawPartCircle(float cx, float cy, float r, int num_segments, int begindraw, int enddraw)
{
    cout << "air besar anda";
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(r, g, b);
    for(int ii = begindraw; ii < min(enddraw, num_segments); ii++)
    {
        float theta = 2.0 * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(border_r, border_g, border_b);
    for(int ii = begindraw; ii < min(enddraw, num_segments); ii++)
    {
        float theta = 2.0 * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();
    cout << " baunya tidak sedap" << endl;
}

void DrawRectangle(float x1, float y1, float x2, float y2) {
    glColor3f(r, g, b);
    glRectf(x1,y1,x2,y2);
}

void DrawPolygon(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);
    glEnd();

//    glBegin(GL_LINE_STRIP);
//    glColor3f(border_r, border_g, border_b);
//    glVertex2f(x1, y1);
//    glVertex2f(x2, y2);
//    glVertex2f(x3, y3);
//    glVertex2f(x4, y4);
//    glEnd();
}

void DrawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINE_STRIP);
    glColor3f(border_r, border_g, border_b);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void DrawDragon() {
    // Sayap kiri depan
    DrawLine(242, -120, 163, -79);
    DrawLine(163, -79, 110, -111);
    DrawLine(110,-111, 17, -193);
    DrawLine(17, -193, 8, -216);

    // Sayap kanan depan
    DrawLine(371, -122, 445, -77);
    DrawLine(445, -77, 511, -116);
    DrawLine(511, -116, 593, -189);
    DrawLine(593, -189, 608, -215);

    // Sayap kiri belakang
    DrawFullCircle(79, -265, 86.5, 1000, 140, 400, false);
    DrawFullCircle(151, -232, 41, 1000, -80, 355, false);
    DrawFullCircle(224, -275, 46, 1000, -50, 400, false);

    // Sayap kanan belakang
    DrawFullCircle(405, -293, 109/2, 1000, 170, 505, false);
    DrawFullCircle(477, -244, 99/2, 1000, 225, 500, false);
    DrawFullCircle(539, -255, 161/2, 1000, 120, 380, false);

    // Selangkangan
    DrawPartCircle(308, -320, 104/2, 1000, 100, 190); // selangkangan kiri
    DrawPartCircle(308, -320, 104/2, 1000, 310, 390); // selangkangan kanan

    // Ekor
    DrawLine(287, -273, 301, -501);
    DrawLine(301, -501, 286, -501);
    DrawLine(286, -501, 304, -545);
    DrawLine(304, -545, 326, -501);
    DrawLine(326, -501, 309, -501);
    DrawLine(309, -501, 330, -273);

    // Pundak
    DrawPartCircle(308, -35, 218/2, 1000, 630, 715);
    DrawPartCircle(308, -35, 218/2, 1000, 783, 855);

    // Leher
    DrawLine(283, -139, 294, -98);
    DrawLine(294, -98, 296, -58);
    DrawLine(294, -98, 296, -58);
    DrawLine(321, -56, 320, -106);
    DrawLine(320, -106, 331, -145);

    // Kepala
    DrawLine(296, -58, 285, -76);
    DrawLine(285, -76, 302, -9);
    DrawLine(302, -9, 314, -9);
    DrawLine(314, -9, 329, -71);
    DrawLine(329, -71, 321, -56);
}

DrawDragonFill() {
    glColor3f(dragon_r, dragon_g, dragon_b);
    glRectf(10000, 10000, -10000, -10000);
}

DrawDragonBreath() {
    float g1 = 0.01;
    float g = 0.09;
    float r = 1;
    for (int i = 50; i < 300; i += 5) {
        g = g - g * g1;
        r = r + r * g;
        DrawFullCircle(308, i, r, 1000, 0, 1000, true);
    }
    g = 0.01;
    for (int i = 300; i < 340; i += 5) {
        g = g + g * 40*g1;
        r = r - r * g;
        DrawFullCircle(308, i, r, 1000, 0, 1000, true);
    }
}

DrawLuarDragon() {
    //=> Border
    DrawRectangle(-10000, -10000, 0, 10000); //left
    DrawRectangle(10000, -10000, 619.5, 10000); //right
    DrawRectangle(-10000, 10000, 10000, -9); //top
    DrawRectangle(-10000, -10000, 10000, -545); //bottom

    //=> Bottom right
    DrawPolygon(304, -545, 326, -501, 630, -255, 620, -545);
    DrawPolygon(326, -501, 309, -501, 330, -273, 351, -290);
    DrawPolygon(351, -290, 326, -501, 620, -501, 620, -290);

    //=> Bottom left
    DrawPolygon(0,-300, 0, -545, 280, -545, 285, -300);
    DrawPolygon(0,-300, 0, -250, 250, -250, 250, -300);
    DrawPolygon(304, -545, 286, -501, 0, -200, 0, -545);
    DrawPolygon(286, -501, 301, -501, 287, -273, 0, -482);

    //=> Top left
    DrawPolygon(302, -9, 285, -76, 163, -79, 0, -9);
    DrawPolygon(17, -193, 8, -216, -100, -216, 17, 100);
    DrawPolygon(17, -193, 17, 100, 110, 100, 110, -111);
    DrawPolygon(110, 100, 110, -111, 163, -79, 163, 100);
    DrawPolygon(163, -79, 283, -139, 285, -76, 150, 100);
    DrawPolygon(239, -120, 283, -142, 242, 100, 285, 100);
    DrawPolygon(285, -76, 280, -98, 294, -98, 296, -58);
    DrawPolygon(294, -98, 283, -139, 250, -98, 101, -98);

    //=> Top right
    DrawPolygon(314, -9, 329, -71, 445, -77, 620, -9);
    DrawPolygon(329, -71, 445, -77, 371, -122, 372, -122);
    DrawPolygon(372, -123, 330, -142, 320, -100, 329, -71);
    DrawPolygon(329, -71, 321, -56, 321, -57, 320, -106);
    DrawPolygon(445, -77, 511, -116, 511, 100, 445, 100);
    DrawPolygon(511, -116, 593, -189, 593, 100, 511, 100);
    DrawPolygon(593, -189, 608, -215, 608, 100, 593, 100);
    DrawPolygon(608, -215, 608, 100, 630, 100, 630, -500);
}

/* =========================================*/
/*                   MAIN                   */
/* =========================================*/

void render(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    //=> SCALE
    if (first) {
        glScalef(scaleconst, scaleconst, scaleconst);
        glTranslatef(-300, 105, 0);
        first = false;
    }

    //=> SHAPES
    DrawDragonFill();
    DrawLuarDragon();
    DrawDragon();
    DrawDragonBreath();

    glutSwapBuffers();
}

int main (int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("DU RAH GHHHOOONN ZZZZZHHH");

    glutDisplayFunc(render);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    glutMainLoop();
}

void keyboard(unsigned char c, int x, int y) {
    if (c == 27) {
        exit(0);
    }
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON) {
        exit(0);
    }
}






