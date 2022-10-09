/*
 * Meu Primeiro Programa: xxx.cpp
 * <NomeCompleto>, RA <RA>, data DD/MM/AAAA
 */

#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>
#include <unistd.h> // needed to sleep

/* ASCII code for the escape key. */
#define ESCAPE 27

/* The number of our GLUT window */
int window;
int i;
double angle;

void display(void)
{
    /* clear all pixels  */
    glClear(GL_COLOR_BUFFER_BIT);

    /* draw white polygon (rectangle) with corners at
     * (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)
     */
    glColor3f(1.0, 1.0, 1.0);
    GLdouble PI = 3.1415926535897;
    GLint circle_points = 1000;
    glBegin(GL_LINE_LOOP);
    for (i = 0; i < circle_points; i++)
    {
        angle = 2 * PI * i / circle_points;
        glVertex2f(cos(angle), sin(angle));
    }
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    circle_points = 6;
    for (i = 0; i < circle_points; i++)
    {
        angle = 2 * PI * i / circle_points;
        glVertex2f(cos(angle), sin(angle));
    }
    glEnd();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(0.0f, 1.1f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f(-0.63f, -0.63f, 0.0f);
    glVertex3f(0.63f, -0.63f, 0.0f);
    glVertex3f(0.63f, 0.63f, 0.0f);
    glVertex3f(-0.63f, 0.63f, 0.0f);
    glEnd();

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(0.0f, 0.5f, 1.0f);
    glBegin(GL_POLYGON);
    circle_points = 1000;
    for (i = 0; i < circle_points; i++)
    {
        angle = 2 * PI * i / circle_points;
        glVertex2f(cos(angle) * 0.63, sin(angle) * 0.63);
    }

    glEnd();

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex3f(-0.45f, -0.45f, 0.0f);
    glVertex3f(0.45f, -0.45f, 0.0f);
    glVertex3f(-0.45f, 0.45f, 0.0f);
    glEnd();

    /* don't wait!
     * start processing buffered OpenGL routines
     */
    glFlush();
}

void init(void)
{
    /* select clearing color     */
    glClearColor(0.0, 0.0, 0.0, 0.0);

    /* initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 0.0, 0.0, 0.0, -5.0, 0.0);
}

/*
 * Declare initial window size, position, and display mode
 * (single buffer and RGBA).  Open window with "hello"
 * in its title bar.  Call initialization routines.
 * Register callback function to display graphics.
 * Enter main loop and process events.
 */
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bruno Nascimento");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0; /* ANSI C requires main to return int. */
}
