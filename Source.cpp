#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.14

int n;
int is_depth;

float xrot = 0.0f;
float yrot = 0.0f;
float xdiff = 0.0f;
float ydiff = 0.0f;
bool mouseDown = false;

float xmov = 0.0f;
float ymov = 0.0f;
float zmov = 0.0f;

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    is_depth = 1;
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

void angkajam(float jarak, float x, float y, float z) {
    glPointSize(3);

    glBegin(GL_POINTS);
    glColor3f(0, 0, 0);
    for (n = 0; n < 360; n += 30)
        glVertex3f(jarak * (float)sin(n * PI / 180.0) + x, jarak * (float)cos(n * PI / 180.0) + y, jarak * z);
    glEnd();
}


void jam(int xp, int yp, int zp, int r, int banyak) {
    float a, x, y, z;
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    a = 6.28 / banyak;
    for (int i = 0; i < banyak; i++) {
        x = xp + r * cos(i + a);
        y = yp + r * sin(i + a);
        z = zp + r * sin(a);
        glVertex3f(x, y, z);
    }
    glEnd();
}

void kotak(float x1, float y1, float z1, float x2, float y2, float z2)
{
    //depan
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x1, y1, z1);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(x2, y1, z1);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(x2, y2, z1);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(x1, y2, z1);
    //atas
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x1, y2, z1);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(x2, y2, z1);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(x2, y2, z2);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(x1, y2, z2);
    //belakang
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x1, y2, z2);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(x2, y2, z2);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(x2, y1, z2);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(x1, y1, z2);
    //bawah
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x1, y1, z2);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(x2, y1, z2);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(x2, y1, z1);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(x1, y1, z1);
    //samping kiri
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x1, y1, z1);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(x1, y2, z1);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(x1, y2, z2);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(x1, y1, z2);
    //samping kanan
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x2, y1, z1);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(x2, y2, z1);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(x2, y2, z2);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(x2, y1, z2);
}

void meja()
{
    //BLKG
    glBegin(GL_QUADS);
    glColor3ub(33, 19, 13);
    glVertex3f(-10, 7, 30);
    glVertex3f(10, 7, 30);
    glVertex3f(10, 6.5, 30);
    glVertex3f(-10, 6.5, 30);
    glEnd();

    //DPN
    glBegin(GL_QUADS);
    glColor3ub(33, 19, 13);
    glVertex3f(-10, 7, 35);
    glVertex3f(10, 7, 35);
    glVertex3f(10, 6.5, 35);
    glVertex3f(-10, 6.5, 35);
    glEnd();

    //KNAN
    glBegin(GL_QUADS);
    glColor3ub(33, 19, 13);
    glVertex3f(10, 7, 35);
    glVertex3f(10, 6.5, 35);
    glVertex3f(10, 6.5, 30);
    glVertex3f(10, 7, 30);
    glEnd();

    //kir
    glBegin(GL_QUADS);
    glColor3ub(33, 19, 13);
    glVertex3f(-10, 7, 35);
    glVertex3f(-10, 6.5, 35);
    glVertex3f(-10, 6.5, 30);
    glVertex3f(-10, 7, 30);
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(33, 19, 13);
    glVertex3f(10, 7, 35);
    glVertex3f(10, 7, 30);
    glVertex3f(-10, 7, 30);
    glVertex3f(-10, 7, 35);
    glEnd();
    //bawah
    glBegin(GL_QUADS);
    glColor3ub(33, 19, 13);
    glVertex3f(10, 6.5, 35);
    glVertex3f(10, 6.5, 30);
    glVertex3f(-10, 6.5, 30);
    glVertex3f(-10, 6.5, 35);
    glEnd();

    //kakikan
    glBegin(GL_QUADS);
    glColor3ub(33, 19, 13);
    glVertex3f(9, 6.5, 34.5);
    glVertex3f(9, 0, 34.5);
    glVertex3f(9, 0, 30.5);
    glVertex3f(9, 6.5, 30.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(33, 19, 13);
    glVertex3f(8, 6.5, 34.5);
    glVertex3f(8, 0, 34.5);
    glVertex3f(8, 0, 30.5);
    glVertex3f(8, 6.5, 30.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(33, 19, 13);
    glVertex3f(8, 6.5, 30.5);
    glVertex3f(9, 6.5, 30.5);
    glVertex3f(9, 0, 30.5);
    glVertex3f(8, 0, 30.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(33, 19, 13);
    glVertex3f(8, 6.5, 34.5);
    glVertex3f(9, 6.5, 34.5);
    glVertex3f(9, 0, 34.5);
    glVertex3f(8, 0, 34.5);
    glEnd();

    //kakikir
    glBegin(GL_QUADS);
    glColor3ub(33, 19, 13);
    glVertex3f(-9, 6.5, 34.5);
    glVertex3f(-9, 0, 34.5);
    glVertex3f(-9, 0, 30.5);
    glVertex3f(-9, 6.5, 30.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(33, 19, 13);
    glVertex3f(-8, 6.5, 34.5);
    glVertex3f(-8, 0, 34.5);
    glVertex3f(-8, 0, 30.5);
    glVertex3f(-8, 6.5, 30.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(33, 19, 13);
    glVertex3f(-8, 6.5, 30.5);
    glVertex3f(-9, 6.5, 30.5);
    glVertex3f(-9, 0, 30.5);
    glVertex3f(-8, 0, 30.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(33, 19, 13);
    glVertex3f(-8, 6.5, 34.5);
    glVertex3f(-9, 6.5, 34.5);
    glVertex3f(-9, 0, 34.5);
    glVertex3f(-8, 0, 34.5);
    glEnd();


    //kakitengah
    glBegin(GL_QUADS);
    glColor3ub(33, 19, 13);
    glVertex3f(-1, 6.5, 33);
    glVertex3f(-1, 0, 33);
    glVertex3f(-1, 0, 31);
    glVertex3f(-1, 6.5, 31);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(33, 19, 13);
    glVertex3f(1, 6.5, 33);
    glVertex3f(1, 0, 33);
    glVertex3f(1, 0, 31);
    glVertex3f(1, 6.5, 31);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(33, 19, 13);
    glVertex3f(-1, 0, 31);
    glVertex3f(-1, 6.5, 31);
    glVertex3f(1, 6.5, 31);
    glVertex3f(1, 0, 31);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(33, 19, 13);
    glVertex3f(-1, 0, 33);
    glVertex3f(-1, 6.5, 33);
    glVertex3f(1, 6.5, 33);
    glVertex3f(1, 0, 33);
    glEnd();
}

void kursi()
{
    //BLKG
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(-10, 4.5, 36);
    glVertex3f(10, 4.5, 36);
    glVertex3f(10, 3.5, 36);
    glVertex3f(-10, 3.5, 36);
    glEnd();

    //DPN
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(-10, 4.5, 39);
    glVertex3f(10, 4.5, 39);
    glVertex3f(10, 3.5, 39);
    glVertex3f(-10, 3.5, 39);
    glEnd();

    //KNAN
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(10, 4.5, 39);
    glVertex3f(10, 3.5, 39);
    glVertex3f(10, 3.5, 36);
    glVertex3f(10, 4.5, 36);
    glEnd();

    //kir
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(-10, 4.5, 39);
    glVertex3f(-10, 3.5, 39);
    glVertex3f(-10, 3.5, 36);
    glVertex3f(-10, 4.5, 36);
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(10, 4.5, 39);
    glVertex3f(10, 4.5, 36);
    glVertex3f(-10, 4.5, 36);
    glVertex3f(-10, 4.5, 39);
    glEnd();
    //bawah
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(10, 3.5, 39);
    glVertex3f(10, 3.5, 36);
    glVertex3f(-10, 3.5, 36);
    glVertex3f(-10, 3.5, 39);
    glEnd();

    //kakikan
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(9, 3.5, 38.5);
    glVertex3f(9, 0, 38.5);
    glVertex3f(9, 0, 36.5);
    glVertex3f(9, 3.5, 36.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(8, 3.5, 38.5);
    glVertex3f(8, 0, 38.5);
    glVertex3f(8, 0, 36.5);
    glVertex3f(8, 3.5, 36.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(8, 3.5, 36.5);
    glVertex3f(9, 3.5, 36.5);
    glVertex3f(9, 0, 36.5);
    glVertex3f(8, 0, 36.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(8, 3.5, 38.5);
    glVertex3f(9, 3.5, 38.5);
    glVertex3f(9, 0, 38.5);
    glVertex3f(8, 0, 38.5);
    glEnd();

    //kakikir
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(-9, 3.5, 38.5);
    glVertex3f(-9, 0, 38.5);
    glVertex3f(-9, 0, 36.5);
    glVertex3f(-9, 3.5, 36.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(-8, 3.5, 38.5);
    glVertex3f(-8, 0, 38.5);
    glVertex3f(-8, 0, 36.5);
    glVertex3f(-8, 3.5, 36.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(-8, 3.5, 36.5);
    glVertex3f(-9, 3.5, 36.5);
    glVertex3f(-9, 0, 36.5);
    glVertex3f(-8, 0, 36.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(-8, 3.5, 38.5);
    glVertex3f(-9, 3.5, 38.5);
    glVertex3f(-9, 0, 38.5);
    glVertex3f(-8, 0, 38.5);
    glEnd();

    //kakitengah
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(-1, 3.5, 38.25);
    glVertex3f(-1, 0, 38.25);
    glVertex3f(-1, 0, 36.75);
    glVertex3f(-1, 3.5, 36.75);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(1, 3.5, 38.25);
    glVertex3f(1, 0, 38.25);
    glVertex3f(1, 0, 36.75);
    glVertex3f(1, 3.5, 36.75);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(-1, 0, 36.75);
    glVertex3f(-1, 3.5, 36.75);
    glVertex3f(1, 3.5, 36.75);
    glVertex3f(1, 0, 36.75);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(-1, 0, 38.25);
    glVertex3f(-1, 3.5, 38.25);
    glVertex3f(1, 3.5, 38.25);
    glVertex3f(1, 0, 38.25);
    glEnd();

    //kakitengah kiri
    glPushMatrix();
    glTranslatef(-4.5, 0, 0);
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(-1, 3.5, 38.25);
    glVertex3f(-1, 0, 38.25);
    glVertex3f(-1, 0, 36.75);
    glVertex3f(-1, 3.5, 36.75);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(1, 3.5, 38.25);
    glVertex3f(1, 0, 38.25);
    glVertex3f(1, 0, 36.75);
    glVertex3f(1, 3.5, 36.75);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(-1, 0, 36.75);
    glVertex3f(-1, 3.5, 36.75);
    glVertex3f(1, 3.5, 36.75);
    glVertex3f(1, 0, 36.75);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(-1, 0, 38.25);
    glVertex3f(-1, 3.5, 38.25);
    glVertex3f(1, 3.5, 38.25);
    glVertex3f(1, 0, 38.25);
    glEnd();
    glPopMatrix();

    //kakitengah kiri
    glPushMatrix();
    glTranslatef(4.5, 0, 0);
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(-1, 3.5, 38.25);
    glVertex3f(-1, 0, 38.25);
    glVertex3f(-1, 0, 36.75);
    glVertex3f(-1, 3.5, 36.75);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(1, 3.5, 38.25);
    glVertex3f(1, 0, 38.25);
    glVertex3f(1, 0, 36.75);
    glVertex3f(1, 3.5, 36.75);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(-1, 0, 36.75);
    glVertex3f(-1, 3.5, 36.75);
    glVertex3f(1, 3.5, 36.75);
    glVertex3f(1, 0, 36.75);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(118, 68, 46);
    glVertex3f(-1, 0, 38.25);
    glVertex3f(-1, 3.5, 38.25);
    glVertex3f(1, 3.5, 38.25);
    glVertex3f(1, 0, 38.25);
    glEnd();
    glPopMatrix();
}

void TV(void)
{
    //depan
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-5, 24, 2);
    glVertex3f(5, 24, 2);
    glVertex3f(5, 30, 2);
    glVertex3f(-5, 30, 2);
    glEnd();

    //belakang
    glBegin(GL_QUADS);
    glColor4ub(169, 169, 169, 1);
    glVertex3f(-4, 25, 3);
    glVertex3f(4, 25, 3);
    glVertex3f(4, 29, 3);
    glVertex3f(-4, 29, 3);
    glEnd();

    //tombol
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-4, 24, 3);
    glVertex3f(-4., 24, 3);
    glVertex3f(-4.5, 24.5, 3);
    glVertex3f(-4, 24.5, 3);
    glEnd();
}

void kaca1(float x, float y, float z)
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-4 + x, 68 + y, 22 + z);
    glVertex3f(-2 + x, 68 + y, 22 + z);
    glVertex3f(-2 + x, 64 + y, 22 + z);
    glVertex3f(-4 + x, 64 + y, 22 + z);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(114, 140, 168);
    glVertex3f(-4 + x, 68 + y, 22 + z);
    glVertex3f(-2 + x, 68 + y, 22 + z);
    glVertex3f(-2 + x, 64 + y, 22 + z);
    glVertex3f(-4 + x, 64 + y, 22 + z);
    glEnd();
}

void kaca2(float x, float y, float z)
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-4 + x, 54 + y, 22 + z);
    glVertex3f(-2 + x, 54 + y, 22 + z);
    glVertex3f(-2 + x, 50 + y, 22 + z);
    glVertex3f(-4 + x, 50 + y, 22 + z);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(114, 140, 168);
    glVertex3f(-4 + x, 54 + y, 22 + z);
    glVertex3f(-2 + x, 54 + y, 22 + z);
    glVertex3f(-2 + x, 50 + y, 22 + z);
    glVertex3f(-4 + x, 50 + y, 22 + z);
    glEnd();
}

void kacabangunan1(float x, float y, float z)
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(20 + x, 25 + y, 2 + z);
    glVertex3f(17 + x, 25 + y, 2 + z);
    glVertex3f(17 + x, 21 + y, 2 + z);
    glVertex3f(20 + x, 21 + y, 2 + z);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(81, 97, 115);
    glVertex3f(20 + x, 25 + y, 2 + z);
    glVertex3f(17 + x, 25 + y, 2 + z);
    glVertex3f(17 + x, 21 + y, 2 + z);
    glVertex3f(20 + x, 21 + y, 2 + z);
    glEnd();
}

void kacabangunan11(float x, float y, float z)
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(20 + x, 10 + y, 2 + z);
    glVertex3f(17 + x, 10 + y, 2 + z);
    glVertex3f(17 + x, 6 + y, 2 + z);
    glVertex3f(20 + x, 6 + y, 2 + z);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(45, 56, 69);
    glVertex3f(20 + x, 10 + y, 2 + z);
    glVertex3f(17 + x, 10 + y, 2 + z);
    glVertex3f(17 + x, 6 + y, 2 + z);
    glVertex3f(20 + x, 6 + y, 2 + z);
    glEnd();
}

void kacabangunan01(float x, float y, float z)
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-26 + x, 25 + y, 2 + z);
    glVertex3f(-23 + x, 25 + y, 2 + z);
    glVertex3f(-23 + x, 21 + y, 2 + z);
    glVertex3f(-26 + x, 21 + y, 2 + z);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(81, 97, 115);
    glVertex3f(-26 + x, 25 + y, 2 + z);
    glVertex3f(-23 + x, 25 + y, 2 + z);
    glVertex3f(-23 + x, 21 + y, 2 + z);
    glVertex3f(-26 + x, 21 + y, 2 + z);
    glEnd();
}

void kacabangunan011(float x, float y, float z)
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-26 + x, 10 + y, 2 + z);
    glVertex3f(-23 + x, 10 + y, 2 + z);
    glVertex3f(-23 + x, 6 + y, 2 + z);
    glVertex3f(-26 + x, 6 + y, 2 + z);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(45, 56, 69);
    glVertex3f(-26 + x, 10 + y, 2 + z);
    glVertex3f(-23 + x, 10 + y, 2 + z);
    glVertex3f(-23 + x, 6 + y, 2 + z);
    glVertex3f(-26 + x, 6 + y, 2 + z);
    glEnd();
}

