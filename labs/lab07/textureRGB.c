#define GL_SILENCE_DEPRECATION
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
/* MAC ONLY */
#include <GLUT/glut.h> // MAC ONLY
#include <iostream>    // MAC ONLY
/* LINUX ONLY */
//#include <GL/gl.h> // LINUX ONLY
//#include <GL/glu.h> // LINUX ONLY
//#include <GL/glut.h> // LINUX ONLY

/* ASCII code for the escape key. */
#define ESCAPE 27

/* Inclui o ficheiro com a textura */
#include "/Users/brunonascimento/developer/github.com/ufabc_processamento_grafico/lab_07/textureRGB.h"
//#include "textureRGB.h"

#define N_VERTICES 4
const GLfloat vertex_coords[N_VERTICES][3] = {
    {-0.5, -0.272, 0.289},
    {0.5, -0.272, 0.289},
    {0.0, -0.272, -0.577},
    {0.0, 0.544, 0.000}};

/* Tri�ngulos do objecto (v�rtices que os constituem) */
#define N_TRIANGLES 4
const GLuint triangles[N_TRIANGLES][3] = {
    {3, 0, 1},
    {3, 1, 2},
    {2, 0, 3},
    {0, 2, 1}};

/* Coordenadas de textura dos v�rices de cada tri�ngulo */
const GLfloat tex_coords[N_TRIANGLES][3][2] = {
    {{0.5, 0.000}, {0.0, 0.875}, {1.0, 0.875}},
    {{0.5, 0.000}, {0.0, 0.875}, {1.0, 0.875}},
    {{0.0, 0.875}, {1.0, 0.875}, {0.5, 0.000}},
    {{0.5, 0.000}, {1.0, 0.875}, {0.0, 0.875}}};

/* Vectores normais aos v�rtices do objecto: */
const GLfloat vertex_normals[N_VERTICES][3] = {
    {-0.81670904, -0.33290246, 0.47134089},
    {0.81670904, -0.33290252, 0.47134092},
    {0.00000000, -0.33331525, -0.94281548},
    {0.00000000, 1.00000000, -0.00019993}};

/**********************************************************************/
/*                        Declara��o de fun��es                       */
/**********************************************************************/
void init_glut(const char *window_name, int argc, char **argv);
void draw_object(void);
void display_callback(void);
void reshape_callback(int w, int h);
void animate_callback(void);
void keyboard_callback(unsigned char key, int x, int y);
void keyboard_callback_special(int key, int x, int y);
void menu_callback(int value);

/**********************************************************************/
/*                                                                    */
/*                       Fun��o principal (main)                      */
/*                                                                    */
/**********************************************************************/

int main(int argc, char **argv)
{

    /* inicia o GLUT e alguns par�metros do OpenGL */
    init_glut("Computa��o Gr�fica - Exemplo Texturas", argc, argv);

    /* fun��o de controlo do GLUT */
    glutMainLoop();

    return 0;
}

/**********************************************************************/
/*                                                                    */
/*                         Defini��o de fun��es                       */
/*                                                                    */
/**********************************************************************/

/*
 * inicia o GLUT e alguns par�metros do OpenGL
 */
