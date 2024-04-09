#include <stdlib.h>
#include <freeglut.h>
#include "player.h"
#include "raycasting.h"
#include "sprite.h"
#include <memory>

std::unique_ptr<Player> p(new Player());
Raycaster r;
Sprite sp;
Sprite sprites[2];

void spriteInit()
{
    sprites[0].type = 1;
    sprites[0].state = 1;
    sprites[0].map = 0;
    sprites[0].x = 1.5 * 64;
    sprites[0].y = 5 * 64;
    sprites[0].z = 20; // key

    sprites[3].type = 3;
    sprites[3].state = 1;
    sprites[3].map = 2;
    sprites[3].x = 2.5 * 64;
    sprites[3].y = 2 * 64;
    sprites[3].z = 20; // enemy
}

void timerCB(int millisec)
{
    glutTimerFunc(millisec, timerCB, 0);
    glutPostRedisplay();
}

int gameState = 0;
int timer = 0;

void display()
{
    timerCB(1000 / 120);
    frame2 = glutGet(GLUT_ELAPSED_TIME);
    fps = (frame2 - frame1);
    frame1 = glutGet(GLUT_ELAPSED_TIME);

    if (gameState == 0) // boot up
    {
        timer = 0;
        gameState = 1;
        p->init();
        spriteInit();
    }
    if (gameState == 1) // intro/title
    {
        timer += 1 * fps;
        if (timer > 1000)
        {
            timer = 0;
            gameState = 2;
        }
    }
    if (gameState == 2) // game loop
    {

        p->movement();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        r.drawRaycast(p->px, p->py, p->pa);
        sp.drawSprite(sprites, p->px, p->py, p->pa, p->keyPickedUp, gameState);
        if ((int)p->px / 48 == 1 && (int)p->py / 48 == 1)
        {
            timer = 0;
            gameState = 3;
        }
    }
    if (gameState == 3) // win
    {
        r.screen(2);
        timer += 1 * fps;
        if (timer > 3000)
        {
            timer = 0;
            gameState = 0;
        }
    }
    if (gameState == 4) // lose
    {
        r.screen(3);
        timer += 1 * fps;
        if (timer > 3000)
        {
            timer = 0;
            gameState = 0;
        }
    }
    glutSwapBuffers();
}

void btnDown(unsigned char key, int x, int y)
{
    p->ButtonDown(key, x, y);
}

void btnUp(unsigned char key, int x, int y)
{
    p->ButtonUp(key, x, y);
}

void resize(int w, int h) // screen window rescaled, snap back
{
    glutReshapeWindow(960, 640);
}

int main(int argc, char *argv[])
{
    spriteInit();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(960, 640);
    glutCreateWindow("wolfenstein-esque Clone");
    glClearColor(0.3, 0.3, 0.3, 0);
    gluOrtho2D(0, 960, 640, 0);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(btnDown);
    glutKeyboardUpFunc(btnUp);
    glutMainLoop();
}