void kacabangunan4(float x, float y, float z)
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(34 + x, 20 + y, 2 + z);
    glVertex3f(31 + x, 20 + y, 2 + z);
    glVertex3f(31 + x, 16 + y, 2 + z);
    glVertex3f(34 + x, 16 + y, 2 + z);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(81, 97, 115);
    glVertex3f(34 + x, 20 + y, 2 + z);
    glVertex3f(31 + x, 20 + y, 2 + z);
    glVertex3f(31 + x, 16 + y, 2 + z);
    glVertex3f(34 + x, 16 + y, 2 + z);
    glEnd();
}

void kacabangunan44(float x, float y, float z)
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(34 + x, 10 + y, 2 + z);
    glVertex3f(31 + x, 10 + y, 2 + z);
    glVertex3f(31 + x, 6 + y, 2 + z);
    glVertex3f(34 + x, 6 + y, 2 + z);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(45, 56, 69);
    glVertex3f(34 + x, 10 + y, 2 + z);
    glVertex3f(31 + x, 10 + y, 2 + z);
    glVertex3f(31 + x, 6 + y, 2 + z);
    glVertex3f(34 + x, 6 + y, 2 + z);
    glEnd();
}

void kacabangunan04(float x, float y, float z)
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-46 + x, 20 + y, 2 + z);
    glVertex3f(-43 + x, 20 + y, 2 + z);
    glVertex3f(-43 + x, 16 + y, 2 + z);
    glVertex3f(-46 + x, 16 + y, 2 + z);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(81, 97, 115);
    glVertex3f(-46 + x, 20 + y, 2 + z);
    glVertex3f(-43 + x, 20 + y, 2 + z);
    glVertex3f(-43 + x, 16 + y, 2 + z);
    glVertex3f(-46 + x, 16 + y, 2 + z);
    glEnd();
}

void kacabangunan044(float x, float y, float z)
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-46 + x, 10 + y, 2 + z);
    glVertex3f(-43 + x, 10 + y, 2 + z);
    glVertex3f(-43 + x, 6 + y, 2 + z);
    glVertex3f(-46 + x, 6 + y, 2 + z);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(45, 56, 69);
    glVertex3f(-46 + x, 10 + y, 2 + z);
    glVertex3f(-43 + x, 10 + y, 2 + z);
    glVertex3f(-43 + x, 6 + y, 2 + z);
    glVertex3f(-46 + x, 6 + y, 2 + z);
    glEnd();
}