void init_glut(const char *nome_janela, int argc, char **argv)
{
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {25.0};
    GLfloat light_position[] = {-1.0, 1.0, 1.0, 0.0};

    /* inicia o GLUT */
    glutInit(&argc, argv);

    /* inicia o display usando RGB e double-buffering */
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(nome_janela);

    /* define as func�es de callback */
    glutKeyboardFunc(keyboard_callback);
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutSpecialFunc(keyboard_callback_special);
    glutIdleFunc(animate_callback);

    /* define o menu */
    glutCreateMenu(menu_callback);
    glutAddMenuEntry("Desenhar a azul", 0);
    glutAddMenuEntry("Desenhar a verde", 1);
    glutAddMenuEntry("Desenhar a vermelho", 2);
    glutAddMenuEntry("Sair", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    /* Inicia a ilumina��o e as caracter�sticas gerais dos materiais */
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    /* Prepara a textura */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_WIDTH, TEXTURE_HEIGHT,
                 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glEnable(GL_TEXTURE_2D);

    /* Activa o modelo de sombreagem de "Gouraud". */
    glShadeModel(GL_SMOOTH);

    /* Activa o z-buffering, de modo a remover as superf�cies escondidas */
    glEnable(GL_DEPTH_TEST);

    /* Define a c�r de fundo (preto) e a cor de desenho inicial (azul) */
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(0.5, 0.5, 1.0);

    return;
}

/*
 * Desenha o objecto, tri�ngulo por tri�ngulo, definindo os vectores
 * normais e as coordenadas de textura de cada v�rtice.
 */
void draw_object(void)
{
    GLuint i, j;

    /* Desenha todos os tri�ngulos do objecto */
    glBegin(GL_TRIANGLES);
    for (i = 0; i < N_TRIANGLES; i++)
    {
        for (j = 0; j < 3; j++)
        {
            /* Define o v�rtice j do tri�ngulo i */
            glTexCoord2fv(tex_coords[i][j]);
            glNormal3fv(vertex_normals[triangles[i][j]]);
            glVertex3fv(vertex_coords[triangles[i][j]]);
        }
    }
    glEnd();

    return;
}

/*
 * fun��o para controlar o display (desenhar no ecr� em cada frame)
 */
void display_callback(void)
{
    static float angulo = 0.0f;

    /* Apaga o ecr� e o depth buffer, e reinicia a matriz */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    /* Transforma��o de vis�o */
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    /* faz variar o �ngulo de rota��o entre 0 e 360 graus, e roda o *
     * referencial segundo o eixo (1, 1, 0).                        */
    angulo++;
    if (angulo > 360.0)
        angulo -= 360.0;
    glRotatef(angulo, 1.0, 1.0, 0.0);

    /* Desenha o objecto */
    draw_object();

    /* Troca os buffers, mostrando o que acabou de ser desenhado */
    glutSwapBuffers();
    return;
}

/*
 * Processa o reshape da janela
 */
void reshape_callback(int w, int h)
{

    /* define a zona da janela onde se vai desenhar */
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    /* muda para o modo GL_PROJECTION e reinicia a projec��o */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* Define a forma do "viewing volume" para termos *
     * uma projec��o de perspectiva (3D).             */
    gluPerspective(30, (float)w / (float)h, 1.0, 100.0);

    /* muda para o modo GL_MODELVIEW (n�o pretendemos alterar a projec��o
     * quando estivermos a desenhar no ecr�) */
    glMatrixMode(GL_MODELVIEW);
    return;
}

/*
 * Fun��o necess�ria para a anima��o
 */
void animate_callback(void)
{
    glutPostRedisplay(); /* Manda o redesenhar o ecr� em cada frame */
    return;
}

/*
 * Controlo das teclas normais
 */
void keyboard_callback(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0); /* Esc: sai do programa */
    return;
}

/*
 * Controlo das teclas especiais (Cursores, F1 a F12, etc...)
 */
void keyboard_callback_special(int key, int x, int y)
{
    switch (key)
    {
    case 1:
        glColor3f(0.5, 0.5, 1.0); /* F1: muda a cor para azul */
        break;

    case 2:
        glColor3f(0.5, 1.0, 0.5); /* F2: muda a cor para verde */
        break;

    case 3:
        glColor3f(1.0, 0.5, 0.5); /* F3: muda a cor para vermelho */
        break;

    default: /* isto aqui n�o faz nada, mas evita warnings :P */
        break;
    }

    return;
}

/*
 * Fun��o callback para o controlo do menu
 */
void menu_callback(int value)
{
    switch (value)
    {
    case 'b':
        glColor3f(0.5, 0.5, 1.0); /* Op��o 1: muda a cor para azul */
        break;

    case 'g':
        glColor3f(0.5, 1.0, 0.5); /* Op��o 2: muda a cor para verde */
        break;

    case 'r':
        glColor3f(1.0, 0.5, 0.5); /* Op��o 3: muda a cor para vermelho */
        break;

    case 27:
        exit(0); /* Op��o 4: sai do programa */
        break;

    default:
        break;
    }

    /* Manda o redesenhar o ecr� quando o menu for desactivado */
    glutPostRedisplay();

    return;
}
