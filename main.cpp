#include <GL/glut.h>
#include <cmath>
#include <stdlib.h>
#include <iostream>
//#include <GLUT/glut.h>

using namespace std;

struct Point {
	GLint x;
	GLint y;
};

struct Color {
	GLfloat r;
	GLfloat g;
	GLfloat b;
};

void render(void);

void keyboard(unsigned char c, int x, int y);

void mouse(int button, int state, int x, int y);

const float r = 1.0;
const float g = 1.0;
const float b = 1.0;
const float DEG2RAD = 3.14159/180;
const float scaleconst  = 0.002;
const float dx = -400;
const float dy = 400;

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
}

Color getPixelColor(GLint x, GLint y) {
	Color color;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
	return color;
}

void setPixelColor(GLint x, GLint y, Color color) {
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void floodFill(GLint x, GLint y, Color borderColor, Color newColor) {
	Color color;
	color = getPixelColor(x, y);
	cout << "flood ";

	if(color.r != borderColor.r && color.g != borderColor.g && color.b != borderColor.b)
	{
	    cout << "is ";
		setPixelColor(x, y, newColor);
		floodFill(x+1, y, borderColor, newColor);
		floodFill(x, y+1, borderColor, newColor);
		floodFill(x-1, y, borderColor, newColor);
		floodFill(x, y-1, borderColor, newColor);
	}
	cout << "done" << endl;
	return;
}

void DrawCircle(float cx, float cy, float r, int num_segments, int begindraw, int enddraw)
{
    cout << "air besar anda";
    glBegin(GL_LINE_STRIP);
    for(int ii = begindraw; ii < min(enddraw, num_segments); ii++)
    {
        float theta = 2.0 * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx + dx, y + cy + dy);//output vertex
        glColor3f(r, g, b);
    }
    glEnd();
    cout << " baunya tidak sedap" << endl;
}

void DrawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINE_STRIP);
    glVertex2f(x1 + dx, y1 + dy);
    glVertex2f(x2 + dx, y2 + dy);
    glColor3f(r, g, b);
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
    DrawCircle(79, -265, 86.5, 1000, 140, 400);
    DrawCircle(151, -232, 41, 1000, -80, 355);
    DrawCircle(224, -275, 46, 1000, -50, 400);

    // Sayap kanan belakang
    DrawCircle(405, -293, 109/2, 1000, 170, 505);
    DrawCircle(477, -244, 99/2, 1000, 225, 500);
    DrawCircle(539, -255, 161/2, 1000, 120, 380);

    // Selangkangan
    DrawCircle(308, -320, 104/2, 1000, 100, 190); // selangkangan kiri
    DrawCircle(308, -320, 104/2, 1000, 310, 390); // selangkangan kanan

    // Ekor
    DrawLine(287, -273, 301, -501);
    DrawLine(301, -501, 286, -501);
    DrawLine(286, -501, 304, -545);
    DrawLine(304, -545, 326, -501);
    DrawLine(326, -501, 309, -501);
    DrawLine(309, -501, 330, -273);

    // Pundak
    DrawCircle(308, -35, 218/2, 1000, 630, 715);
    DrawCircle(308, -35, 218/2, 1000, 783, 855);

    // Leher
    DrawLine(283, -139, 294, -98);
    DrawLine(294, -98, 296, -58);
    DrawLine(294, -98, 296, -58);
    DrawLine(296, -58, 285, -76);
    DrawLine(285, -76, 302, -9);
    DrawLine(302, -9, 314, -9);
    DrawLine(314, -9, 329, -71);
    DrawLine(329, -71, 321, -56);
    DrawLine(321, -56, 320, -106);
    DrawLine(320, -106, 331, -145);
}

/* =========================================*/
/*                   MAIN                   */
/* =========================================*/

void render(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    //=> SCALE
    glScalef(scaleconst, scaleconst, scaleconst);

    //=> SHAPES
    DrawDragon();

    Color bordercolor = {r,g,b};
    Color fillcolor = {r,g,b};
    //floodFill(0.0, 0.0, bordercolor, fillcolor);

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