void kacabangunan6(float x, float y, float z)
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(55.5 + x, 17 + y, -7 + z);
    glVertex3f(53.5 + x, 17 + y, -7 + z);
    glVertex3f(53.5 + x, 13 + y, -7 + z);
    glVertex3f(55.5 + x, 13 + y, -7 + z);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(81, 97, 115);
    glVertex3f(55.5 + x, 17 + y, -7 + z);
    glVertex3f(53.5 + x, 17 + y, -7 + z);
    glVertex3f(53.5 + x, 13 + y, -7 + z);
    glVertex3f(55.5 + x, 13 + y, -7 + z);
    glEnd();
}

void kacabangunan66(float x, float y, float z)
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(55.5 + x, 7 + y, -7 + z);
    glVertex3f(53.5 + x, 7 + y, -7 + z);
    glVertex3f(53.5 + x, 3 + y, -7 + z);
    glVertex3f(55.5 + x, 3 + y, -7 + z);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(45, 56, 69);
    glVertex3f(55.5 + x, 7 + y, -7 + z);
    glVertex3f(53.5 + x, 7 + y, -7 + z);
    glVertex3f(53.5 + x, 3 + y, -7 + z);
    glVertex3f(55.5 + x, 3 + y, -7 + z);
    glEnd();
}

void kacabangunan06(float x, float y, float z)
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-65.5 + x, 17 + y, -7 + z);
    glVertex3f(-63.5 + x, 17 + y, -7 + z);
    glVertex3f(-63.5 + x, 13 + y, -7 + z);
    glVertex3f(-65.5 + x, 13 + y, -7 + z);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(81, 97, 115);
    glVertex3f(-65.5 + x, 17 + y, -7 + z);
    glVertex3f(-63.5 + x, 17 + y, -7 + z);
    glVertex3f(-63.5 + x, 13 + y, -7 + z);
    glVertex3f(-65.5 + x, 13 + y, -7 + z);
    glEnd();
}

void kacabangunan066(float x, float y, float z)
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-65.5 + x, 7 + y, -7 + z);
    glVertex3f(-63.5 + x, 7 + y, -7 + z);
    glVertex3f(-63.5 + x, 3 + y, -7 + z);
    glVertex3f(-65.5 + x, 3 + y, -7 + z);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(45, 56, 69);
    glVertex3f(-65.5 + x, 7 + y, -7 + z);
    glVertex3f(-63.5 + x, 7 + y, -7 + z);
    glVertex3f(-63.5 + x, 3 + y, -7 + z);
    glVertex3f(-65.5 + x, 3 + y, -7 + z);
    glEnd();
}

void kacabangunan0(float x, float y, float z)
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-6 + x, 40 + y, 26 + z);
    glVertex3f(-4 + x, 40 + y, 26 + z);
    glVertex3f(-4 + x, 34 + y, 26 + z);
    glVertex3f(-6 + x, 34 + y, 26 + z);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(81, 97, 115);
    glVertex3f(-6 + x, 40 + y, 26 + z);
    glVertex3f(-4 + x, 40 + y, 26 + z);
    glVertex3f(-4 + x, 34 + y, 26 + z);
    glVertex3f(-6 + x, 34 + y, 26 + z);
    glEnd();
}

void ulang1(void)
{
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            kaca1(i * 6, j * 2, 0);
        }
    }
}

void ulang2(void)
{
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++)
        {
            kaca2(i * 6, j * 2, 0);
        }
    }
}

void ulangbangunan1(void)
{
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 5; j++)
        {
            kacabangunan1(i * 6, j * 2, 0);
        }
    }
}

void ulangbangunan11(void)
{
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 5; j++)
        {
            kacabangunan11(i * 6, j * 2, 0);
        }
    }
}

void ulangbangunan01(void)
{
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 5; j++)
        {
            kacabangunan01(i * 6, j * 2, 0);
        }
    }
}

void ulangbangunan011(void)
{
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 5; j++)
        {
            kacabangunan011(i * 6, j * 2, 0);
        }
    }
}

void ulangbangunan4(void)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
        {
            kacabangunan4(i * 6, j * 2, 0);
        }
    }
}

void ulangbangunan44(void)
{

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
        {
            kacabangunan44(i * 6, j * 2, 0);
        }
    }
}

void ulangbangunan04(void)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
        {
            kacabangunan04(i * 6, j * 2, 0);
        }
    }
}

void ulangbangunan044(void)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
        {
            kacabangunan044(i * 6, j * 2, 0);
        }
    }
}

void ulangbangunan6(void)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++)
        {
            kacabangunan6(i * 5, j * 2, 0);
        }
    }
}

void ulangbangunan66(void)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++)
        {
            kacabangunan66(i * 5, j * 2, 0);
        }
    }
}

void ulangbangunan06(void)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++)
        {
            kacabangunan06(i * 5, j * 2, 0);
        }
    }
}

void ulangbangunan066(void)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++)
        {
            kacabangunan066(i * 5, j * 2, 0);
        }
    }
}

void ulangbangunan0(void)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++)
        {
            kacabangunan0(i * 5, j * 2, 0);
        }
    }
}

void bangunan1(void)
{
    //gedungtengah
//belakang
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(-30, 0, -80); //D
    glVertex3f(30, 0, -80); //C
    glVertex3f(30, 40, -80); //G
    glVertex3f(-30, 40, -80); //H
    glEnd();

    //penutup bangunan
    //depan
    glBegin(GL_QUADS);
    glColor3ub(43, 34, 32);
    glVertex3f(-30, 40, 0); //A
    glVertex3f(30, 40, 0); //B
    glVertex3f(35, 45, 0); //F
    glVertex3f(-35, 45, 0); //E
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(43, 34, 32);
    glVertex3f(30, 40, 0); //B
    glVertex3f(30, 40, -80); //C
    glVertex3f(35, 45, -80); //G
    glVertex3f(35, 45, 0); //F
    glEnd();

    //belakang
    glBegin(GL_QUADS);
    glColor3ub(43, 34, 32);
    glVertex3f(-30, 40, -80); //D
    glVertex3f(30, 40, -80); //C
    glVertex3f(35, 45, -80); //G
    glVertex3f(-35, 45, -80); //H
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(43, 34, 32);
    glVertex3f(-30, 40, 0); //A
    glVertex3f(-30, 40, -80); //D
    glVertex3f(-35, 45, -80); //H
    glVertex3f(-35, 45, 0); //E
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(43, 34, 32);
    glVertex3f(-35, 45, 0); //E
    glVertex3f(35, 45, 0); //F
    glVertex3f(35, 45, -80); //G
    glVertex3f(-35, 45, -80); //H
    glEnd();

    //bangunan
    //depan
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(-30, 0, 0); //A
    glVertex3f(30, 0, 0); //B
    glVertex3f(30, 40, 0); //F
    glVertex3f(-30, 40, 0); //E
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(30, 30, 0); //B
    glVertex3f(30, 30, -80); //C
    glVertex3f(30, 40, -80); //G
    glVertex3f(30, 40, 0); //F
    glEnd();

    //belakang
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(-30, 0, -80); //D
    glVertex3f(30, 0, -80); //C
    glVertex3f(30, 40, -80); //G
    glVertex3f(-30, 40, -80); //H
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(-30, 30, 0); //A
    glVertex3f(-30, 30, -80); //D
    glVertex3f(-30, 40, -80); //H
    glVertex3f(-30, 40, 0); //E
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(-30, 40, 0); //E
    glVertex3f(30, 40, 0); //F
    glVertex3f(30, 40, -80); //G
    glVertex3f(-30, 40, -80); //H
    glEnd();

    //bawah
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(-30, 40, 0); //A
    glVertex3f(30, 40, 0); //B
    glVertex3f(30, 40, -10); //C
    glVertex3f(-30, 40, -10); //D
    glEnd();

    ///////////////////////////////
   //depan besar
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(30, 0, 5);
    glVertex3f(27, 0, 5);
    glVertex3f(27, 37, 5);
    glVertex3f(30, 37, 5);
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(30, 37, 0);
    glVertex3f(27, 37, 0);
    glVertex3f(27, 37, 5);
    glVertex3f(30, 37, 5);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(27, 0, 0); //A
    glVertex3f(27, 0, 5); //D
    glVertex3f(27, 37, 5); //H
    glVertex3f(27, 37, 0); //E
    glEnd();
    //kanan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(30, 0, 0); //A
    glVertex3f(30, 0, 5); //D
    glVertex3f(30, 37, 5); //H
    glVertex3f(30, 37, 0); //E
    glEnd();

    ///////////////////
    //depankecil
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(22, 0, 3); //A
    glVertex3f(21, 0, 3); //D
    glVertex3f(21, 37, 3); //H
    glVertex3f(22, 37, 3); //E
    glEnd();
    //atas
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(22, 37, 0);
    glVertex3f(21, 37, 0);
    glVertex3f(21.5, 37, 3);
    glVertex3f(22, 37, 3);
    glEnd();
    //kiri
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(21, 0, 0); //A
    glVertex3f(21, 0, 3); //D
    glVertex3f(21, 37, 3); //H
    glVertex3f(21, 37, 0); //E
    glEnd();
    //kanan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(22, 0, 0); //A
    glVertex3f(22, 0, 3); //D
    glVertex3f(22, 37, 3); //H
    glVertex3f(22, 37, 0); //E
    glEnd();

    ///////////////////////
    //depan besar
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-30, 0, 5);
    glVertex3f(-27, 0, 5);
    glVertex3f(-27, 37, 5);
    glVertex3f(-30, 37, 5);
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-30, 37, 0);
    glVertex3f(-27, 37, 0);
    glVertex3f(-27, 37, 5);
    glVertex3f(-30, 37, 5);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-27, 0, 0); //A
    glVertex3f(-27, 0, 5); //D
    glVertex3f(-27, 37, 5); //H
    glVertex3f(-27, 37, 0); //E
    glEnd();
    //kanan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-30, 0, 0); //A
    glVertex3f(-30, 0, 5); //D
    glVertex3f(-30, 37, 5); //H
    glVertex3f(-30, 37, 0); //E
    glEnd();

    //////////////////////////
    //depankecil
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-22, 0, 3); //A
    glVertex3f(-21, 0, 3); //D
    glVertex3f(-21, 37, 3); //H
    glVertex3f(-22, 37, 3); //E
    glEnd();
    //atas
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-22, 37, 0);
    glVertex3f(-21, 37, 0);
    glVertex3f(-21.5, 37, 3);
    glVertex3f(-22, 37, 3);
    glEnd();
    //kiri
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-21, 0, 0); //A
    glVertex3f(-21, 0, 3); //D
    glVertex3f(-21, 37, 3); //H
    glVertex3f(-21, 37, 0); //E
    glEnd();
    //kanan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-22, 0, 0); //A
    glVertex3f(-22, 0, 3); //D
    glVertex3f(-22, 37, 3); //H
    glVertex3f(-22, 37, 0); //E
    glEnd();
}

