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
const float scaleconst  = 0.5;

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

        glVertex2f(x + cx, y + cy);//output vertex
        glColor3f(r, g, b);
    }
    glEnd();
    cout << " baunya tidak sedap" << endl;
}

void DrawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINE_STRIP);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glColor3f(r, g, b);
    glEnd();
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
    DrawCircle(0.0, 0.0, 0.2, 100, 0, 110);
    DrawLine(0.0, 1.0, 1.0, 0.0);

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
