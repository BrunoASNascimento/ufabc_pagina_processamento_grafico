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

static int current_angle = 0, rotation = 0, n = 2, angular_velocity = 50, nuclear_rotation = 0;
static GLfloat spin = 0.0;
static int fotonAngle = 0;
static GLfloat photonPosition = 50.0;
static GLfloat photonPosition2 = 20.0;
static int showPhoton2 = 0;
static GLfloat diffuse1[] = {.0, .0, 0.0, 1.0};
static double RydbergConstant = 10973731.6;
static double waveLength = 0.0;

int randAngle()
{
    int min = 0;
    int max = 360;

    return rand() % (max - min + 1) + min;
}

// source https://stackoverflow.com/a/14917481
void waveLengthToRGB(double Wavelength) {
    double Gamma = 0.80;
    double IntensityMax = 255;
    double factor;
    double Red, Green, Blue;

    if((Wavelength >= 380) && (Wavelength < 440)) {
        Red = -(Wavelength - 440) / (440 - 380);
        Green = 0.0;
        Blue = 1.0;
    } else if((Wavelength >= 440) && (Wavelength < 490)) {
        Red = 0.0;
        Green = (Wavelength - 440) / (490 - 440);
        Blue = 1.0;
    } else if((Wavelength >= 490) && (Wavelength < 510)) {
        Red = 0.0;
        Green = 1.0;
        Blue = -(Wavelength - 510) / (510 - 490);
    } else if((Wavelength >= 510) && (Wavelength < 580)) {
        Red = (Wavelength - 510) / (580 - 510);
        Green = 1.0;
        Blue = 0.0;
    } else if((Wavelength >= 580) && (Wavelength < 645)) {
        Red = 1.0;
        Green = -(Wavelength - 645) / (645 - 580);
        Blue = 0.0;
    } else if((Wavelength >= 645) && (Wavelength < 781)) {
        Red = 1.0;
        Green = 0.0;
        Blue = 0.0;
    } else {
        Red = 0.0;
        Green = 0.0;
        Blue = 0.0;
    }

    // Let the intensity fall off near the vision limits
    if((Wavelength >= 380) && (Wavelength < 420)) {
        factor = 0.3 + 0.7 * (Wavelength - 380) / (420 - 380);
    } else if((Wavelength >= 420) && (Wavelength < 701)) {
        factor = 1.0;
    } else if((Wavelength >= 701) && (Wavelength < 781)) {
        factor = 0.3 + 0.7 * (780 - Wavelength) / (780 - 700);
    } else {
        factor = 0.0;
    }

    // Don't want 0^x = 1 for x <> 0
    diffuse1[0] = Red == 0.0 ? 0 : (IntensityMax * pow(Red * factor, Gamma)) / 255.0;
    diffuse1[1] = Green == 0.0 ? 0 : (IntensityMax * pow(Green * factor, Gamma)) / 255.0;
    diffuse1[2] = Blue == 0.0 ? 0 : (IntensityMax * pow(Blue * factor, Gamma)) / 255.0;
}

// source: https://openstax.org/books/university-physics-volume-3/pages/6-4-bohrs-model-of-the-hydrogen-atom
double balmerFormula(double ni, double nf) 
{
    return 1.0/(RydbergConstant*((1/(nf*nf))-(1/(ni*ni)))) * 10E8;
}

void init(void)
{
    GLfloat lmodel_ambient[] = {0.4, 0.4, 0.4, 1.0};
    GLfloat local_view[] = {0.0};

    glClearColor(0.0, 0.1, 0.1, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
    
    glEnable(GL_LIGHTING);

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

    GLfloat high_shininess[] = {100.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat position[] = {photonPosition, 0.0, .4, 1.0};

    glPushMatrix();
    glLightfv(GL_LIGHT1, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
    glRotated((GLdouble)fotonAngle, .0, .0, 1.0);
    glLightfv(GL_LIGHT1, GL_POSITION, position);
    glTranslated(photonPosition, 0.0, .4);
    glDisable(GL_LIGHTING);
    glColor3f(diffuse1[0], diffuse1[1], diffuse1[2]);
    glutSolidSphere(0.2, 10, 8); 
    glEnable(GL_LIGHTING);
    glPopMatrix();


    GLfloat position2[] = {photonPosition2, 0.0, .4, 1.0};
    GLfloat diffuse2[] = {.5, .5, .5, 1.0};

    if (showPhoton2 == 1) {
        glPushMatrix();
        glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse2);
        glRotated((GLdouble)fotonAngle, .0, .0, 1.0);
        glLightfv(GL_LIGHT0, GL_POSITION, position2);
        glTranslated(photonPosition2, 0.0, .4);
        glDisable(GL_LIGHTING);
        glColor3f(1.0, 1.0, 1.0);
        glutSolidSphere(0.2, 10, 8); 
        glEnable(GL_LIGHTING);
        glPopMatrix();
    }

    GLfloat sphere_mat_specular[] = {.5, .5, .5, 1.0};
    glColor3f(1.0, 1.0, 1.0);
    glMaterialfv(GL_FRONT, GL_SPECULAR, sphere_mat_specular);
    glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0, 0.0, -250.0);
    glutSolidSphere(250, 50, 50);
    glEnd();
    glTranslatef(0.0, 0.0, 250.0);

    glDisable(GL_LIGHTING);

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
    glTranslatef(.4 * (n * n), 0.5, 0.0);            // eletron location
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
    char waveLenStr[30];

    sprintf(energyStr, "Nivel de energia(n): %d", n);
    printText(-16, -12, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, energyStr);

    sprintf(waveLenStr, "Comprimento de onda: %0.2f nm", waveLength);
    printText(-16, -14, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, (char *)waveLenStr);

    printText(-16, -16, 1, 1, 1, GLUT_BITMAP_HELVETICA_12, (char *)"Use o teclado numerico, W/S ou CIMA/BAIXO para alterar nivel de energia");
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
    photonPosition = photonPosition + .5;
    if (photonPosition > 20.0)
    {
        glDisable(GL_LIGHT1);
    }

    photonPosition2 = photonPosition2 - .5;
    if (photonPosition2 < .5)
    {
        photonPosition2 = 20.0;
        showPhoton2 = 0;
        glDisable(GL_LIGHT0);
    }

    // Redesenha o quadrado com as novas coordenadas
    glutPostRedisplay();
    glutTimerFunc(33, Timer, 1);
}

void emitPhoton(int ni, int nf) {
    waveLength = balmerFormula(ni, nf);
    waveLengthToRGB(waveLength);
    glDisable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    photonPosition = 1.0;
}

void setOrbital(int x)
{
    if (x > 0 && x < 7)
    {
        fotonAngle = randAngle();
        if (x < n) {
            emitPhoton(n, x);
        }

        if (x > n) {
            showPhoton2 = 1;
            glEnable(GL_LIGHT0);
        }
        
        n = x;
    }
}

void increaseOrbital()
{
    if (n < 6)
    {
        setOrbital(n + 1);
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