void bangunan2(void)
{
    //penutupatap
    //depan
    glBegin(GL_QUADS);
    glColor3ub(9, 9, 9);
    glVertex3f(-15, 80, 20); //M
    glVertex3f(15, 80, 20); //N
    glVertex3f(20, 85, 20); //O
    glVertex3f(-20, 85, 20); //P
    glEnd();

    //penutupatap
    //belakang
    glBegin(GL_QUADS);
    glColor3ub(9, 9, 9);
    glVertex3f(-15, 80, 0); //M
    glVertex3f(15, 80, 0); //N
    glVertex3f(20, 85, 0); //O
    glVertex3f(-20, 85, 0); //P
    glEnd();


    //penutupatap
    //kanan
    glBegin(GL_QUADS);
    glColor3ub(9, 9, 9);
    glVertex3f(15, 80, 20); //M
    glVertex3f(15, 80, 0); //N
    glVertex3f(20, 85, 0); //O
    glVertex3f(20, 85, 20); //P
    glEnd();

    //penutupatap
    //kiri
    glBegin(GL_QUADS);
    glColor3ub(9, 9, 9);
    glVertex3f(-15, 80, 20); //M
    glVertex3f(-15, 80, 0); //N
    glVertex3f(-20, 85, 0); //O
    glVertex3f(-20, 85, 20); //P
    glEnd();

    //penutupatap
    //atas
    glBegin(GL_QUADS);
    glColor3ub(43, 34, 32);
    glVertex3f(-20, 85, 0); //E
    glVertex3f(20, 85, 0); //F
    glVertex3f(20, 85, 20); //G
    glVertex3f(-20, 85, 20); //H
    glEnd();


    //depan
    glBegin(GL_QUADS);
    glColor3ub(141, 107, 98);
    glVertex3f(-15, 0, 20); //I
    glVertex3f(15, 0, 20); //J
    glVertex3f(15, 80, 20); //N
    glVertex3f(-15, 80, 20); //M
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(141, 107, 98);
    glVertex3f(15, 0, 20); //J
    glVertex3f(15, 0, 0); //K
    glVertex3f(15, 80, 0); //O
    glVertex3f(15, 80, 20); //N
    glEnd();

    //belakang
    glBegin(GL_QUADS);
    glColor3ub(141, 107, 98);
    glVertex3f(-15, 0, 0); //L
    glVertex3f(15, 0, 0); //k
    glVertex3f(15, 80, 0); //o
    glVertex3f(-15, 80, 0); //p
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(141, 107, 98);
    glVertex3f(-15, 0, 20); //I
    glVertex3f(-15, 0, 0); //L
    glVertex3f(-15, 80, 0); //P
    glVertex3f(-15, 80, 20); //M
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(141, 107, 98);
    glVertex3f(-15, 80, 20); //M
    glVertex3f(15, 80, 20); //N
    glVertex3f(15, 80, 0); //O
    glVertex3f(-15, 80, 0); //P
    glEnd();

    //bawah
    glBegin(GL_QUADS);
    glColor3ub(141, 107, 98);
    glVertex3f(-15, 0, 20); //I
    glVertex3f(15, 0, 20); //J
    glVertex3f(15, 0, 0); //K
    glVertex3f(-15, 0, 0); //L
    glEnd();

    ///////////////////////////////////////////////

    //sisikiri gedngatas depan

    //depan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-15, 30, 23); //I
    glVertex3f(-10, 30, 23); //J
    glVertex3f(-10, 90, 23); //N
    glVertex3f(-15, 90, 23); //M
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-10, 30, 23); //J
    glVertex3f(-10, 30, 20); //K
    glVertex3f(-10, 90, 20); //O
    glVertex3f(-10, 90, 23); //N
    glEnd();

    //belakang
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-15, 80, 20); //L
    glVertex3f(-10, 80, 20); //k
    glVertex3f(-10, 90, 20); //o
    glVertex3f(-15, 90, 20); //p
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-15, 30, 23); //I
    glVertex3f(-15, 30, 20); //L
    glVertex3f(-15, 90, 20); //P
    glVertex3f(-15, 90, 23); //M
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-15, 80, 23); //M
    glVertex3f(15, 80, 23); //N
    glVertex3f(15, 80, 20); //O
    glVertex3f(-15, 80, 20); //P
    glEnd();

    /////////////////////////////////////

    //depan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(15, 30, 23); //I
    glVertex3f(10, 30, 23); //J
    glVertex3f(10, 90, 23); //N
    glVertex3f(15, 90, 23); //M
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(10, 30, 23); //J
    glVertex3f(10, 30, 20); //K
    glVertex3f(10, 90, 20); //O
    glVertex3f(10, 90, 23); //N
    glEnd();

    //belakang
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(15, 80, 20); //L
    glVertex3f(10, 80, 20); //k
    glVertex3f(10, 90, 20); //o
    glVertex3f(15, 90, 20); //p
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(15, 30, 23); //I
    glVertex3f(15, 30, 20); //L
    glVertex3f(15, 90, 20); //P
    glVertex3f(15, 90, 23); //M
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(15, 80, 23); //M
    glVertex3f(10, 80, 23); //N
    glVertex3f(10, 80, 20); //O
    glVertex3f(15, 80, 20); //P
    glEnd();

    ////////////////////////////////////

    //depan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(6, 30, 23); //I
    glVertex3f(5, 30, 23); //J
    glVertex3f(5, 90, 23); //N
    glVertex3f(6, 90, 23); //M
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(5, 30, 23); //J
    glVertex3f(5, 30, 20); //K
    glVertex3f(5, 90, 20); //O
    glVertex3f(5, 90, 23); //N
    glEnd();

    //belakang
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(6, 80, 20); //L
    glVertex3f(5, 80, 20); //k
    glVertex3f(5, 90, 20); //o
    glVertex3f(6, 90, 20); //p
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(6, 30, 23); //I
    glVertex3f(6, 30, 20); //L
    glVertex3f(6, 90, 20); //P
    glVertex3f(6, 90, 23); //M
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(6, 80, 20); //M
    glVertex3f(5, 80, 20); //N
    glVertex3f(5, 80, 0); //O
    glVertex3f(6, 80, 0); //P
    glEnd();

    /////////////////////////////////////

    //depan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-6, 30, 23); //I
    glVertex3f(-5, 30, 23); //J
    glVertex3f(-5, 90, 23); //N
    glVertex3f(-6, 90, 23); //M
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-5, 30, 23); //J
    glVertex3f(-5, 30, 20); //K
    glVertex3f(-5, 90, 20); //O
    glVertex3f(-5, 90, 23); //N
    glEnd();

    //belakang
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-6, 80, 20); //L
    glVertex3f(-5, 80, 20); //k
    glVertex3f(-5, 90, 20); //o
    glVertex3f(-6, 90, 20); //p
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-6, 30, 23); //I
    glVertex3f(-6, 30, 20); //L
    glVertex3f(-6, 90, 20); //P
    glVertex3f(-6, 90, 23); //M
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-6, 80, 20); //M
    glVertex3f(-5, 80, 20); //N
    glVertex3f(-5, 80, 0); //O
    glVertex3f(-6, 80, 0); //P
    glEnd();

    //////////////////////////////////////////

    //depan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-0.5, 30, 23); //I
    glVertex3f(0.5, 30, 23); //J
    glVertex3f(0.5, 90, 23); //N
    glVertex3f(-0.5, 90, 23); //M
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(0.5, 30, 23); //J
    glVertex3f(0.5, 30, 20); //K
    glVertex3f(0.5, 90, 20); //O
    glVertex3f(0.5, 90, 23); //N
    glEnd();

    //belakang
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-0.5, 80, 20); //L
    glVertex3f(0.5, 80, 20); //k
    glVertex3f(0.5, 90, 20); //o
    glVertex3f(-0.5, 90, 20); //p
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-0.5, 30, 23); //I
    glVertex3f(-0.5, 30, 20); //L
    glVertex3f(-0.5, 90, 20); //P
    glVertex3f(-0.5, 90, 23); //M
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-0.5, 80, 20); //M
    glVertex3f(0.5, 80, 20); //N
    glVertex3f(0.5, 80, 0); //O
    glVertex3f(-0.5, 80, 0); //P
    glEnd();


}

