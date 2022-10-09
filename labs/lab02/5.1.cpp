/*
 * Meu Primeiro Programa: xxx.cpp
 * <NomeCompleto>, RA <RA>, data DD/MM/AAAA
 */

#include <GL/glut.h>


// For MAC:
// #define GL_SILENCE_DEPRECATION
// #include <iostream>
// #include <stdlib.h>
// #include <math.h>
// #include <GLUT/glut.h>
// #include <unistd.h> // needed to sleep

/* ASCII code for the escape key. */
#define ESCAPE 27

/* The number of our GLUT window */
int window;

void display(void)
{
    /* clear all pixels  */
    glClear(GL_COLOR_BUFFER_BIT);

    /* draw white polygon (rectangle) with corners at
     * (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)
     */
    glBegin(GL_TRIANGLES);
        glColor3f(.89, 1.0, 1.0);
        glVertex3f(0.13, 0.73, 0.0); // p1
        glVertex3f(0.26, 0.33, 0.0); // p2
        glVertex3f(0.54, 0.61, 0.0); // p5

        glVertex3f(0.26, 0.33, 0.0); // p2
        glVertex3f(0.95, 0.42, 0.0); // p3
        glVertex3f(0.54, 0.61, 0.0); // p5

        glVertex3f(0.95, 0.42, 0.0); // p3
        glVertex3f(0.84, 0.88, 0.0); // p4
        glVertex3f(0.54, 0.61, 0.0); // p5
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
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
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
    glutInitWindowSize(250, 250);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Equipe Átomos");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0; /* ANSI C requires main to return int. */
}
