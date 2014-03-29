/*
 * File:   main.cpp
 * Author: mohd
 *
 * Created on November 30, 2012, 7:17 PM
 */

#include <stdio.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "include/GL/freeglut.h"
#include "matrix.h"

#define NUM_POINTS   300000
/*
 *
 */

int width=1920, height=1080, SCALE=90;
std::vector<Vec2D> points;
std::vector< std::vector<double> > colors;

void computePoints(unsigned int npoints)
{
	colors.clear();
    points.clear();
    Vec2D point(0.,0.);
    MAT22 *transformations[4];
    int r, inx;
    double coeff[4][5]= {
                                {0.   ,0.   ,0.   ,0.16,0.},
                                {0.85 ,0.04 ,-0.04,0.85,1.6},
                                {0.20 ,-0.26,0.23 ,0.22,1.6},
                                {-0.15,0.28 ,0.26 ,0.24,0.44}
                        };
    double p[4] = {1,86,93,100};
    for ( unsigned int i = 0; i < 4; i++ )
        transformations[i]=new MAT22(coeff[i][0], coeff[i][1], coeff[i][2], coeff[i][3]);
    points.push_back(point);
	colors.push_back(std::vector<double>());
	colors[0].push_back(0);
	colors[0].push_back(0);
	colors[0].push_back(0);
    for ( unsigned int i = 0; i < npoints-1; i++ ){
        r=rand()%100;
        inx=3;
        for ( int j = 0; j < 4; j++ ){
            if ( r < p[j] ){
                inx=j;
                break;
            }
        }
        point=transformations[inx]->mulVector(point);
        point=point.add(Vec2D(0.,coeff[inx][4]));
        points.push_back(point);
		std::vector<double> scheme;
		scheme.push_back(abs(cos(point.x)+rand()%255/255.));
		scheme.push_back(0);
		scheme.push_back(abs(sin(point.y*point.x)+rand()%255/255.));
		colors.push_back(scheme);
    }
    for ( unsigned int i = 0; i < 4; i++ )
        delete transformations[i];
}

void setup()
{
	// we gonna do this in ortho
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-width/2., width/2., -height/2., height/2., -1.,1);
	glMatrixMode(GL_MODELVIEW);
}

void resize(int w, int h)
{
	width=w;
	height=h;
	setup();
	computePoints(NUM_POINTS);
}
void drawfern()
{
	glBegin(GL_POINTS);
	for ( int i = 0; i < points.size(); i++ ){
		glColor3f(colors[i][0], colors[i][1], colors[i][2]);
		glVertex2f(points[i].x*SCALE,points[i].y*SCALE);
	}
	glEnd();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.,1.,1.,1);
	glLoadIdentity();
	glColor3f(20/255.,107/255.,47/255.);
	glTranslatef(0,-400,0);
	drawfern();
	glutSwapBuffers();
}
void mouse(int x, int y)
{
}
void mousefunc(int button, int state, int x, int y)
{
}
void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'z':
	case 'Z':
		SCALE*=2;
		break;
	case 'x':
	case 'X':
		SCALE/=2;
		break;
	}
}
void update(int value)
{
	glutPostRedisplay();
	glutTimerFunc(15, update, 0);
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(width,height);
	glutCreateWindow("Fern");
	setup();
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutPassiveMotionFunc(mouse);
	glutMouseFunc(mousefunc);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(25, update, 0);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glPointSize(1);
	glutMainLoop();
    return 0;
}