void bangunan3(void)
{
    //jalan depan
    glBegin(GL_POLYGON);
    glColor3ub(197, 189, 183);
    glVertex3f(-10, 0, 50);
    glVertex3f(10, 0, 50);
    glVertex3f(10, 0, 100);
    glVertex3f(-10, 0, 100);
    glEnd();

    //pintu depan
    glBegin(GL_POLYGON);
    glColor3ub(9, 9, 9);
    glVertex3f(-10, 0, 50);
    glVertex3f(10, 0, 50);
    glVertex3f(10, 15, 50);
    glVertex3f(0, 20, 50);
    glVertex3f(-10, 15, 50);
    glEnd();

    /////////
    //depam
    glBegin(GL_QUADS);
    glColor4ub(189, 183, 107, 1);
    glVertex3f(-13, 0, 52);
    glVertex3f(-12, 0, 52);
    glVertex3f(-12, 35, 52);
    glColor4ub(128, 128, 0, 1);
    glVertex3f(-13, 35, 52);
    glEnd();
    //atas
    glBegin(GL_QUADS);
    glColor4ub(189, 183, 107, 1);
    glVertex3f(-13, 35, 50);
    glVertex3f(-12, 35, 50);
    glVertex3f(-12, 35, 52);
    glVertex3f(-13, 35, 52);
    glEnd();
    //kanan
    glBegin(GL_QUADS);
    glColor4ub(189, 183, 107, 1);
    glVertex3f(-12, 0, 52);
    glVertex3f(-12, 0, 50);
    glVertex3f(-12, 35, 50);
    glVertex3f(-12, 35, 52);
    glEnd();
    //kiri
    glBegin(GL_QUADS);
    glColor4ub(189, 183, 107, 1);
    glVertex3f(-13, 0, 52);
    glVertex3f(-13, 0, 50);
    glVertex3f(-13, 35, 50);
    glVertex3f(-13, 35, 52);
    glEnd();


    //depan1
    glBegin(GL_QUADS);
    glColor4ub(189, 183, 107, 1);
    glVertex3f(-11, 0, 52);
    glVertex3f(-10, 0, 52);
    glVertex3f(-10, 35, 52);
    glColor4ub(128, 128, 0, 1);
    glVertex3f(-11, 35, 52);
    glEnd();
    //atas
    glBegin(GL_QUADS);
    glColor4ub(189, 183, 107, 1);
    glVertex3f(-11, 35, 50);
    glVertex3f(-10, 35, 50);
    glVertex3f(-10, 35, 52);
    glVertex3f(-11, 35, 52);
    glEnd();
    //kanan
    glBegin(GL_QUADS);
    glColor4ub(189, 183, 107, 1);
    glVertex3f(-11, 0, 52);
    glVertex3f(-11, 0, 50);
    glVertex3f(-11, 35, 50);
    glVertex3f(-11, 35, 52);
    glEnd();
    //kiri
    glBegin(GL_QUADS);
    glColor4ub(189, 183, 107, 1);
    glVertex3f(-10, 0, 52);
    glVertex3f(-10, 0, 50);
    glVertex3f(-10, 35, 50);
    glVertex3f(-10, 35, 52);
    glEnd();

    /////////
    //depan
    glBegin(GL_QUADS);
    glColor4ub(189, 183, 107, 1);
    glVertex3f(13, 0, 52);
    glVertex3f(12, 0, 52);
    glVertex3f(12, 35, 52);
    glColor4ub(128, 128, 0, 1);
    glVertex3f(13, 35, 52);
    glEnd();
    //atas
    glBegin(GL_QUADS);
    glColor4ub(189, 183, 107, 1);
    glVertex3f(13, 35, 50);
    glVertex3f(12, 35, 50);
    glVertex3f(12, 35, 52);
    glVertex3f(13, 35, 52);
    glEnd();
    //kanan
    glBegin(GL_QUADS);
    glColor4ub(189, 183, 107, 1);
    glVertex3f(12, 0, 52);
    glVertex3f(12, 0, 50);
    glVertex3f(12, 35, 50);
    glVertex3f(12, 35, 52);
    glEnd();
    //kiri
    glBegin(GL_QUADS);
    glColor4ub(189, 183, 107, 1);
    glVertex3f(13, 0, 52);
    glVertex3f(13, 0, 50);
    glVertex3f(13, 35, 50);
    glVertex3f(13, 35, 52);
    glEnd();


    //depan2
    glBegin(GL_QUADS);
    glColor4ub(189, 183, 107, 1);
    glVertex3f(11, 0, 52);
    glVertex3f(10, 0, 52);
    glVertex3f(10, 35, 52);
    glColor4ub(128, 128, 0, 1);
    glVertex3f(11, 35, 52);
    glEnd();
    //atas
    glBegin(GL_QUADS);
    glColor4ub(189, 183, 107, 1);
    glVertex3f(11, 35, 50);
    glVertex3f(10, 35, 50);
    glVertex3f(10, 35, 52);
    glVertex3f(11, 35, 52);
    glEnd();
    //kanan
    glBegin(GL_QUADS);
    glColor4ub(189, 183, 107, 1);
    glVertex3f(11, 0, 52);
    glVertex3f(11, 0, 50);
    glVertex3f(11, 35, 50);
    glVertex3f(11, 35, 52);
    glEnd();
    //kiri
    glBegin(GL_QUADS);
    glColor4ub(189, 183, 107, 1);
    glVertex3f(10, 0, 52);
    glVertex3f(10, 0, 50);
    glVertex3f(10, 35, 50);
    glVertex3f(10, 35, 52);
    glEnd();


    ///////
    //jalan kanan
    glBegin(GL_POLYGON);
    glColor3ub(197, 189, 183);
    glVertex3f(15, 0, 45);
    glVertex3f(15, 0, 25);
    glVertex3f(100, 0, 25);
    glVertex3f(100, 0, 45);
    glEnd();

    //pintu kanan
    glBegin(GL_POLYGON);
    glColor3ub(9, 9, 9);
    glVertex3f(15, 0, 45);
    glVertex3f(15, 0, 25);
    glVertex3f(15, 15, 25);
    glVertex3f(15, 20, 35);
    glVertex3f(15, 15, 45);
    glEnd();

    //jalan kanan
    glBegin(GL_POLYGON);
    glColor3ub(197, 189, 183);
    glVertex3f(-15, 0, 45);
    glVertex3f(-15, 0, 25);
    glVertex3f(-100, 0, 25);
    glVertex3f(-100, 0, 45);
    glEnd();


    //pintu kiri
    glBegin(GL_POLYGON);
    glColor3ub(9, 9, 9);
    glVertex3f(-15, 0, 45);
    glVertex3f(-15, 0, 25);
    glVertex3f(-15, 15, 25);
    glVertex3f(-15, 20, 35);
    glVertex3f(-15, 15, 45);
    glEnd();

    //depan
    glBegin(GL_QUADS);
    glColor3ub(225, 186, 123);
    glVertex3f(-15, 0, 50); //Q
    glVertex3f(15, 0, 50); //R
    glVertex3f(15, 30, 50); //V
    glVertex3f(-15, 30, 50); //U
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(225, 186, 123);
    glVertex3f(15, 0, 50); //R
    glVertex3f(15, 0, 20); //S
    glVertex3f(15, 30, 20); //W
    glVertex3f(15, 30, 50); //V
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(225, 186, 123);
    glVertex3f(-15, 0, 50); //Q
    glVertex3f(-15, 0, 20); //T
    glVertex3f(-15, 30, 20); //X
    glVertex3f(-15, 30, 50); //U
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(225, 186, 123);
    glVertex3f(-15, 30, 50); //U
    glVertex3f(15, 30, 50); //V
    glVertex3f(15, 30, 20); //W
    glVertex3f(-15, 30, 20); //X
    glEnd();

    //bawah
    glBegin(GL_QUADS);
    glColor3ub(225, 186, 123);
    glVertex3f(-15, 0, 50); //Q
    glVertex3f(15, 0, 50); //R
    glVertex3f(15, 0, 20); //S
    glVertex3f(-15, 0, 20); //T
    glEnd();

    //////////////////////////////////////////////////////

    //depan
    glBegin(GL_QUADS);
    glColor3ub(185, 143, 123);
    glVertex3f(-7, 30, 25); //Q
    glVertex3f(7, 30, 25); //R
    glVertex3f(7, 50, 25); //V
    glVertex3f(-7, 50, 25); //U
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(185, 143, 123);
    glVertex3f(7, 30, 25); //R
    glVertex3f(7, 30, 20); //S
    glVertex3f(7, 50, 20); //W
    glVertex3f(7, 50, 25); //V
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(185, 143, 123);
    glVertex3f(-7, 30, 25); //Q
    glVertex3f(-7, 30, 20); //T
    glVertex3f(-7, 50, 20); //X
    glVertex3f(-7, 50, 25); //U
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(185, 143, 123);
    glVertex3f(-7, 50, 25); //U
    glVertex3f(7, 50, 25); //V
    glVertex3f(7, 50, 20); //W
    glVertex3f(-7, 50, 20); //X
    glEnd();

    //bawah
    glBegin(GL_QUADS);
    glColor3ub(185, 143, 123);
    glVertex3f(-7, 30, 25); //Q
    glVertex3f(7, 30, 25); //R
    glVertex3f(7, 30, 20); //S
    glVertex3f(-7, 30, 20); //T
    glEnd();

    ////////////////////
    //tiangdepan
    glBegin(GL_POLYGON);
    glColor3ub(190, 162, 146);
    glVertex3f(-10, 0, 50);
    glVertex3f(10, 0, 50);
    glVertex3f(10, 15, 50);
    glVertex3f(0, 20, 50);
    glVertex3f(-10, 15, 50);
    glEnd();
}

