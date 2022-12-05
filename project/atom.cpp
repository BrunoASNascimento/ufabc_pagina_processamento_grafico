#define GL_SILENCE_DEPRECATION
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
/* MAC ONLY */
// #include <GLUT/glut.h> // MAC ONLY
// #include <iostream>    // MAC ONLY
/* LINUX ONLY */
#include <GL/gl.h> // LINUX ONLY
#include <GL/glu.h> // LINUX ONLY
#include <GL/glut.h> // LINUX ONLY

/* ASCII code for the escape key. */
#define ESCAPE 27

static int current_angle = 0, rotation = 0, n = 1, angular_velocity = 50, nuclear_rotation = 0;
static GLfloat spin = 0.0;
static int fotonAngle = 0;
static GLfloat fotonPosition = 50.0;

int randAngle()
{
    int min = 0;
    int max = 360;

    return rand() % (max - min + 1) + min;
}

void init(void)
{
    //    glClearColor(0.0, 0.0, 0.0, 0.0);
    // glShadeModel(GL_FLAT);
    GLfloat ambient[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat diffuse[] = {.2, .2, .2, 1.0};
    GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat position[] = {-4.0, 3.0, 2.0, 0.0};
    GLfloat lmodel_ambient[] = {0.4, 0.4, 0.4, 1.0};
    GLfloat local_view[] = {0.0};

    glClearColor(0.0, 0.1, 0.1, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

    GLfloat high_shininess[] = {100.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat diffuse1[] = {.0, .0, 1.0, 1.0};

    glLightfv(GL_LIGHT1, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
    // glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);

    // GLfloat lmodel_ambient[] = {0.4, 0.4, 0.4, 1.0};
    // glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glEnable(GL_COLOR_MATERIAL);
}

// source: https://stackoverflow.com/a/2185753
void printText(int x, int y, float r, float g, float b, void *font, char *string)
{
    glDisable(GL_LIGHTING);
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    int len, i;
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_ambient[] = {0.7, 0.7, 0.7, 1.0};
    GLfloat mat_ambient_color[] = {0.8, 0.8, 0.2, 1.0};
    GLfloat mat_diffuse[] = {0.1, 0.5, 0.8, 1.0};
    GLfloat mat_diffuse2[] = {0.8, 0.5, 0.1, 1.0};
    GLfloat mat_specular[] = {.5, .5, .5, 1.0};
    GLfloat no_shininess[] = {0.0};
    GLfloat low_shininess[] = {5.0};
    GLfloat high_shininess[] = {100.0};
    GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};

    GLfloat position[] = {fotonPosition, 0.0, .1, 1.0};
    GLfloat mat_shininess[] = {1.0};

    glPushMatrix();
    // glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    // glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT1, GL_POSITION, position);
    glRotated((GLdouble)fotonAngle, .0, .0, 1.0);
    glTranslated(fotonPosition, 0.0, .1);
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 1.0);
    //    glutWireCube (0.1);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    glColor3f(1.0, 1.0, 1.0);
    glNormal3f(0, 0, 1);
    //    glBegin(GL_QUADS);
    // glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, no_mat);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    // glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    // glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0, 0.0, -250.0);
    glutSolidSphere(250, 50, 50);

    glEnd();
    glTranslatef(0.0, 0.0, 250.0);

    glDisable(GL_LIGHTING);
    // glPushMatrix();
    // glTranslatef(-0.5, 0.2, -2.0f);
    // glutSolidCube (20.0);
    // glPopMatrix();

    glColor4f(1.0f, 0.0f, 0.0f, 0.0f); // Red
    glPushMatrix();
    glRotatef((GLfloat)nuclear_rotation, 0.0, 0.0, 1.0);
    glTranslatef(0.5, 0.0, 0.0);
    glutSolidSphere(0.5, 20, 16); // nuclear - proton

    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    glRotatef((GLfloat)nuclear_rotation, 0.0, 0.0, 1.0);
    glTranslatef(-0.5, 0.2, 0.0);
    glutSolidSphere(0.5, 20, 16); // nuclear - neutron

    glRotatef((GLfloat)current_angle, 0.0, 0.0, 1.0); // eletron rotation around the nuclear
    glTranslatef(1.9 * (n * n), 0.0, 0.0);            // eletron location
    glPushMatrix();                                   // push eletron system

    glRotatef((GLfloat)rotation, 0.0, 1.0, 0.0); // eletron spinn
    glRotatef(90 - 23.4, 1.0, 0.0, 0.0);         // eletron axis
    glColor4f(0.0f, 1.0f, 1.0f, 1.0f);           // light blue
    glutSolidSphere(0.1, 10, 8);                 // eletron
    glPopMatrix();
    glPopMatrix(); // pop eletron system

    printText(-5, 15, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, (char *)"MODELO DE BOHR");
    printText(-2, 14, 1, 1, 1, GLUT_BITMAP_HELVETICA_12, (char *)"Equipe Atomos");

    char energyStr[30];

    sprintf(energyStr, "Nivel de energia(n): %d", n);
    printText(-16, -14, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, energyStr);
    printText(-16, -16, 1, 1, 1, GLUT_BITMAP_HELVETICA_12, (char *)"W/S ou CIMA/BAIXO: Alterar nivel de energia");

    glEnable(GL_LIGHTING);

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120.0, (GLfloat)w / (GLfloat)h, 1.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

// Função callback chamada pela GLUT a cada intervalo de tempo
// (a window não está sendo redimensionada ou movida)
// source: https://www.inf.pucrs.br/~manssour/OpenGL/Animacao.html
void Timer(int value)
{
    current_angle = (current_angle + (angular_velocity / (n * n * n))) % 360;
    if (angular_velocity % 45 > 0)
    {
        nuclear_rotation = nuclear_rotation + angular_velocity % 45;
    }
    else
    {
        nuclear_rotation = nuclear_rotation * 0;
    }

    // foton
    fotonPosition = fotonPosition + .7;
    if (fotonPosition > 30.0)
    {
        glDisable(GL_LIGHT1);
    }

    // Redesenha o quadrado com as novas coordenadas
    glutPostRedisplay();
    glutTimerFunc(33, Timer, 1);
}

void increaseOrbital()
{
    if (n < 3)
    {
        n = n + 1;
    }
}

void setOrbital(int x)
{
    if (x > 0 && x < 7)
    {
        n = x;
        glEnable(GL_LIGHT1);
        fotonAngle = randAngle();
        fotonPosition = 1.9 * (n * n);
    }
}

void decreaseOrbital()
{
    if (n > 1)
    {
        setOrbital(n - 1);
    }
}



void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
    case 'W':
        increaseOrbital();
        break;
    case 's':
    case 'S':
        decreaseOrbital();
        break;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
        setOrbital(key - '0');
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

/*
 * Controlo das teclas especiais (Cursores, F1 a F12, etc...)
 */
void keyboard_callback_special(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        increaseOrbital();
        break;
    case GLUT_KEY_DOWN:
        decreaseOrbital();
        break;
    default:
        break;
    }

    return;
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 500);
    glutInitWindowPosition(100, 100);
    // glutCreateWindow(argv[0]);
    glutCreateWindow("MODELO DE BOHR");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboard_callback_special);
    glutTimerFunc(33, Timer, 1);
    glutMainLoop();
    return 0;
}
