#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.1415926535897932384626433832795
#define janela_altura  400
#define janela_largura 600
float rotacao = 1;
float zoom = 1;
float pontax = 20, pontay = 20, velocidadebola = 10, pontaxPkb = -20, pontayPkb = -20;
float trans = 1;
float tx = 0.0, ty = 0.0, xStep = 4, yStep = 4, raiox = 20, raioy = 25;
void tela(GLsizei w, GLsizei h);
void keyboard();
void display(void);
void mousemoveu(int x, int y);
void anima(int valor);
void colisao();
int main(int argc, char** argv)
{
    glutInit(&argc, argv);  // controla se o sistema operacional tem suporte a janelas.

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // quantidade de buffer de cores e que o padrao de cores é RGB ou RGBA
    glutInitWindowSize(janela_largura, janela_altura);  // tamanho da janela

    //glutInitWindowPosition(100, 0); // posicao inicial da janela
    glutCreateWindow("GLUT");   /// cria a janela
    //glutFullScreen();  // full screen

    glutReshapeFunc(tela);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutTimerFunc(velocidadebola, anima, 1);
    glutPassiveMotionFunc(mousemoveu);
    glutSetCursor(GLUT_CURSOR_CROSSHAIR);

    glutMainLoop();

    return EXIT_SUCCESS;
}
void anima(int valor) {
    colisao();
    tx += xStep;
    ty += yStep;
    glutPostRedisplay();
    glutTimerFunc(velocidadebola, anima, 1);
}
void colisao() {

    //COLISÃO-PAREDE-INICIO

    if (tx + 10 > 300 || tx - 10 < -300) {//colisão em cima ou embaixo da janela
        xStep = -xStep;//inverte  a direção
        tx += xStep * 2;//recua 2 pixels

    }
    if (tx > janela_largura / 2) {//se sair da janela à direita
        tx = janela_largura / 2 - 10;//volta pra dentro da janela
    }
    if (tx < -janela_largura / 2) {//se sair da janela à direita
        tx = -janela_largura / 2 + 10;//volta pra dentro da janela
    }
    if ((ty + 10) > (200) || (ty - 10) < (-200)) {//colisão nas paredes laterais
        yStep = -yStep;//inverte a direção
        ty += yStep * 2;//recua 2 pixels pra tras

    }
    if (ty > janela_altura / 2) {//se a bola passar da altura maxima volta pra area da tela
        ty = janela_altura / 2;//retorna pra dentro da janela
    }
    if (ty < -janela_altura / 2 - 10) {//se a bola passar da largura maxima volta pra area da tela
        ty = -janela_altura / 2 + 10;//retorna pra dentro da janela
    }

    //COLISÃO-RAQUETE PlayerMouse
    if ((tx + 10 > pontax - 10 && tx - 10 < pontax + 10)) {// colisao nas laterais da bola
        if ((ty + 20 > pontay - 20 && ty - 20 < pontay + 20)) {//colisao no topo e na base da bola
            if (tx < pontax) {//se a bola estiver mais a esquerda que a raquete
                xStep = -4; //bola vai pra esquerda
                tx += xStep * 2;//recua 2 pixels
            }
            if (tx > pontax) {//se a bola estiver mais a direita que a raquete
                xStep = 4;//bola vai pra direita
                tx += xStep * 2;//recua 2 pixels
            }
            if (ty < pontay) {//se a bola estiver mais a baixo que a raquete
                yStep = -4;//bola vai baixo
                ty += yStep * 2;//recua 2 pixels
            }
            if (ty > pontay) {//se a bola estiver mais a cima que a raquete
                yStep = 4;//bola vai pra cima
                ty += yStep * 2;//recua 2 pixels
            }
        }

    }
    //COLISÃO-RAQUETE PlayerKeyboard
    if ((tx + 10 > pontaxPkb - 10 && tx - 10 < pontaxPkb + 10)) {// colisao nas laterais da bola
        if ((ty + 20 > pontayPkb - 20 && ty - 20 < pontayPkb + 20)) {//colisao no topo e na base da bola
            if (tx < pontaxPkb) {//se a bola estiver mais a esquerda que a raquete
                xStep = -4; //bola vai pra esquerda
                tx += xStep * 2;//recua 2 pixels
            }
            if (tx > pontaxPkb) {//se a bola estiver mais a direita que a raquete
                xStep = 4;//bola vai pra direita
                tx += xStep * 2;//recua 2 pixels
            }
            if (ty < pontayPkb) {//se a bola estiver mais a baixo que a raquete
                yStep = -4;//bola vai baixo
                ty += yStep * 2;//recua 2 pixels
            }
            if (ty > pontayPkb) {//se a bola estiver mais a cima que a raquete
                yStep = 4;//bola vai pra cima
                ty += yStep * 2;//recua 2 pixels
            }
        }

    }
}
void mousemoveu(int x, int y) {

    if (x >= 320) {
        pontax = x - janela_largura / 2;// alinha largura no centro
    }
    pontay = (y * -1) + janela_altura / 2;//alinha altura no centro
    colisao();//testar ao mover o mouse
}
void tela(GLsizei w, GLsizei h)
{

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, janela_largura, 0, janela_altura);
    glMatrixMode(GL_PROJECTION);
}
static class Jogador {
public:
    static void desenharP1() {
        glPushMatrix();//empilha uma matriz

        glutPassiveMotionFunc(mousemoveu);
        glTranslatef(pontax, pontay, 0);//realoca a matriz no plano
        glRotated(pontay / 2.22222, 0, 0, 1);

        //CABO DA RAQUETE
        glBegin(GL_POLYGON);
        glColor3f(0.4, 0, 0);
        glVertex2f(7, -15);//CIMA_e
        glVertex2f(-7, -15);//CIMA_d
        glVertex2f(-7, -40);//BAIXO_e
        glVertex2f(7, -40);//BAIXO_d
        glVertex2f(-6, -42);//BAIXOedg_e
        glVertex2f(6, -42);//BAIXOedg_d
        glEnd();
        //RAQUETE





        glBegin(GL_POLYGON);

        for (double i = 0; i < 25 * PI; i++) { //<-- Change this Value
            if (i < 25 / 2) {
                glColor3f(1, 1, 1);
            }
            else {
                glColor3f(1, 0, 0);
            }
            glVertex3f(cos(i) * raiox, sin(i) * raioy, 0.0);

        }
        glEnd();

        glPopMatrix();//desempilha matriz pra desenhar apartir da matriz original

    }
    static void desenharP2() {
        glPushMatrix();//empilha uma matriz

        glutPassiveMotionFunc(mousemoveu);
        glTranslatef(pontaxPkb, pontayPkb, 0);//realoca a matriz no plano
        glRotated(-pontayPkb / 2.22222, 0, 0, 1);

        //CABO DA RAQUETE
        glBegin(GL_POLYGON);
        glColor3f(0.4, 0, 0);
        glVertex2f(7, -15);//CIMA_e
        glVertex2f(-7, -15);//CIMA_d
        glVertex2f(-7, -40);//BAIXO_e
        glVertex2f(7, -40);//BAIXO_d
        glVertex2f(-6, -42);//BAIXOedg_e
        glVertex2f(6, -42);//BAIXOedg_d
        glEnd();
        //RAQUETE
        glBegin(GL_POLYGON);

        for (double i = 0; i < 25 * PI; i++) { //<-- Change this Value
            if (i < 25 / 2) {
                glColor3f(1, 1, 1);
            }
            else {
                glColor3f(0, 0, 0);
            }
            glVertex3f(cos(i) * raiox, sin(i) * raioy, 0.0);

        }
        glEnd();

        glPopMatrix();//desempilha matriz pra desenhar apartir da matriz original

    }
};
void desenhar() {
    Sleep(5);
    Jogador::desenharP1();
    Jogador::desenharP2();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(0, 200);
    glVertex2f(0, -200);
    glEnd();

    /*PAREDES*/
    glBegin(GL_LINE_LOOP);
    glColor3f(1, 0, 0);
    glVertex2f(300, -200);
    glVertex2f(300, 199);
    glVertex2f(-299, 199);
    glVertex2f(-299, -200);
    glEnd();



    glTranslatef(tx, ty, 0.0f);
    glBegin(GL_POINTS);
    glColor3f(1, 0.5, 0);
    glVertex2f(0, 0);
    glEnd();
    //Suavização 
    glBegin(GL_POINT_SIZE);
    glPointSize(20.0);
    glEnd();

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glFlush();
}
void display() {
    keyboard();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(janela_largura / 2, janela_altura / 2, 0.0);
    glClearColor(0.001f, 0.5f, 0.02f, 1.0f);  // cor do fundo
    glClear(GL_COLOR_BUFFER_BIT);  // limpa a tela com a cor do fundo
    glViewport(0, 0, janela_largura, janela_altura);

    desenhar();

    glFlush(); // executa o desenho
}
void keyboard()
{

    if (GetAsyncKeyState('W') != 0) {
        if (pontayPkb < 200) {
            pontayPkb += 2;
        }
    }
    if (GetAsyncKeyState('A') != 0) {
        if (pontaxPkb > -300) {
            pontaxPkb -= 2;
        }
    }
    if (GetAsyncKeyState('S') != 0) {
        if (pontayPkb > -200) {
            pontayPkb -= 2;
        }
    }
    if (GetAsyncKeyState('D') != 0) {
        if (pontaxPkb < -20) {
            pontaxPkb += 2;
        }
    }
    glutPostRedisplay();
}