void bangunan4(void)
{
    //depan
    glBegin(GL_QUADS);
    glColor3ub(141, 107, 98);
    glVertex3f(30, 0, -80);
    glVertex3f(50, 0, -80);
    glVertex3f(50, 30, -80);
    glVertex3f(30, 30, -80);
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(141, 107, 98);
    glVertex3f(50, 0, 0);
    glVertex3f(50, 0, -80);
    glVertex3f(50, 30, -80);
    glVertex3f(50, 30, 0);
    glEnd();

    //belakang
    glBegin(GL_QUADS);
    glColor3ub(141, 107, 98);
    glVertex3f(30, 0, -80);
    glVertex3f(50, 0, -80);
    glVertex3f(50, 30, -80);
    glVertex3f(30, 30, -80);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(141, 107, 98);
    glVertex3f(30, 0, 0);
    glVertex3f(30, 0, -80);
    glVertex3f(30, 30, -80);
    glVertex3f(30, 30, 0);
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(141, 107, 98);
    glVertex3f(30, 30, 0);
    glVertex3f(50, 30, 0);
    glVertex3f(50, 30, -80);
    glVertex3f(30, 30, -80);
    glEnd();

    //bawah
    glBegin(GL_QUADS);
    glColor3ub(141, 107, 98);
    glVertex3f(30, 0, 0);
    glVertex3f(50, 0, 0);
    glVertex3f(50, 0, -80);
    glVertex3f(30, 0, -80);
    glEnd();

    //depan
    glBegin(GL_QUADS);
    glColor3ub(141, 107, 98);
    glVertex3f(-30, 0, -80);
    glVertex3f(-50, 0, -80);
    glVertex3f(-50, 30, -80);
    glVertex3f(-30, 30, -80);
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(141, 107, 98);
    glVertex3f(-50, 0, 0);
    glVertex3f(-50, 0, -80);
    glVertex3f(-50, 30, -80);
    glVertex3f(-50, 30, 0);
    glEnd();

    //belakang
    glBegin(GL_QUADS);
    glColor3ub(141, 107, 98);
    glVertex3f(-30, 0, -80);
    glVertex3f(-50, 0, -80);
    glVertex3f(-50, 30, -80);
    glVertex3f(-30, 30, -80);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(141, 107, 98);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 0, -80);
    glVertex3f(-30, 30, -80);
    glVertex3f(-30, 30, 0);
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(141, 107, 98);
    glVertex3f(-30, 30, 0);
    glVertex3f(-50, 30, 0);
    glVertex3f(-50, 30, -80);
    glVertex3f(-30, 30, -80);
    glEnd();

    //bawah
    glBegin(GL_QUADS);
    glColor3ub(141, 107, 98);
    glVertex3f(-30, 0, 0);
    glVertex3f(-50, 0, 0);
    glVertex3f(-50, 0, -80);
    glVertex3f(-30, 0, -80);
    glEnd();

    ///////////////////////
    //depan besar
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(50, 0, 5);
    glVertex3f(47, 0, 5);
    glVertex3f(47, 27, 5);
    glVertex3f(50, 27, 5);
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(50, 27, 0);
    glVertex3f(47, 27, 0);
    glVertex3f(47, 27, 5);
    glVertex3f(50, 27, 5);
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(50, 0, 0);
    glVertex3f(50, 0, 5);
    glVertex3f(50, 27, 5);
    glVertex3f(50, 27, 0);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(47, 0, 0);
    glVertex3f(47, 0, 5);
    glVertex3f(47, 27, 5);
    glVertex3f(47, 27, 0);
    glEnd();

    ///////////////////////
    //depan besar
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-50, 0, 5);
    glVertex3f(-47, 0, 5);
    glVertex3f(-47, 27, 5);
    glVertex3f(-50, 27, 5);
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-50, 27, 0);
    glVertex3f(-47, 27, 0);
    glVertex3f(-47, 27, 5);
    glVertex3f(-50, 27, 5);
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-50, 0, 0);
    glVertex3f(-50, 0, 5);
    glVertex3f(-50, 27, 5);
    glVertex3f(-50, 27, 0);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-47, 0, 0);
    glVertex3f(-47, 0, 5);
    glVertex3f(-47, 27, 5);
    glVertex3f(-47, 27, 0);
    glEnd();

    ///////
     //depan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(36, 0, 3);
    glVertex3f(35, 0, 3);
    glVertex3f(35, 27, 3);
    glVertex3f(36, 27, 3);
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(36, 27, 0);
    glVertex3f(35, 27, 0);
    glVertex3f(35, 27, 3);
    glVertex3f(36, 27, 3);
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(36, 0, 0);
    glVertex3f(36, 0, 3);
    glVertex3f(36, 27, 3);
    glVertex3f(36, 27, 0);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(35, 0, 0);
    glVertex3f(35, 0, 3);
    glVertex3f(35, 27, 3);
    glVertex3f(35, 27, 0);
    glEnd();
    ////////
   //depan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(42, 0, 3);
    glVertex3f(41, 0, 3);
    glVertex3f(41, 27, 3);
    glVertex3f(42, 27, 3);
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(42, 27, 0);
    glVertex3f(41, 27, 0);
    glVertex3f(41, 27, 3);
    glVertex3f(42, 27, 3);
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(42, 0, 0);
    glVertex3f(42, 0, 3);
    glVertex3f(42, 27, 3);
    glVertex3f(42, 27, 0);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(41, 0, 0);
    glVertex3f(41, 0, 3);
    glVertex3f(41, 27, 3);
    glVertex3f(41, 27, 0);
    glEnd();
    ////////
   //depan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-42, 0, 3);
    glVertex3f(-41, 0, 3);
    glVertex3f(-41, 27, 3);
    glVertex3f(-42, 27, 3);
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-42, 27, 0);
    glVertex3f(-41, 27, 0);
    glVertex3f(-41, 27, 3);
    glVertex3f(-42, 27, 3);
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-42, 0, 0);
    glVertex3f(-42, 0, 3);
    glVertex3f(-42, 27, 3);
    glVertex3f(-42, 27, 0);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-41, 0, 0);
    glVertex3f(-41, 0, 3);
    glVertex3f(-41, 27, 3);
    glVertex3f(-41, 27, 0);
    glEnd();

    //depan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-36, 0, 3);
    glVertex3f(-35, 0, 3);
    glVertex3f(-35, 27, 3);
    glVertex3f(-36, 27, 3);
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-36, 27, 0);
    glVertex3f(-35, 27, 0);
    glVertex3f(-35, 27, 3);
    glVertex3f(-36, 27, 3);
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-36, 0, 0);
    glVertex3f(-36, 0, 3);
    glVertex3f(-36, 27, 3);
    glVertex3f(-36, 27, 0);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-35, 0, 0);
    glVertex3f(-35, 0, 3);
    glVertex3f(-35, 27, 3);
    glVertex3f(-35, 27, 0);
    glEnd();

    //gedkanan
    //atap kanan
    glBegin(GL_QUADS);
    glColor3ub(9, 9, 9);
    glVertex3f(50, 30, 0);
    glVertex3f(50, 30, -80);
    glVertex3f(55, 35, -80);
    glVertex3f(55, 35, 0);
    glEnd();

    //gedkanan
   //atap depan
    glBegin(GL_QUADS);
    glColor3ub(9, 9, 9);
    glVertex3f(30, 30, 0);
    glVertex3f(50, 30, 0);
    glVertex3f(55, 35, 0);
    glVertex3f(30, 35, 0);
    glEnd();

    //gedkanan
   //atap belakang
    glBegin(GL_QUADS);
    glColor3ub(9, 9, 9);
    glVertex3f(30, 30, -80);
    glVertex3f(50, 30, -80);
    glVertex3f(55, 35, -80);
    glVertex3f(30, 35, -80);
    glEnd();

    //gedkanan
  //atap atas
    glBegin(GL_QUADS);
    glColor3ub(9, 9, 9);
    glVertex3f(30, 35, 0);
    glVertex3f(55, 35, 0);
    glVertex3f(55, 35, -80);
    glVertex3f(30, 35, -80);
    glEnd();

    //bawah
    glBegin(GL_QUADS);
    glColor3ub(141, 107, 98);
    glVertex3f(30, 0, 0);
    glVertex3f(50, 0, 0);
    glVertex3f(50, 0, -80);
    glVertex3f(30, 0, -80);
    glEnd();

    //depan
    glBegin(GL_QUADS);
    glColor3ub(141, 107, 98);
    glVertex3f(-30, 0, 0);
    glVertex3f(-50, 0, 0);
    glVertex3f(-50, 30, 0);
    glVertex3f(-30, 30, 0);
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(141, 107, 98);
    glVertex3f(-50, 0, 0);
    glVertex3f(-50, 0, -80);
    glVertex3f(-50, 30, -80);
    glVertex3f(-50, 30, 0);
    glEnd();

    //belakang
    glBegin(GL_QUADS);
    glColor3ub(141, 107, 98);
    glVertex3f(-30, 0, -80);
    glVertex3f(-50, 0, -80);
    glVertex3f(-50, 30, -80);
    glVertex3f(-30, 30, -80);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(141, 107, 98);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 0, -80);
    glVertex3f(-30, 30, -80);
    glVertex3f(-30, 30, 0);
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(141, 107, 98);
    glVertex3f(-30, 30, 0);
    glVertex3f(-50, 30, 0);
    glVertex3f(-50, 30, -80);
    glVertex3f(-30, 30, -80);
    glEnd();

    //gedungkiri
    //atap kanan
    glBegin(GL_QUADS);
    glColor3ub(9, 9, 9);
    glVertex3f(-30, 30, 0);
    glVertex3f(-30, 30, -80);
    glVertex3f(-30, 35, -80);
    glVertex3f(-30, 35, 0);
    glEnd();

    //gedungkiri
    //atap kiri
    glBegin(GL_QUADS);
    glColor3ub(9, 9, 9);
    glVertex3f(-50, 30, 0);
    glVertex3f(-50, 30, -80);
    glVertex3f(-55, 35, -80);
    glVertex3f(-55, 35, 0);
    glEnd();

    //gedungkiri
    //atap depan
    glBegin(GL_QUADS);
    glColor3ub(9, 9, 9);
    glVertex3f(-50, 30, 0);
    glVertex3f(-30, 30, 0);
    glVertex3f(-30, 35, 0);
    glVertex3f(-55, 35, 0);
    glEnd();

    //gedungkiri
    //atap blakang
    glBegin(GL_QUADS);
    glColor3ub(9, 9, 9);
    glVertex3f(-50, 30, -80);
    glVertex3f(-30, 30, -80);
    glVertex3f(-30, 35, -80);
    glVertex3f(-55, 35, -80);
    glEnd();

    //gedungkiri
    //atap atas
    glBegin(GL_QUADS);
    glColor3ub(9, 9, 9);
    glVertex3f(-55, 35, 0);
    glVertex3f(-30, 35, 0);
    glVertex3f(-30, 35, -80);
    glVertex3f(-55, 35, -80);
    glEnd();

    //bawah
    glBegin(GL_QUADS);
    glColor3ub(141, 107, 98);
    glVertex3f(-30, 0, 0);
    glVertex3f(-50, 0, 0);
    glVertex3f(-50, 0, -80);
    glVertex3f(-30, 0, -80);
    glEnd();
}

