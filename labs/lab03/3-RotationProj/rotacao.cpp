/*
 *  rotacao.cpp
 *  Este programa originalmente denominado exemplo1.c foi obtido 
 *  na página Web do Prof. Samuel Nunes, por ser bastante didatico:
 *  http://w3.ualg.pt/~srnunes/CG/index.html
 *  e foi adaptado por Celso Kurashima para a disciplina BC1515
 *  Modificado em 22/03/2009 - UFABC
 */


/* Inclui os headers do OpenGL, GLU, e GLUT */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


/**********************************************************************/
/*                        Declaração de funções                       */
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
/*                       Função principal (main)                      */
/*                                                                    */
/**********************************************************************/

int main(int argc, char **argv){

   /* inicia o GLUT e alguns parâmetros do OpenGL */
   init_glut("BC1515 - rotacao.cpp", &argc, argv);

   /* função de controlo do GLUT */
   glutMainLoop();

   return 0;
}


/**********************************************************************/
/*                                                                    */
/*                         Definição de funções                       */
/*                                                                    */
/**********************************************************************/

/*
 * inicia o GLUT e alguns parâmetros do OpenGL
 */
void init_glut(const char *nome_janela, int *argcp, char **argv){

    /* inicia o GLUT */
    glutInit(argcp,argv);

    /* inicia o display usando RGB e double-buffering */
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100,100);
    glutCreateWindow(nome_janela);

    /* define as funcões de callback */
    glutKeyboardFunc(keyboard_callback);
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutSpecialFunc(keyboard_callback_special);
    glutIdleFunc(animate_callback);

    /* define a côr com a qual a tela será apagado */
    glClearColor(0.0,0.0,0.0,0.0);

    /* define a cor de desenho inicial (azul) */
    glColor3f(0.0, 0.0, 1.0);

    return;
}


/*
 * função para controlar o display (desenhar na tela em cada frame)
 */
void display_callback(void){
    static GLfloat angulo = 0.0f; /* por ter sido declarada como "static" dentro *
                                   * de uma função, esta variável tem "memória"  */

    /* Apaga o ecrã e reinicia a matriz */
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    /* faz variar o ângulo entre 0 e 360 graus */
    angulo++;
    if (angulo> 360.0) angulo -= 360.0;

    /* desenha um triângulo rodado de acordo com "angulo" */
    glRotatef(angulo, 0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.5, -0.289);
        glVertex2f( 0.5, -0.289);
        glVertex2f( 0.0,  0.577);
    glEnd();

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

   /* muda para o modo GL_PROJECTION e reinicia a projecção */
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();

   /* adapta a projecção ortogonal de acordo com as dimensões da janela */
   if (h > w){
      gluOrtho2D(-1.0, 1.0, (GLfloat)-h/(GLfloat)w, (GLfloat)h/(GLfloat)w);
   }else{
      gluOrtho2D((GLfloat)-w/(GLfloat)h, (GLfloat)w/(GLfloat)h, -1.0, 1.0);
   }

   /* muda para o modo GL_MODELVIEW (não pretendemos alterar a projecção *
    * quando estivermos a desenhar na tela)                              */
   glMatrixMode (GL_MODELVIEW);
   return;
}


/*
 * Função necessária para a animação
 */
void animate_callback(void){
    glutPostRedisplay(); /* Manda o redesenhar o ecrã em cada frame */
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

        default: /* isto aqui não faz nada, mas evita warnings :P */
            break;
    }

    return;
}

