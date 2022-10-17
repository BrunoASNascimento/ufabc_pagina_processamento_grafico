/*
 *  Este programa originalmente denominado exemplo1.c foi obtido 
 *  na p�gina Web do Prof. Samuel Nunes, por ser bastante didatico:
 *  http://w3.ualg.pt/~srnunes/CG/index.html
 *  e foi adaptado por Celso Kurashima para a disciplina BC1515
 *  Modificado em 22/03/2009 - UFABC
 */


/* Inclui os headers do OpenGL, GLU, e GLUT */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


/**********************************************************************/
/*                        Declara��o de fun��es                       */
/**********************************************************************/
void init_glut(const char *window_name, int *argcp, char **argv);
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


void drawArrow() {
   glBegin(GL_TRIANGLE_STRIP);
      glVertex3f (-1.0, 2.0, 0.0);
      glVertex3f (-2.0, 1.0, 0.0);
      glVertex3f (0.0, 1.0, 0.0);

      glVertex3f (-1.0, 0.0, 0.0);

      glVertex3f (-2.0, 1.0, 0.0);
      glVertex3f (-6.0, 0.0, 0.0);
      glVertex3f (-2.0, -1.0, 0.0);

      glVertex3f (-1.0, 0.0, 0.0);
      glVertex3f (0.0, -1.0, 0.0);
      glVertex3f (-2.0, -1.0, 0.0);
      glVertex3f (-1.0, -2.0, 0.0);
   glEnd();
}

int main(int argc, char **argv){

   /* inicia o GLUT e alguns par�metros do OpenGL */
   init_glut("Equipe átomos", &argc, argv);

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
void init_glut(const char *nome_janela, int *argcp, char **argv){

    /* inicia o GLUT */
    glutInit(argcp,argv);

    /* inicia o display usando RGB e double-buffering */
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(250, 250);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(nome_janela);

    /* define as func�es de callback */
    glutKeyboardFunc(keyboard_callback);
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutSpecialFunc(keyboard_callback_special);
    glutIdleFunc(animate_callback);

    /* define a c�r com a qual a tela ser� apagado */
    glClearColor(0.0,0.0,0.0,0.0);

    /* define a cor de desenho inicial (azul) */
    glColor3f(0.0, 0.0, 1.0);

    return;
}


/*
 * fun��o para controlar o display (desenhar na tela em cada frame)
 */
void display_callback(void){
    static GLfloat angulo = 0.0f; /* por ter sido declarada como "static" dentro *
                                   * de uma fun��o, esta vari�vel tem "mem�ria"  */

    /* Apaga o ecr� e reinicia a matriz */
    glClear(GL_COLOR_BUFFER_BIT);
    // glLoadIdentity();

    // /* faz variar o �ngulo entre 0 e 360 graus */
    // angulo++;
    // if (angulo> 360.0) angulo -= 360.0;

    // /* desenha um tri�ngulo rodado de acordo com "angulo" */
    // glRotatef(angulo, 0.0, 0.0, 1.0);
    // glBegin(GL_TRIANGLES);
    //     glVertex2f(-0.5, -0.289);
    //     glVertex2f( 0.5, -0.289);
    //     glVertex2f( 0.0,  0.577);
    // glEnd();

    drawArrow();


    glRotatef(90.0, 0.0, 0.0, 1.0);
    drawArrow();


    glRotatef(90.0, 0.0, 0.0, 1.0);
    drawArrow();

    glRotatef(90.0, 0.0, 0.0, 1.0);
    drawArrow();
    
    /* troca os buffers, mostrando o que acabou de ser desenhado */
    glutSwapBuffers();
    return;
}


/*
 * Processa o reshape da janela
 */
void reshape_callback(int w, int h){

   /* define a zona da janela onde se vai desenhar */
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);

   /* muda para o modo GL_PROJECTION e reinicia a projec��o */
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();

   /* adapta a projec��o ortogonal de acordo com as dimens�es da janela */
   glOrtho(-6.0, 6.0, -6.0, 6.0, -1.0, 1.0);

   /* muda para o modo GL_MODELVIEW (n�o pretendemos alterar a projec��o *
    * quando estivermos a desenhar na tela)                              */
//    glMatrixMode (GL_MODELVIEW);
   return;
}


/*
 * Fun��o necess�ria para a anima��o
 */
void animate_callback(void){
    glutPostRedisplay(); /* Manda o redesenhar o ecr� em cada frame */
    return;
}


/*
 * Controlo das teclas normais
 */
void keyboard_callback(unsigned char key, int x, int y){
    if (key==27) exit(0); /* Esc: sai do programa */
    return;
}


/*
 * Controlo das teclas especiais (Cursores, F1 a F12, etc...)
 */
void keyboard_callback_special(int key, int x, int y){
    switch(key){
        case 1:
            glColor3f(0.0, 0.0, 1.0);      /* F1: muda a cor para azul */
            break;

        case 2:
            glColor3f(0.0, 1.0, 0.0);      /* F2: muda a cor para verde */
            break;

        case 3:
            glColor3f(1.0, 0.0, 0.0);      /* F2: muda a cor para vermelho */
            break;

        default: /* isto aqui n�o faz nada, mas evita warnings :P */
            break;
    }

    return;
}