void bangunan6(void)
{
    //depan
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(50, 0, -80);
    glVertex3f(70, 0, -80);
    glVertex3f(70, 25, -80);
    glVertex3f(50, 25, -80);
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(70, 0, -10);
    glVertex3f(70, 0, -80);
    glVertex3f(70, 25, -80);
    glVertex3f(70, 25, -10);
    glEnd();

    //belakang
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(50, 0, -80);
    glVertex3f(70, 0, -80);
    glVertex3f(70, 25, -80);
    glVertex3f(50, 25, -80);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(50, 0, -10);
    glVertex3f(50, 0, -80);
    glVertex3f(50, 25, -80);
    glVertex3f(50, 25, -10);
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(50, 25, -10);
    glVertex3f(70, 25, -10);
    glVertex3f(70, 25, -80);
    glVertex3f(50, 25, -80);
    glEnd();

    //bawah
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(50, 0, -10);
    glVertex3f(70, 0, -10);
    glVertex3f(70, 0, -80);
    glVertex3f(50, 0, -80);
    glEnd();

    //depan
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(-50, 0, -80);
    glVertex3f(-70, 0, -80);
    glVertex3f(-70, 25, -80);
    glVertex3f(-50, 25, -80);
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(-70, 0, -10);
    glVertex3f(-70, 0, -80);
    glVertex3f(-70, 25, -80);
    glVertex3f(-70, 25, -10);
    glEnd();

    //belakang
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(-50, 0, -80);
    glVertex3f(-70, 0, -80);
    glVertex3f(-70, 25, -80);
    glVertex3f(-50, 25, -80);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(-50, 0, -10);
    glVertex3f(-50, 0, -80);
    glVertex3f(-50, 25, -80);
    glVertex3f(-50, 25, -10);
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(-50, 25, -10);
    glVertex3f(-70, 25, -10);
    glVertex3f(-70, 25, -80);
    glVertex3f(-50, 25, -80);
    glEnd();

    //bawah
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(-50, 0, -10);
    glVertex3f(-70, 0, -10);
    glVertex3f(-70, 0, -80);
    glVertex3f(-50, 0, -80);
    glEnd();

    //////////
    //depan besar
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(70, 0, -10);
    glVertex3f(68, 0, -10);
    glVertex3f(68, 22, -10);
    glVertex3f(70, 22, -10);
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(70, 22, -5);
    glVertex3f(68, 22, -5);
    glVertex3f(68, 22, -10);
    glVertex3f(70, 22, -10);
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(70, 0, -5);
    glVertex3f(70, 0, -10);
    glVertex3f(70, 22, -10);
    glVertex3f(70, 22, -5);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(68, 0, -5);
    glVertex3f(68, 0, -10);
    glVertex3f(68, 22, -10);
    glVertex3f(68, 22, -5);
    glEnd();
    /////////
    //depan kecil2
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(57, 0, -7);
    glVertex3f(56, 0, -7);
    glVertex3f(56, 22, -7);
    glVertex3f(57, 22, -7);
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(57, 22, -4);
    glVertex3f(56, 22, -4);
    glVertex3f(56, 22, -7);
    glVertex3f(57, 22, -7);
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(57, 0, -4);
    glVertex3f(57, 0, -7);
    glVertex3f(57, 22, -7);
    glVertex3f(57, 22, -4);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(56, 0, -4);
    glVertex3f(56, 0, -7);
    glVertex3f(56, 22, -7);
    glVertex3f(56, 22, -4);
    glEnd();
    /////////
  //depan kecil
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(62, 0, -7);
    glVertex3f(61, 0, -7);
    glVertex3f(61, 22, -7);
    glVertex3f(62, 22, -7);
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(62, 22, -4);
    glVertex3f(61, 22, -4);
    glVertex3f(61, 22, -7);
    glVertex3f(62, 22, -7);
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(62, 0, -4);
    glVertex3f(62, 0, -7);
    glVertex3f(62, 22, -7);
    glVertex3f(62, 22, -4);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(61, 0, -4);
    glVertex3f(61, 0, -7);
    glVertex3f(61, 22, -7);
    glVertex3f(61, 22, -4);
    glEnd();

    //////////
   //depan besar
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-70, 0, -10);
    glVertex3f(-68, 0, -10);
    glVertex3f(-68, 22, -10);
    glVertex3f(-70, 22, -10);
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-70, 22, -5);
    glVertex3f(-68, 22, -5);
    glVertex3f(-68, 22, -10);
    glVertex3f(-70, 22, -10);
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-68, 0, -5);
    glVertex3f(-68, 0, -10);
    glVertex3f(-68, 22, -10);
    glVertex3f(-68, 22, -5);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-70, 0, -5);
    glVertex3f(-70, 0, -10);
    glVertex3f(-70, 22, -10);
    glVertex3f(-70, 22, -5);
    glEnd();

    /////////
    //depan kecil
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-62, 0, -7);
    glVertex3f(-61, 0, -7);
    glVertex3f(-61, 22, -7);
    glVertex3f(-62, 22, -7);
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-62, 22, -4);
    glVertex3f(-61, 22, -4);
    glVertex3f(-61, 22, -7);
    glVertex3f(-62, 22, -7);
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-62, 0, -4);
    glVertex3f(-62, 0, -7);
    glVertex3f(-62, 22, -7);
    glVertex3f(-62, 22, -4);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-61, 0, -4);
    glVertex3f(-61, 0, -7);
    glVertex3f(-61, 22, -7);
    glVertex3f(-61, 22, -4);
    glEnd();
    /////////
   //depan kecil2
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-57, 0, -7);
    glVertex3f(-56, 0, -7);
    glVertex3f(-56, 22, -7);
    glVertex3f(-57, 22, -7);
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-57, 22, -4);
    glVertex3f(-56, 22, -4);
    glVertex3f(-56, 22, -7);
    glVertex3f(-57, 22, -7);
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-57, 0, -4);
    glVertex3f(-57, 0, -7);
    glVertex3f(-57, 22, -7);
    glVertex3f(-57, 22, -4);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(190, 162, 146);
    glVertex3f(-56, 0, -4);
    glVertex3f(-56, 0, -7);
    glVertex3f(-56, 22, -7);
    glVertex3f(-56, 22, -4);
    glEnd();

    //gedpalingkanan
    //kiri
    glBegin(GL_QUADS);
    glColor3ub(9, 9, 9);
    glVertex3f(50, 25, -10);
    glVertex3f(50, 25, -80);
    glVertex3f(50, 30, -80);
    glVertex3f(50, 30, -10);
    glEnd();

    //gedpalingkanan
    //kanan
    glBegin(GL_QUADS);
    glColor3ub(9, 9, 9);
    glVertex3f(70, 25, -10);
    glVertex3f(70, 25, -80);
    glVertex3f(75, 30, -80);
    glVertex3f(75, 30, -10);
    glEnd();

    //gedpalingkanan
   //depan
    glBegin(GL_QUADS);
    glColor3ub(9, 9, 9);
    glVertex3f(50, 25, -10);
    glVertex3f(70, 25, -10);
    glVertex3f(75, 30, -10);
    glVertex3f(50, 30, -10);
    glEnd();

    //gedpalingkanan
   //belakang
    glBegin(GL_QUADS);
    glColor3ub(9, 9, 9);
    glVertex3f(50, 25, -80);
    glVertex3f(70, 25, -80);
    glVertex3f(75, 30, -80);
    glVertex3f(50, 30, -80);
    glEnd();

    //gedpalingkanan
  //atas
    glBegin(GL_QUADS);
    glColor3ub(9, 9, 9);
    glVertex3f(50, 30, -10);
    glVertex3f(75, 30, -10);
    glVertex3f(75, 30, -80);
    glVertex3f(50, 30, -80);
    glEnd();

    //bawah
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(50, 0, -10);
    glVertex3f(70, 0, -10);
    glVertex3f(70, 0, -80);
    glVertex3f(50, 0, -80);
    glEnd();

    //belakang
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(-50, 0, -80);
    glVertex3f(-70, 0, -80);
    glVertex3f(-70, 25, -80);
    glVertex3f(-50, 25, -80);
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(-70, 0, -10);
    glVertex3f(-70, 0, -80);
    glVertex3f(-70, 25, -80);
    glVertex3f(-70, 25, -10);
    glEnd();

    //depan
    //palingkiriged
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(-50, 0, -10);
    glVertex3f(-70, 0, -10);
    glVertex3f(-70, 25, -10);
    glVertex3f(-50, 25, -10);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(-50, 0, -10);
    glVertex3f(-50, 0, -80);
    glVertex3f(-50, 25, -80);
    glVertex3f(-50, 25, -10);
    glEnd();

    //atas
    //gedpalingkiri
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(-50, 25, -10);
    glVertex3f(-70, 25, -10);
    glVertex3f(-70, 25, -80);
    glVertex3f(-50, 25, -80);
    glEnd();

    //atap kanan
    //gedpalingkiri
    glBegin(GL_QUADS);
    glColor3ub(9, 9, 9);
    glVertex3f(-50, 25, -10);
    glVertex3f(-50, 25, -80);
    glVertex3f(-50, 30, -80);
    glVertex3f(-50, 30, -10);
    glEnd();

    //atap kiri
    //gedpalingkiri
    glBegin(GL_QUADS);
    glColor3ub(9, 9, 9);
    glVertex3f(-70, 25, -10);
    glVertex3f(-70, 25, -80);
    glVertex3f(-75, 30, -80);
    glVertex3f(-75, 30, -10);
    glEnd();

    //atap depan
    //gedpalingkiri
    glBegin(GL_QUADS);
    glColor3ub(9, 9, 9);
    glVertex3f(-70, 25, -10);
    glVertex3f(-50, 25, -10);
    glVertex3f(-50, 30, -10);
    glVertex3f(-75, 30, -10);
    glEnd();


    //atap belakang
    //gedpalingkiri
    glBegin(GL_QUADS);
    glColor3ub(9, 9, 9);
    glVertex3f(-70, 25, -80);
    glVertex3f(-50, 25, -80);
    glVertex3f(-50, 30, -80);
    glVertex3f(-75, 30, -80);
    glEnd();


    //atap atas
    //gedpalingkiri
    glBegin(GL_QUADS);
    glColor3ub(9, 9, 9);
    glVertex3f(-75, 30, -10);
    glVertex3f(-50, 30, -10);
    glVertex3f(-50, 30, -80);
    glVertex3f(-75, 30, -80);
    glEnd();

    //bawah
    glBegin(GL_QUADS);
    glColor3ub(157, 119, 100);
    glVertex3f(-50, 0, -10);
    glVertex3f(-70, 0, -10);
    glVertex3f(-70, 0, -80);
    glVertex3f(-50, 0, -80);
    glEnd();
}
void halaman(void)
{
    glBegin(GL_POLYGON);
    glColor3ub(99, 120, 4);
    glVertex3f(-100, 0, 0);
    glVertex3f(100, 0, 0);
    glVertex3f(100, 0, 100);
    glVertex3f(-100, 0, 100);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(177, 166, 144);
    glVertex3f(-100, 0, 100);
    glVertex3f(100, 0, 100);
    glVertex3f(100, 0, -100);
    glVertex3f(-100, 0, -100);
    glEnd();
}

void tampil(void)
{
    if (is_depth) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    else {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);

    glTranslatef(xmov, ymov, zmov);

    glPushMatrix();

    bangunan1();
    bangunan2();
    bangunan3();
    bangunan4();
    bangunan6();

    ulang1();
    ulang2();
    ulangbangunan1();
    ulangbangunan11();
    ulangbangunan01();
    ulangbangunan011();
    ulangbangunan4();
    ulangbangunan44();
    ulangbangunan04();
    ulangbangunan044();
    ulangbangunan6();
    ulangbangunan66();
    ulangbangunan06();
    ulangbangunan066();
    ulangbangunan0();

    halaman();
    meja();
    kursi();
    TV();
    glPopMatrix();

    //lemari pakaian
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.5f, 0.0f);
    //kotakbase
    kotak(-20, 0, -73, -5, 20, -78);
    //kiri
    kotak(-21, 0, -73, -20, 22, -78);
    //kanan
    kotak(-5, 0, -73, -4, 22, -78);
    //bagpintu
    glColor3f(1.1f, 1.0f, 1.0f);
    //gagang pintu kiri
    kotak(-13, 9, -72, -13.5, 11, -73);
    //gagang pintu kanan
    kotak(-11, 9, -72, -10.5, 11, -73);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.1f, 0.1f);
    //pintu kiri
    kotak(-19, 2, -73, -12.5, 18, -72);
    //pintu kanan
    kotak(-11.5, 2, -73, -5.5, 18, -72);
    glEnd();
    glPopMatrix();

    //papan pengumuman
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.5f, 0.0f);
    //papanbase
    kotak(5, 9, -80, 25, 22, -79.5);
    glColor3f(1.1f, 1.0f, 1.0f);
    //boarddepan
    kotak(6, 11, -79.5, 24, 20, -79);

    glEnd();
    glPopMatrix();

    glPushMatrix();
    jam(0, 75, 23, 5, 500);
    angkajam(4.4, 0, 75, 5.3);
    glEnd();
    glPopMatrix();



    glFlush();
    glutSwapBuffers();

}

void idle() {
    if (!mouseDown) {
        xrot += 0.3f;
        yrot += 0.4f;
    }

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouseDown = true;
        xdiff = x - yrot;
        ydiff = -y + xrot;
    }
    else
        mouseDown = false;
}

void mouseMotion(int x, int y) {
    if (mouseDown) {
        yrot = x - xdiff;
        xrot = y + ydiff;

        glutPostRedisplay();
    }
}
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
    case 'W':
        zmov += 3.0;
        break;
    case 'd':
    case 'D':
        xmov += 3.0;
        break;
    case 's':
    case 'S':
        zmov -= 3.0;
        break;
    case 'a':
    case 'A':
        xmov -= 3.0;
        break;
    case '7':
        ymov += 3.0;
        break;
    case '9':
        ymov -= 3.0;
        break;
    case '2':
        glRotatef(2.0, 1.0, 0.0, 0.0);
        break;
    case '8':
        glRotatef(-2.0, 1.0, 0.0, 0.0);
        break;
    case '6':
        glRotatef(2.0, 0.0, 1.0, 0.0);
        break;
    case '4':
        glRotatef(-2.0, 0.0, 1.0, 0.0);
        break;
    case '1':
        glRotatef(2.0, 0.0, 0.0, 1.0);
        break;
    case '3':
        glRotatef(-2.0, 0.0, 0.0, 1.0);
        break;
    case '5':
        if (is_depth)
        {
            is_depth = 0;
            glDisable(GL_DEPTH_TEST);
        }
        else
        {
            is_depth = 1;
            glEnable(GL_DEPTH_TEST);
        }
    }
    tampil();
}

void ukuran(int lebar, int tinggi)
{
    if (tinggi == 0) tinggi = 1;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80.0, lebar / tinggi, 10.0, 600.0);
    glTranslatef(0.0, -5.0, -150.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(250, 80);
    glutCreateWindow("Universitas Tokyo");
    init();
    glutDisplayFunc(tampil);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);

    glutReshapeFunc(ukuran);
    glutMainLoop();
    return 0;
}