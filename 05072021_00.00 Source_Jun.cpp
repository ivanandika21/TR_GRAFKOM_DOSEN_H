#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

#define FPS 120
#define TO_RADIANS 3.14/180.0

// pohon natal, ember, kasur, meja ruang tamu + gelas, jam dinding, lampu, ac, tv

const int width = 1280;
const int height = 720;
int i;
float sudut;
double x_geser, y_geser, z_geser;

float pitch = 0.0, yaw = 0.0;
float camX = 0.0, camZ = 0.0, terbang = 25.0;


void display();
void reshape(int w, int h);
void timer(int);
void passive_motion(int, int);
void camera();
void keyboard(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);

struct Motion
{
	bool Forward, Backward, Left, Right, Naik, Turun;
};
Motion motion = { false,false,false,false,false,false };

void init()
{
	glClearColor(0.529, 0.807, 0.921, 0.0);
	glutSetCursor(GLUT_CURSOR_NONE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	glutWarpPointer(width / 2, height / 2);
}

void ground() {
	glBegin(GL_QUADS);
	glColor3f(0.3f, 0.3f, 0.3f);
	glVertex3f(-400.0, 0, -400.0);
	glColor3f(0.6f, 0.6f, 0.6f);
	glVertex3f(400.0, 0, -400.0);
	glColor3f(0.6f, 0.6f, 0.6f);
	glVertex3f(400.0, 0, 145.0);
	glColor3f(0.3f, 0.3f, 0.3f);
	glVertex3f(-400.0, 0, 145.0);
	glEnd();
}

void jam() {
	//frame
	glColor3f(0, 0, 0);
	glPushMatrix();
	glRotatef(90,0,1,0);
	glBegin(GL_POLYGON);
	float a = 6.28 / 360;
	for (int i = 0; i < 360; i++) {
		float x = 0 + 4 * cos(i * a);
		float y = 0 + 4 * sin(i * a);
		glVertex3f(x+75, y+40, 5.7);
	}
	glEnd();
	glPopMatrix();
}

void tv() {
	//belakang
	glBegin(GL_QUADS);
	glColor3f(0, 0.05, 0.2);
	glVertex3f(-20.2, 30, -219.9);
	glVertex3f(-60.2, 30, -219.9);
	glVertex3f(-60.2, 50, -219.9);
	glVertex3f(-20.2, 50, -219.9);
	glEnd();

	//depan
	glBegin(GL_QUADS);
	glColor3f(0, 0.05, 0.2);
	glVertex3f(-20.2, 30, -218.4);
	glVertex3f(-60.2, 30, -218.4);
	glVertex3f(-60.2, 50, -218.4);
	glVertex3f(-20.2, 50, -218.4);
	glEnd();

	//kiri
	glBegin(GL_QUADS);
	glColor3f(0, 0.05, 0.2);
	glVertex3f(-60.2, 30, -219.9);
	glVertex3f(-60.2, 50, -219.9);
	glVertex3f(-60.2, 50, -218.4);
	glVertex3f(-60.2, 30, -218.4);
	glEnd();

	//kanan
	glBegin(GL_QUADS);
	glColor3f(0, 0.05, 0.2);
	glVertex3f(-20.2, 30, -219.9);
	glVertex3f(-20.2, 50, -219.9);
	glVertex3f(-20.2, 50, -218.4);
	glVertex3f(-20.2, 30, -218.4);
	glEnd();

	//layar
	glBegin(GL_QUADS);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(-20.7, 32, -218.35);
	glVertex3f(-59.7, 32, -218.35);
	glVertex3f(-59.7, 49.5, -218.35);
	glVertex3f(-20.7, 49.5, -218.35);
	glEnd();

	//tombol
	glBegin(GL_QUADS);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(-20.7, 30.85, -218.35);
	glVertex3f(-22.5, 30.85, -218.35);
	glVertex3f(-22.5, 31.15, -218.35);
	glVertex3f(-20.7, 31.15, -218.35);
	glEnd();
}

void soundbar(float y) {
	//depan
	glBegin(GL_QUADS);
	glColor3f(0, 0.05, 0.2);
	glVertex3f(-21.6, 22.5, -216.4);
	glVertex3f(-58.8, 22.5, -216.4);
	glVertex3f(-58.8, 25, -216.4);
	glVertex3f(-21.6, 25, -216.4);
	glEnd();

	//atas
	glBegin(GL_QUADS);
	glColor3f(0, 0.05, 0.2);
	glVertex3f(-21.6, 25, -216.4);
	glVertex3f(-58.8, 25, -216.4);
	glVertex3f(-58.8, 25, -218.4);
	glVertex3f(-21.6, 25, -218.4);
	glEnd();

	//belakang
	glBegin(GL_QUADS);
	glColor3f(0, 0.05, 0.2);
	glVertex3f(-21.6, 22.5, -218.4);
	glVertex3f(-58.8, 22.5, -218.4);
	glVertex3f(-58.8, 25, -218.4);
	glVertex3f(-21.6, 25, -218.4);
	glEnd();

	//kiri
	glBegin(GL_QUADS);
	glColor3f(0, 0.05, 0.2);
	glVertex3f(-58.8, 25, -216.4);
	glVertex3f(-58.8, 22.5, -216.4);
	glVertex3f(-58.8, 22.5, -218.4);
	glVertex3f(-58.8, 25, -218.4);
	glEnd();

	//kanan
	glBegin(GL_QUADS);
	glColor3f(0, 0.05, 0.2);
	glVertex3f(-21.6, 25, -216.4);
	glVertex3f(-21.6, 22.5, -216.4);
	glVertex3f(-21.6, 22.5, -218.4);
	glVertex3f(-21.6, 25, -218.4);
	glEnd();

	//strip
	glBegin(GL_LINE_STRIP);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(-24.6, 23+y, -216.35);
	glVertex3f(-55.8, 23+y, -216.35);
	glEnd();
}

void rakdinding() {
	//depan
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(-20.2, 22.45, -212.4);
	glVertex3f(-60.2, 22.45, -212.4);
	glVertex3f(-60.2, 21, -212.4);
	glVertex3f(-20.2, 21, -212.4);
	glEnd();

	//atas
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(-20.2, 22.45, -212.4);
	glVertex3f(-60.2, 22.45, -212.4);
	glVertex3f(-60.2, 22.45, -219.9);
	glVertex3f(-20.2, 22.45, -219.9);
	glEnd();

	//bawah
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(-20.2, 21, -212.4);
	glVertex3f(-60.2, 21, -212.4);
	glVertex3f(-60.2, 21, -219.9);
	glVertex3f(-20.2, 21, -219.9);
	glEnd();

	//belakang
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(-20.2, 22.45, -219.9);
	glVertex3f(-60.2, 22.45, -219.9);
	glVertex3f(-60.2, 21, -219.9);
	glVertex3f(-20.2, 21, -219.9);
	glEnd();

	//kiri
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(-60.2, 21, -212.4);
	glVertex3f(-60.2, 22.45, -212.4);
	glVertex3f(-60.2, 22.45, -219.9);
	glVertex3f(-60.2, 21, -219.9);
	glEnd();

	//kanan
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(-20.2, 21, -212.4);
	glVertex3f(-20.2, 22.45, -212.4);
	glVertex3f(-20.2, 22.45, -219.9);
	glVertex3f(-20.2, 21, -219.9);
	glEnd();
}

void matahari() {
	int i = 0, size = 200;
	double transparan = 1;
	for (i = 0; i < 5; i++) {
		glPushMatrix();
		glColor4f(1, 0.725, 0.039, transparan);
		glTranslatef(3000, 6000, 0);
		glutSolidSphere(size, 200, 200);
		glPopMatrix();
		transparan -= 0.2;
		size += 80;
	}
}

void sofa() {
	//Sofa
	glBegin(GL_QUADS);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3d(-140, 0, -92);
	glVertex3d(-90, 0, -92);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3d(-90, 15, -92);
	glVertex3d(-140, 15, -92);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3d(-140, 15, -92);
	glVertex3d(-90, 15, -92);
	glVertex3d(-90, 15, -89);
	glVertex3d(-140, 15, -89);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3d(-140, 0, -89);
	glVertex3d(-90, 0, -89);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3d(-90, 15, -89);
	glVertex3d(-140, 15, -89);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3d(-140, 0, -92);
	glVertex3d(-140, 0, -89);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3d(-140, 15, -89);
	glVertex3d(-140, 15, -92);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3d(-90, 0, -92);
	glVertex3d(-90, 0, -89);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3d(-90, 15, -89);
	glVertex3d(-90, 15, -92);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3d(-140, 7, -89);
	glVertex3d(-90, 7, -89);
	glVertex3d(-90, 7, -82);
	glVertex3d(-140, 7, -82);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3d(-135, 7, -82);
	glVertex3d(-95, 7, -82);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3d(-95, 0, -82);
	glVertex3d(-135, 0, -82);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3d(-140, 0, -88.9);
	glVertex3d(-135, 0, -88.9);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3d(-135, 11, -88.9);
	glVertex3d(-140, 11, -88.9);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3d(-140, 0, -89);
	glVertex3d(-140, 0, -82);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3d(-140, 11, -82);
	glVertex3d(-140, 11, -89);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3d(-135, 0, -89);
	glVertex3d(-135, 0, -82);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3d(-135, 11, -82);
	glVertex3d(-135, 11, -89);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3d(-140, 0, -82);
	glVertex3d(-135, 0, -82);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3d(-135, 11, -82);
	glVertex3d(-140, 11, -82);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3d(-140, 11, -88.9);
	glVertex3d(-135, 11, -88.9);
	glVertex3d(-135, 11, -82);
	glVertex3d(-140, 11, -82);
	glEnd();

	glBegin(GL_QUADS); //
	glColor3f(0.3, 0.3, 0.3);
	glVertex3d(-95, 0, -88.9);
	glVertex3d(-90, 0, -88.9);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3d(-90, 11, -88.9);
	glVertex3d(-95, 11, -88.9);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3d(-95, 0, -89);
	glVertex3d(-95, 0, -82);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3d(-95, 11, -82);
	glVertex3d(-95, 11, -89);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3d(-90, 0, -89);
	glVertex3d(-90, 0, -82);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3d(-90, 11, -82);
	glVertex3d(-90, 11, -89);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3d(-95, 0, -82);
	glVertex3d(-90, 0, -82);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3d(-90, 11, -82);
	glVertex3d(-95, 11, -82);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3d(-95, 11, -88.9);
	glVertex3d(-90, 11, -88.9);
	glVertex3d(-90, 11, -82);
	glVertex3d(-95, 11, -82);
	glEnd();
}


void draw() {
	tv(); 
	for (float i = 0; i < 4; i++)
	{
		soundbar(i * 0.5);
	}
	rakdinding();
	jam();
	
	matahari();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(152, 8, 144);
	sofa();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(204, 8, 25);
	sofa();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_LINE_LOOP);

	//Lantai halaman
	glBegin(GL_QUADS);//bawah
	glColor3f(0.631, 0.631, 0.631);
	glVertex3f(-70, 0, 17);
	glVertex3f(70, 0, 17);
	glVertex3f(70, 0, -220);
	glVertex3f(-70, 0, -220);
	glEnd();
	glBegin(GL_QUADS);//atas
	glColor3f(0.784, 0.694, 0.694);
	glVertex3f(-70, 8, -35);
	glVertex3f(70, 8, -35);
	glVertex3f(70, 8, -220);
	glVertex3f(-70, 8, -220);
	glEnd();
	glBegin(GL_QUADS);//teras
	glColor3f(0.258, 0.258, 0.258);
	glVertex3f(-70, 8, 0);
	glVertex3f(70, 8, 0);
	glVertex3f(70, 8, -35);
	glVertex3f(-70, 8, -35);
	glEnd();
	glBegin(GL_QUADS);//teras
	glColor3f(0.258, 0.258, 0.258);
	glVertex3f(-70, 8.1, 0);
	glVertex3f(6, 8.1, 0);
	glVertex3f(6, 8.1, -35);
	glVertex3f(-70, 8.1, -35);
	glEnd();
	//atap
	glBegin(GL_QUADS);//atas seluruh
	glColor3f(1, 0.937, 0.901);
	glVertex3f(-70.2, 65, 0.1);
	glVertex3f(70.2, 65, 0.1);
	glVertex3f(70.2, 65, -220.1);
	glVertex3f(-70.2, 65, -220.1);
	glEnd();
	glBegin(GL_QUADS);//atas teras
	glColor3f(0.870, 0.870, 0.870);
	glVertex3f(-70.2, 65, 0.1);
	glVertex3f(70.2, 65, 0.1);
	glVertex3f(70.2, 75, -35);
	glVertex3f(-70.2, 75, -35);
	glEnd();
	glBegin(GL_QUADS);//atas belakang
	glColor3f(0.494, 0.317, 0.243);
	glVertex3f(-70.2, 75, -35);
	glVertex3f(70.2, 75, -35);
	glVertex3f(70.2, 120, -128);
	glVertex3f(-70.2, 120, -128);
	glEnd();
	glBegin(GL_QUADS);//atas belakang
	glColor3f(0.494, 0.317, 0.243);
	glVertex3f(-70.2, 120, -128);
	glVertex3f(70.2, 120, -128);
	glVertex3f(70.2, 65, -220);
	glVertex3f(-70.2, 65, -220);
	glEnd();
	glBegin(GL_POLYGON);//atas kanan
	glColor3f(0.631, 0.631, 0.631);
	glVertex3f(-70.2, 65, 0.1);
	glVertex3f(-70.2, 75, -35);
	glVertex3f(-70.2, 120, -128);
	glVertex3f(-70.2, 65, -220);
	glEnd();
	glBegin(GL_POLYGON);//atas kanan
	glColor3f(0.631, 0.631, 0.631);
	glVertex3f(70.2, 65, 0.1);
	glVertex3f(70.2, 75, -35);
	glVertex3f(70.2, 120, -128);
	glVertex3f(70.2, 65, -220);
	glEnd();

	glBegin(GL_LINES);//atas
	glColor3f(0, 0, 0);
	glVertex3f(-70.2, 120, -128);
	glVertex3f(70.2, 120, -128);
	glEnd();

	//tembok kanan rumah
	glBegin(GL_QUADS);
	glColor3f(0.631, 0.631, 0.631);
	glVertex3f(70.2, 0, 2);
	glVertex3f(70.2, 65, 2);
	glVertex3f(70.2, 65, -220);
	glVertex3f(70.2, 0, -220);
	glEnd();
	//tembok kiri rumah
	glBegin(GL_QUADS);
	glColor3f(0.631, 0.631, 0.631);
	glVertex3f(-70.2, 0, 2);
	glVertex3f(-70.2, 65, 2);
	glVertex3f(-70.2, 65, -220);
	glVertex3f(-70.2, 0, -220);
	glEnd();
	//tembok belakang rumah
	glBegin(GL_QUADS);
	glColor3f(0.631, 0.631, 0.631);
	glVertex3f(70.2, 0, -220);
	glVertex3f(-70.2, 0, -220);
	glVertex3f(-70.2, 65, -220);
	glVertex3f(70.2, 65, -220);
	glEnd();

	//tanjakan depan
	glBegin(GL_QUADS);
	glColor3f(0.258, 0.956, 0.203);
	glVertex3f(-15, 0, 0);
	glVertex3f(15, 0, 0);
	glVertex3f(15, 8, 0);
	glVertex3f(-15, 8, 0);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.560, 0.074, 0);
	glVertex3f(-15, 8, 0);
	glVertex3f(15, 8, 0);
	glVertex3f(15, 8, 2);
	glVertex3f(-15, 8, 2);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.952, 0.509, 0.509);
	glVertex3f(-15, 0, 17);
	glVertex3f(15, 0, 17);
	glVertex3f(15, 8, 2);
	glVertex3f(-15, 8, 2);
	glEnd();

	//pilar sebelah kanan gerbang
	glBegin(GL_QUADS);//depan
	glColor3f(0.431, 0.874, 0.305);
	glVertex3f(9, 0, 2);
	glVertex3f(15, 0, 2);
	glVertex3f(15, 40, 2);
	glVertex3f(9, 40, 2);
	glEnd();
	glBegin(GL_QUADS);//blakang
	glColor3f(0.431, 0.874, 0.305);
	glVertex3f(9, 0, -4);
	glVertex3f(15, 0, -4);
	glVertex3f(15, 40, -4);
	glVertex3f(9, 40, -4);
	glEnd();
	glBegin(GL_QUADS);//kiri
	glColor3f(0.431, 0.874, 0.305);
	glVertex3f(9, 0, 2);
	glVertex3f(9, 40, 2);
	glVertex3f(9, 40, -4);
	glVertex3f(9, 0, -4);
	glEnd();
	glBegin(GL_QUADS);//kanan
	glColor3f(0.431, 0.874, 0.305);
	glVertex3f(15, 0, 2);
	glVertex3f(15, 40, 2);
	glVertex3f(15, 40, -4);
	glVertex3f(15, 0, -4);
	glEnd();

	//pilar sebelah kiri gerbang
	glBegin(GL_QUADS);//depan
	glColor3f(0.431, 0.874, 0.305);
	glVertex3f(-15, 0, 2);
	glVertex3f(-9, 0, 2);
	glVertex3f(-9, 40, 2);
	glVertex3f(-15, 40, 2);
	glEnd();
	glBegin(GL_QUADS);//blakang
	glColor3f(0.431, 0.874, 0.305);
	glVertex3f(-15, 0, -4);
	glVertex3f(-9, 0, -4);
	glVertex3f(-9, 40, -4);
	glVertex3f(-15, 40, -4);
	glEnd();
	glBegin(GL_QUADS);//kiri
	glColor3f(0.431, 0.874, 0.305);
	glVertex3f(-15, 0, 2);
	glVertex3f(-15, 40, 2);
	glVertex3f(-15, 40, -4);
	glVertex3f(-15, 0, -4);
	glEnd();
	glBegin(GL_QUADS);//kanan
	glColor3f(0.431, 0.874, 0.305);
	glVertex3f(-9, 0, 2);
	glVertex3f(-9, 40, 2);
	glVertex3f(-9, 40, -4);
	glVertex3f(-9, 0, -4);
	glEnd();


	//tembok kiri
	glBegin(GL_QUADS);//depan
	glColor3f(0.431, 0.874, 0.305);
	glVertex3f(-15, 0, 0);
	glVertex3f(-70, 0, 0);
	glVertex3f(-70, 40, 0);
	glVertex3f(-15, 40, 0);
	glEnd();
	glBegin(GL_QUADS);//blakang
	glColor3f(0.431, 0.874, 0.305);
	glVertex3f(-15, 0, -6);
	glVertex3f(-70, 0, -6);
	glVertex3f(-70, 40, -6);
	glVertex3f(-15, 40, -6);
	glEnd();
	glBegin(GL_QUADS);//kiri
	glColor3f(0.431, 0.874, 0.305);
	glVertex3f(-15, 0, 0);
	glVertex3f(-15, 40, 0);
	glVertex3f(-15, 40, -6);
	glVertex3f(-15, 0, -6);
	glEnd();
	glBegin(GL_QUADS);//kanan
	glColor3f(0.431, 0.874, 0.305);
	glVertex3f(-70, 0, 0);
	glVertex3f(-70, 40, 0);
	glVertex3f(-70, 40, -6);
	glVertex3f(-70, 0, -6);
	glEnd();

	//tembok kanan
	glBegin(GL_QUADS);//depan
	glColor3f(0.431, 0.874, 0.305);
	glVertex3f(15, 0, 0);
	glVertex3f(70, 0, 0);
	glVertex3f(70, 40, 0);
	glVertex3f(15, 40, 0);
	glEnd();
	glBegin(GL_QUADS);//blakang
	glColor3f(0.431, 0.874, 0.305);
	glVertex3f(15, 0, -6);
	glVertex3f(70, 0, -6);
	glVertex3f(70, 40, -6);
	glVertex3f(15, 40, -6);
	glEnd();
	glBegin(GL_QUADS);//kiri
	glColor3f(0.431, 0.874, 0.305);
	glVertex3f(15, 0, 0);
	glVertex3f(15, 40, 0);
	glVertex3f(15, 40, -6);
	glVertex3f(15, 0, -6);
	glEnd();
	glBegin(GL_QUADS);//kanan
	glColor3f(0.431, 0.874, 0.305);
	glVertex3f(70, 0, 0);
	glVertex3f(70, 40, 0);
	glVertex3f(70, 40, -6);
	glVertex3f(70, 0, -6);
	glEnd();

	//putih tembok kanan
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(15, 10, 0.1);
	glVertex3f(20, 10, 0.1);
	glVertex3f(20, 33, 0.1);
	glVertex3f(15, 33, 0.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(21, 10, 0.1);
	glVertex3f(26, 10, 0.1);
	glVertex3f(26, 33, 0.1);
	glVertex3f(21, 33, 0.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(27, 10, 0.1);
	glVertex3f(32, 10, 0.1);
	glVertex3f(32, 33, 0.1);
	glVertex3f(27, 33, 0.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(33, 10, 0.1);
	glVertex3f(38, 10, 0.1);
	glVertex3f(38, 33, 0.1);
	glVertex3f(33, 33, 0.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(39, 10, 0.1);
	glVertex3f(44, 10, 0.1);
	glVertex3f(44, 33, 0.1);
	glVertex3f(39, 33, 0.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(45, 10, 0.1);
	glVertex3f(50, 10, 0.1);
	glVertex3f(50, 33, 0.1);
	glVertex3f(45, 33, 0.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(51, 10, 0.1);
	glVertex3f(56, 10, 0.1);
	glVertex3f(56, 33, 0.1);
	glVertex3f(51, 33, 0.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(57, 10, 0.1);
	glVertex3f(62, 10, 0.1);
	glVertex3f(62, 33, 0.1);
	glVertex3f(57, 33, 0.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(63, 10, 0.1);
	glVertex3f(68, 10, 0.1);
	glVertex3f(68, 33, 0.1);
	glVertex3f(63, 33, 0.1);
	glEnd();

	//putih tembok kanan belakang
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(15, 10, -6.1);
	glVertex3f(20, 10, -6.1);
	glVertex3f(20, 33, -6.1);
	glVertex3f(15, 33, -6.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(21, 10, -6.1);
	glVertex3f(26, 10, -6.1);
	glVertex3f(26, 33, -6.1);
	glVertex3f(21, 33, -6.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(27, 10, -6.1);
	glVertex3f(32, 10, -6.1);
	glVertex3f(32, 33, -6.1);
	glVertex3f(27, 33, -6.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(33, 10, -6.1);
	glVertex3f(38, 10, -6.1);
	glVertex3f(38, 33, -6.1);
	glVertex3f(33, 33, -6.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(39, 10, -6.1);
	glVertex3f(44, 10, -6.1);
	glVertex3f(44, 33, -6.1);
	glVertex3f(39, 33, -6.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(45, 10, -6.1);
	glVertex3f(50, 10, -6.1);
	glVertex3f(50, 33, -6.1);
	glVertex3f(45, 33, -6.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(51, 10, -6.1);
	glVertex3f(56, 10, -6.1);
	glVertex3f(56, 33, -6.1);
	glVertex3f(51, 33, -6.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(57, 10, -6.1);
	glVertex3f(62, 10, -6.1);
	glVertex3f(62, 33, -6.1);
	glVertex3f(57, 33, -6.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(63, 10, -6.1);
	glVertex3f(68, 10, -6.1);
	glVertex3f(68, 33, -6.1);
	glVertex3f(63, 33, -6.1);
	glEnd();

	//putih tembok kiri
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(-15, 10, 0.1);
	glVertex3f(-20, 10, 0.1);
	glVertex3f(-20, 33, 0.1);
	glVertex3f(-15, 33, 0.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(-21, 10, 0.1);
	glVertex3f(-26, 10, 0.1);
	glVertex3f(-26, 33, 0.1);
	glVertex3f(-21, 33, 0.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(-27, 10, 0.1);
	glVertex3f(-32, 10, 0.1);
	glVertex3f(-32, 33, 0.1);
	glVertex3f(-27, 33, 0.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(-33, 10, 0.1);
	glVertex3f(-38, 10, 0.1);
	glVertex3f(-38, 33, 0.1);
	glVertex3f(-33, 33, 0.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(-39, 10, 0.1);
	glVertex3f(-44, 10, 0.1);
	glVertex3f(-44, 33, 0.1);
	glVertex3f(-39, 33, 0.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(-45, 10, 0.1);
	glVertex3f(-50, 10, 0.1);
	glVertex3f(-50, 33, 0.1);
	glVertex3f(-45, 33, 0.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(-51, 10, 0.1);
	glVertex3f(-56, 10, 0.1);
	glVertex3f(-56, 33, 0.1);
	glVertex3f(-51, 33, 0.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(-57, 10, 0.1);
	glVertex3f(-62, 10, 0.1);
	glVertex3f(-62, 33, 0.1);
	glVertex3f(-57, 33, 0.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(-63, 10, 0.1);
	glVertex3f(-68, 10, 0.1);
	glVertex3f(-68, 33, 0.1);
	glVertex3f(-63, 33, 0.1);
	glEnd();

	//putih tembok kiri belakang
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(-15, 10, -6.1);
	glVertex3f(-20, 10, -6.1);
	glVertex3f(-20, 33, -6.1);
	glVertex3f(-15, 33, -6.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(-21, 10, -6.1);
	glVertex3f(-26, 10, -6.1);
	glVertex3f(-26, 33, -6.1);
	glVertex3f(-21, 33, -6.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(-27, 10, -6.1);
	glVertex3f(-32, 10, -6.1);
	glVertex3f(-32, 33, -6.1);
	glVertex3f(-27, 33, -6.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(-33, 10, -6.1);
	glVertex3f(-38, 10, -6.1);
	glVertex3f(-38, 33, -6.1);
	glVertex3f(-33, 33, -6.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(-39, 10, -6.1);
	glVertex3f(-44, 10, -6.1);
	glVertex3f(-44, 33, -6.1);
	glVertex3f(-39, 33, -6.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(-45, 10, -6.1);
	glVertex3f(-50, 10, -6.1);
	glVertex3f(-50, 33, -6.1);
	glVertex3f(-45, 33, -6.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(-51, 10, -6.1);
	glVertex3f(-56, 10, -6.1);
	glVertex3f(-56, 33, -6.1);
	glVertex3f(-51, 33, -6.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(-57, 10, -6.1);
	glVertex3f(-62, 10, -6.1);
	glVertex3f(-62, 33, -6.1);
	glVertex3f(-57, 33, -6.1);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(1, 1, 1);
	glVertex3f(-63, 10, -6.1);
	glVertex3f(-68, 10, -6.1);
	glVertex3f(-68, 33, -6.1);
	glVertex3f(-63, 33, -6.1);
	glEnd();

	//item tembok kanan
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(16.5, 10.5, 0.2);
	glVertex3f(18.5, 10.5, 0.2);
	glVertex3f(18.5, 32.5, 0.2);
	glVertex3f(16.5, 32.5, 0.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(22.5, 10.5, 0.2);
	glVertex3f(24.5, 10.5, 0.2);
	glVertex3f(24.5, 32.5, 0.2);
	glVertex3f(22.5, 32.5, 0.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(28.5, 10.5, 0.2);
	glVertex3f(30.5, 10.5, 0.2);
	glVertex3f(30.5, 32.5, 0.2);
	glVertex3f(28.5, 32.5, 0.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(34.5, 10.5, 0.2);
	glVertex3f(36.5, 10.5, 0.2);
	glVertex3f(36.5, 32.5, 0.2);
	glVertex3f(34.5, 32.5, 0.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(40.5, 10.5, 0.2);
	glVertex3f(42.5, 10.5, 0.2);
	glVertex3f(42.5, 32.5, 0.2);
	glVertex3f(40.5, 32.5, 0.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(46.5, 10.5, 0.2);
	glVertex3f(48.5, 10.5, 0.2);
	glVertex3f(48.5, 32.5, 0.2);
	glVertex3f(46.5, 32.5, 0.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(52.5, 10.5, 0.2);
	glVertex3f(54.5, 10.5, 0.2);
	glVertex3f(54.5, 32.5, 0.2);
	glVertex3f(52.5, 32.5, 0.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(58.5, 10.5, 0.2);
	glVertex3f(60.5, 10.5, 0.2);
	glVertex3f(60.5, 32.5, 0.2);
	glVertex3f(58.5, 32.5, 0.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(64.5, 10.5, 0.2);
	glVertex3f(66.5, 10.5, 0.2);
	glVertex3f(66.5, 32.5, 0.2);
	glVertex3f(64.5, 32.5, 0.2);
	glEnd();

	//item tembok kanan belakang
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(16.5, 10.5, -6.2);
	glVertex3f(18.5, 10.5, -6.2);
	glVertex3f(18.5, 32.5, -6.2);
	glVertex3f(16.5, 32.5, -6.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(22.5, 10.5, -6.2);
	glVertex3f(24.5, 10.5, -6.2);
	glVertex3f(24.5, 32.5, -6.2);
	glVertex3f(22.5, 32.5, -6.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(28.5, 10.5, -6.2);
	glVertex3f(30.5, 10.5, -6.2);
	glVertex3f(30.5, 32.5, -6.2);
	glVertex3f(28.5, 32.5, -6.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(34.5, 10.5, -6.2);
	glVertex3f(36.5, 10.5, -6.2);
	glVertex3f(36.5, 32.5, -6.2);
	glVertex3f(34.5, 32.5, -6.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(40.5, 10.5, -6.2);
	glVertex3f(42.5, 10.5, -6.2);
	glVertex3f(42.5, 32.5, -6.2);
	glVertex3f(40.5, 32.5, -6.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(46.5, 10.5, -6.2);
	glVertex3f(48.5, 10.5, -6.2);
	glVertex3f(48.5, 32.5, -6.2);
	glVertex3f(46.5, 32.5, -6.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(52.5, 10.5, -6.2);
	glVertex3f(54.5, 10.5, -6.2);
	glVertex3f(54.5, 32.5, -6.2);
	glVertex3f(52.5, 32.5, -6.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(58.5, 10.5, -6.2);
	glVertex3f(60.5, 10.5, -6.2);
	glVertex3f(60.5, 32.5, -6.2);
	glVertex3f(58.5, 32.5, -6.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(64.5, 10.5, -6.2);
	glVertex3f(66.5, 10.5, -6.2);
	glVertex3f(66.5, 32.5, -6.2);
	glVertex3f(64.5, 32.5, -6.2);
	glEnd();

	//item tembok kiri
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(-16.5, 10.5, 0.2);
	glVertex3f(-18.5, 10.5, 0.2);
	glVertex3f(-18.5, 32.5, 0.2);
	glVertex3f(-16.5, 32.5, 0.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(-22.5, 10.5, 0.2);
	glVertex3f(-24.5, 10.5, 0.2);
	glVertex3f(-24.5, 32.5, 0.2);
	glVertex3f(-22.5, 32.5, 0.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(-28.5, 10.5, 0.2);
	glVertex3f(-30.5, 10.5, 0.2);
	glVertex3f(-30.5, 32.5, 0.2);
	glVertex3f(-28.5, 32.5, 0.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(-34.5, 10.5, 0.2);
	glVertex3f(-36.5, 10.5, 0.2);
	glVertex3f(-36.5, 32.5, 0.2);
	glVertex3f(-34.5, 32.5, 0.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(-40.5, 10.5, 0.2);
	glVertex3f(-42.5, 10.5, 0.2);
	glVertex3f(-42.5, 32.5, 0.2);
	glVertex3f(-40.5, 32.5, 0.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(-46.5, 10.5, 0.2);
	glVertex3f(-48.5, 10.5, 0.2);
	glVertex3f(-48.5, 32.5, 0.2);
	glVertex3f(-46.5, 32.5, 0.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(-52.5, 10.5, 0.2);
	glVertex3f(-54.5, 10.5, 0.2);
	glVertex3f(-54.5, 32.5, 0.2);
	glVertex3f(-52.5, 32.5, 0.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(-58.5, 10.5, 0.2);
	glVertex3f(-60.5, 10.5, 0.2);
	glVertex3f(-60.5, 32.5, 0.2);
	glVertex3f(-58.5, 32.5, 0.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(-64.5, 10.5, 0.2);
	glVertex3f(-66.5, 10.5, 0.2);
	glVertex3f(-66.5, 32.5, 0.2);
	glVertex3f(-64.5, 32.5, 0.2);
	glEnd();

	//item tembok kiri belakang
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(-16.5, 10.5, -6.2);
	glVertex3f(-18.5, 10.5, -6.2);
	glVertex3f(-18.5, 32.5, -6.2);
	glVertex3f(-16.5, 32.5, -6.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(-22.5, 10.5, -6.2);
	glVertex3f(-24.5, 10.5, -6.2);
	glVertex3f(-24.5, 32.5, -6.2);
	glVertex3f(-22.5, 32.5, -6.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(-28.5, 10.5, -6.2);
	glVertex3f(-30.5, 10.5, -6.2);
	glVertex3f(-30.5, 32.5, -6.2);
	glVertex3f(-28.5, 32.5, -6.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(-34.5, 10.5, -6.2);
	glVertex3f(-36.5, 10.5, -6.2);
	glVertex3f(-36.5, 32.5, -6.2);
	glVertex3f(-34.5, 32.5, -6.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(-40.5, 10.5, -6.2);
	glVertex3f(-42.5, 10.5, -6.2);
	glVertex3f(-42.5, 32.5, -6.2);
	glVertex3f(-40.5, 32.5, -6.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(-46.5, 10.5, -6.2);
	glVertex3f(-48.5, 10.5, -6.2);
	glVertex3f(-48.5, 32.5, -6.2);
	glVertex3f(-46.5, 32.5, -6.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(-52.5, 10.5, -6.2);
	glVertex3f(-54.5, 10.5, -6.2);
	glVertex3f(-54.5, 32.5, -6.2);
	glVertex3f(-52.5, 32.5, -6.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(-58.5, 10.5, -6.2);
	glVertex3f(-60.5, 10.5, -6.2);
	glVertex3f(-60.5, 32.5, -6.2);
	glVertex3f(-58.5, 32.5, -6.2);
	glEnd();
	glBegin(GL_POLYGON);//depan
	glColor3f(0.549, 0.549, 0.549);
	glVertex3f(-64.5, 10.5, -6.2);
	glVertex3f(-66.5, 10.5, -6.2);
	glVertex3f(-66.5, 32.5, -6.2);
	glVertex3f(-64.5, 32.5, -6.2);
	glEnd();

	//atas temok kanan
	glBegin(GL_QUADS);//depan
	glColor3f(0.878, 0.396, 0.101);
	glVertex3f(15, 38, 1.5);
	glVertex3f(70, 38, 1.5);
	glVertex3f(70, 40, 1.5);
	glVertex3f(15, 40, 1.5);
	glEnd();
	glBegin(GL_QUADS);//bawah
	glColor3f(0.878, 0.396, 0.101);
	glVertex3f(15, 38, 1.5);
	glVertex3f(70, 38, 1.5);
	glVertex3f(70, 38, -6);
	glVertex3f(15, 38, -6);
	glEnd();
	glBegin(GL_QUADS);//atas
	glColor3f(0.878, 0.396, 0.101);
	glVertex3f(15, 40, 1.5);
	glVertex3f(70.1, 40, 1.5);
	glVertex3f(70.1, 40, -6.1);
	glVertex3f(15, 40, -6.1);
	glEnd();
	glBegin(GL_QUADS);//belakang
	glColor3f(0.878, 0.396, 0.101);
	glVertex3f(15, 38, -6.1);
	glVertex3f(70, 38, -6.1);
	glVertex3f(70, 40, -6.1);
	glVertex3f(15, 40, -6.1);
	glEnd();
	glBegin(GL_QUADS);//kiri
	glColor3f(0.878, 0.396, 0.101);
	glVertex3f(70.1, 38, -6.1);
	glVertex3f(70.1, 40, -6.1);
	glVertex3f(70.1, 40, 1.5);
	glVertex3f(70.1, 38, 1.5);
	glEnd();
	//ataspilarkanan
	glBegin(GL_QUADS);//depan
	glColor3f(0.878, 0.396, 0.101);
	glVertex3f(9, 38, 3.5);
	glVertex3f(16.5, 38, 3.5);
	glVertex3f(16.5, 40, 3.5);
	glVertex3f(9, 40, 3.5);
	glEnd();
	glBegin(GL_QUADS);//belakang
	glColor3f(0.878, 0.396, 0.101);
	glVertex3f(9, 38, -4.1);
	glVertex3f(16.5, 38, -4.1);
	glVertex3f(16.5, 40, -4.1);
	glVertex3f(9, 40, -4.1);
	glEnd();
	glBegin(GL_QUADS);//kiri
	glColor3f(0.878, 0.396, 0.101);
	glVertex3f(8.9, 38, 3.5);
	glVertex3f(8.9, 38, -4.1);
	glVertex3f(8.9, 40, -4.1);
	glVertex3f(8.9, 40, 3.5);
	glEnd();
	glBegin(GL_QUADS);//kiri
	glColor3f(0.878, 0.396, 0.101);
	glVertex3f(16.5, 38, 3.5);
	glVertex3f(16.5, 38, -4.1);
	glVertex3f(16.5, 40, -4.1);
	glVertex3f(16.5, 40, 3.5);
	glEnd();
	glBegin(GL_QUADS);//atas
	glColor3f(0.878, 0.396, 0.101);
	glVertex3f(8.9, 40, 3.5);
	glVertex3f(8.9, 40, -4.1);
	glVertex3f(16.5, 40, -4.1);
	glVertex3f(16.5, 40, 3.5);
	glEnd();

	//atas temok kiri
	glBegin(GL_QUADS);//depan
	glColor3f(0.878, 0.396, 0.101);
	glVertex3f(-15, 38, 1.5);
	glVertex3f(-70, 38, 1.5);
	glVertex3f(-70, 40, 1.5);
	glVertex3f(-15, 40, 1.5);
	glEnd();
	glBegin(GL_QUADS);//bawah
	glColor3f(0.878, 0.396, 0.101);
	glVertex3f(-15, 38, 1.5);
	glVertex3f(-70, 38, 1.5);
	glVertex3f(-70, 38, -6);
	glVertex3f(-15, 38, -6);
	glEnd();
	glBegin(GL_QUADS);//atas
	glColor3f(0.878, 0.396, 0.101);
	glVertex3f(-15, 40, 1.5);
	glVertex3f(-70.1, 40, 1.5);
	glVertex3f(-70.1, 40, -6.1);
	glVertex3f(-15, 40, -6.1);
	glEnd();
	glBegin(GL_QUADS);//belakang
	glColor3f(0.878, 0.396, 0.101);
	glVertex3f(-15, 38, -6.1);
	glVertex3f(-70, 38, -6.1);
	glVertex3f(-70, 40, -6.1);
	glVertex3f(-15, 40, -6.1);
	glEnd();
	glBegin(GL_QUADS);//kiri
	glColor3f(0.878, 0.396, 0.101);
	glVertex3f(-70.1, 38, -6.1);
	glVertex3f(-70.1, 40, -6.1);
	glVertex3f(-70.1, 40, 1.5);
	glVertex3f(-70.1, 38, 1.5);
	glEnd();
	//ataspilarkiri
	glBegin(GL_QUADS);//depan
	glColor3f(0.878, 0.396, 0.101);
	glVertex3f(-9, 38, 3.5);
	glVertex3f(-16.5, 38, 3.5);
	glVertex3f(-16.5, 40, 3.5);
	glVertex3f(-9, 40, 3.5);
	glEnd();
	glBegin(GL_QUADS);//belakang
	glColor3f(0.878, 0.396, 0.101);
	glVertex3f(-9, 38, -4.1);
	glVertex3f(-16.5, 38, -4.1);
	glVertex3f(-16.5, 40, -4.1);
	glVertex3f(-9, 40, -4.1);
	glEnd();
	glBegin(GL_QUADS);//kiri
	glColor3f(0.878, 0.396, 0.101);
	glVertex3f(-8.9, 38, 3.5);
	glVertex3f(-8.9, 38, -4.1);
	glVertex3f(-8.9, 40, -4.1);
	glVertex3f(-8.9, 40, 3.5);
	glEnd();
	glBegin(GL_QUADS);//kiri
	glColor3f(0.878, 0.396, 0.101);
	glVertex3f(-16.5, 38, 3.5);
	glVertex3f(-16.5, 38, -4.1);
	glVertex3f(-16.5, 40, -4.1);
	glVertex3f(-16.5, 40, 3.5);
	glEnd();
	glBegin(GL_QUADS);//atas
	glColor3f(0.878, 0.396, 0.101);
	glVertex3f(-8.9, 40, 3.5);
	glVertex3f(-8.9, 40, -4.1);
	glVertex3f(-16.5, 40, -4.1);
	glVertex3f(-16.5, 40, 3.5);
	glEnd();

	glBegin(GL_LINES);//tiang
	glColor3f(0.941, 0.478, 0.2);
	glVertex3f(65, 40, -2);
	glVertex3f(65, 65, -2);
	glEnd();
	glBegin(GL_LINES);//tiang
	glColor3f(0.941, 0.478, 0.2);
	glVertex3f(-65, 40, -2);
	glVertex3f(-65, 65, -2);
	glEnd();
	glBegin(GL_LINES);//tiang
	glColor3f(0.941, 0.478, 0.2);
	glVertex3f(-18, 40, -2);
	glVertex3f(-18, 65, -2);
	glEnd();

	//tembok kanan pintu
	glBegin(GL_QUADS);
	glColor3f(0.796, 0.772, 0.486);
	glVertex3f(70.2, 0, -35);
	glVertex3f(70.2, 65, -35);
	glVertex3f(6, 65, -35);
	glVertex3f(6, 0, -35);
	glEnd();
	//antara kanan dengan pintu
	glBegin(GL_QUADS);
	glColor3f(0.796, 0.772, 0.486);
	glVertex3f(6, 0, -35);
	glVertex3f(6, 65, -35);
	glVertex3f(6, 65, -50);
	glVertex3f(6, 0, -50);
	glEnd();
	//tembok pintu
	glBegin(GL_QUADS);
	glColor3f(0.796, 0.772, 0.486);
	glVertex3f(-9, 0, -50);
	glVertex3f(-9, 65, -50);
	glVertex3f(-70, 65, -50);
	glVertex3f(-70, 0, -50);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.796, 0.772, 0.486);
	glVertex3f(6, 54, -50);
	glVertex3f(6, 65, -50);
	glVertex3f(-9, 65, -50);
	glVertex3f(-9, 54, -50);
	glEnd();

	//jendela kanan pintu
	glBegin(GL_QUADS);
	glColor3f(0.364, 0.117, 0.015);
	glVertex3f(60, 26, -34.9);
	glVertex3f(60, 55, -34.9);
	glVertex3f(45, 55, -34.9);
	glVertex3f(45, 26, -34.9);
	glEnd();
	//ventilasi
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex3f(59, 50, -34.8);
	glVertex3f(59, 54, -34.8);
	glVertex3f(46, 54, -34.8);
	glVertex3f(46, 50, -34.8);
	glEnd();
	//frame
	glBegin(GL_QUADS);
	glColor3f(0.678, 0.678, 0.678);
	glVertex3f(59, 27, -34.8);
	glVertex3f(59, 48, -34.8);
	glVertex3f(46, 48, -34.8);
	glVertex3f(46, 27, -34.8);
	glEnd();
	//kaca
	glBegin(GL_QUADS);//kiri
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(52, 28, -34.7);
	glVertex3f(52, 34, -34.7);
	glVertex3f(47, 34, -34.7);
	glVertex3f(47, 28, -34.7);
	glEnd();
	glBegin(GL_QUADS);//kiri
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(52, 35, -34.7);
	glVertex3f(52, 41, -34.7);
	glVertex3f(47, 41, -34.7);
	glVertex3f(47, 35, -34.7);
	glEnd();
	glBegin(GL_QUADS);//kiri
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(52, 42, -34.7);
	glVertex3f(52, 47, -34.7);
	glVertex3f(47, 47, -34.7);
	glVertex3f(47, 42, -34.7);
	glEnd();

	//jendela kanan pintu
	glBegin(GL_QUADS);
	glColor3f(0.364, 0.117, 0.015);
	glVertex3f(60, 26, -34.9);
	glVertex3f(60, 55, -34.9);
	glVertex3f(45, 55, -34.9);
	glVertex3f(45, 26, -34.9);
	glEnd();
	//ventilasi
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex3f(59, 50, -34.8);
	glVertex3f(59, 54, -34.8);
	glVertex3f(46, 54, -34.8);
	glVertex3f(46, 50, -34.8);
	glEnd();
	//frame
	glBegin(GL_QUADS);
	glColor3f(0.678, 0.678, 0.678);
	glVertex3f(59, 27, -34.8);
	glVertex3f(59, 48, -34.8);
	glVertex3f(46, 48, -34.8);
	glVertex3f(46, 27, -34.8);
	glEnd();
	//kaca
	glBegin(GL_QUADS);//kanan
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(58, 28, -34.7);
	glVertex3f(58, 34, -34.7);
	glVertex3f(53, 34, -34.7);
	glVertex3f(53, 28, -34.7);
	glEnd();
	glBegin(GL_QUADS);//kanan
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(58, 35, -34.7);
	glVertex3f(58, 41, -34.7);
	glVertex3f(53, 41, -34.7);
	glVertex3f(53, 35, -34.7);
	glEnd();
	glBegin(GL_QUADS);//kanan
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(58, 42, -34.7);
	glVertex3f(58, 47, -34.7);
	glVertex3f(53, 47, -34.7);
	glVertex3f(53, 42, -34.7);
	glEnd();

	//pintu
	glBegin(GL_QUADS);
	glColor3f(0.364, 0.117, 0.015);
	glVertex3f(6, 0, -50);
	glVertex3f(6, 54, -50);
	glVertex3f(-9, 54, -50);
	glVertex3f(-9, 0, -50);
	glEnd();
	glBegin(GL_QUADS);//daun pintu
	glColor3f(0.219, 0.023, 0.023);
	glVertex3f(5, 10, -49.9);
	glVertex3f(5, 48, -49.9);
	glVertex3f(-8, 48, -49.9);
	glVertex3f(-8, 10, -49.9);
	glEnd();
	glBegin(GL_QUADS);//daun pintu
	glColor3f(0.686, 0.203, 0.015);
	glVertex3f(4, 11, -49.8);
	glVertex3f(4, 47, -49.8);
	glVertex3f(-7, 47, -49.8);
	glVertex3f(-7, 11, -49.8);
	glEnd();
	glBegin(GL_LINES);//gagang pintu
	glColor3f(0.545, 0.509, 0.494);
	glVertex3f(-5, 30, -49.8);
	glVertex3f(-5, 30, -47.8);
	glEnd();

	glBegin(GL_QUADS);// ventilasi
	glColor3f(0, 0, 0);
	glVertex3f(5, 49, -49.9);
	glVertex3f(5, 53, -49.9);
	glVertex3f(-8, 53, -49.9);
	glVertex3f(-8, 49, -49.9);
	glEnd();

	//jendela sebelah pintu
	glBegin(GL_QUADS);
	glColor3f(0.364, 0.117, 0.015);
	glVertex3f(-9, 12, -49.9);
	glVertex3f(-9, 54, -49.9);
	glVertex3f(-24, 54, -49.9);
	glVertex3f(-24, 12, -49.9);
	glEnd();
	glBegin(GL_QUADS);// ventilasi
	glColor3f(0, 0, 0);
	glVertex3f(-10, 49, -49.8);
	glVertex3f(-10, 53, -49.8);
	glVertex3f(-23, 53, -49.8);
	glVertex3f(-23, 49, -49.8);
	glEnd();
	glBegin(GL_QUADS);//frame
	glColor3f(0.678, 0.678, 0.678);
	glVertex3f(-10, 13, -49.8);
	glVertex3f(-10, 48, -49.8);
	glVertex3f(-23, 48, -49.8);
	glVertex3f(-23, 13, -49.8);
	glEnd();
	glBegin(GL_QUADS);//kaca kiri
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(-17, 42, -49.7);
	glVertex3f(-17, 47, -49.7);
	glVertex3f(-22, 47, -49.7);
	glVertex3f(-22, 42, -49.7);
	glEnd();
	glBegin(GL_QUADS);//kaca kiri
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(-17, 35, -49.7);
	glVertex3f(-17, 41, -49.7);
	glVertex3f(-22, 41, -49.7);
	glVertex3f(-22, 35, -49.7);
	glEnd();
	glBegin(GL_QUADS);//kaca kiri
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(-17, 28, -49.7);
	glVertex3f(-17, 34, -49.7);
	glVertex3f(-22, 34, -49.7);
	glVertex3f(-22, 28, -49.7);
	glEnd();
	glBegin(GL_QUADS);//kaca kiri
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(-17, 21, -49.7);
	glVertex3f(-17, 27, -49.7);
	glVertex3f(-22, 27, -49.7);
	glVertex3f(-22, 21, -49.7);
	glEnd();
	glBegin(GL_QUADS);//kaca kiri
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(-17, 14, -49.7);
	glVertex3f(-17, 20, -49.7);
	glVertex3f(-22, 20, -49.7);
	glVertex3f(-22, 14, -49.7);
	glEnd();
	glBegin(GL_QUADS);//kaca kanan
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(-11, 42, -49.7);
	glVertex3f(-11, 47, -49.7);
	glVertex3f(-16, 47, -49.7);
	glVertex3f(-16, 42, -49.7);
	glEnd();
	glBegin(GL_QUADS);//kaca kanan
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(-11, 35, -49.7);
	glVertex3f(-11, 41, -49.7);
	glVertex3f(-16, 41, -49.7);
	glVertex3f(-16, 35, -49.7);
	glEnd();
	glBegin(GL_QUADS);//kaca kanan
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(-11, 28, -49.7);
	glVertex3f(-11, 34, -49.7);
	glVertex3f(-16, 34, -49.7);
	glVertex3f(-16, 28, -49.7);
	glEnd();
	glBegin(GL_QUADS);//kaca kanan
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(-11, 21, -49.7);
	glVertex3f(-11, 27, -49.7);
	glVertex3f(-16, 27, -49.7);
	glVertex3f(-16, 21, -49.7);
	glEnd();
	glBegin(GL_QUADS);//kaca kanan
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(-11, 14, -49.7);
	glVertex3f(-11, 20, -49.7);
	glVertex3f(-16, 20, -49.7);
	glVertex3f(-16, 14, -49.7);
	glEnd();

	//jendela sebelah pintu 2
	glBegin(GL_QUADS);
	glColor3f(0.364, 0.117, 0.015);
	glVertex3f(-24, 12, -49.9);
	glVertex3f(-24, 54, -49.9);
	glVertex3f(-39, 54, -49.9);
	glVertex3f(-39, 12, -49.9);
	glEnd();
	glBegin(GL_QUADS);// ventilasi
	glColor3f(0, 0, 0);
	glVertex3f(-25, 49, -49.8);
	glVertex3f(-25, 53, -49.8);
	glVertex3f(-38, 53, -49.8);
	glVertex3f(-38, 49, -49.8);
	glEnd();
	glBegin(GL_QUADS);//frame
	glColor3f(0.678, 0.678, 0.678);
	glVertex3f(-25, 13, -49.8);
	glVertex3f(-25, 48, -49.8);
	glVertex3f(-38, 48, -49.8);
	glVertex3f(-38, 13, -49.8);
	glEnd();
	glBegin(GL_QUADS);//kaca kiri
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(-32, 42, -49.7);
	glVertex3f(-32, 47, -49.7);
	glVertex3f(-37, 47, -49.7);
	glVertex3f(-37, 42, -49.7);
	glEnd();
	glBegin(GL_QUADS);//kaca kiri
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(-32, 35, -49.7);
	glVertex3f(-32, 41, -49.7);
	glVertex3f(-37, 41, -49.7);
	glVertex3f(-37, 35, -49.7);
	glEnd();
	glBegin(GL_QUADS);//kaca kiri
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(-32, 28, -49.7);
	glVertex3f(-32, 34, -49.7);
	glVertex3f(-37, 34, -49.7);
	glVertex3f(-37, 28, -49.7);
	glEnd();
	glBegin(GL_QUADS);//kaca kiri
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(-32, 21, -49.7);
	glVertex3f(-32, 27, -49.7);
	glVertex3f(-37, 27, -49.7);
	glVertex3f(-37, 21, -49.7);
	glEnd();
	glBegin(GL_QUADS);//kaca kiri
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(-32, 14, -49.7);
	glVertex3f(-32, 20, -49.7);
	glVertex3f(-37, 20, -49.7);
	glVertex3f(-37, 14, -49.7);
	glEnd();
	glBegin(GL_QUADS);//kaca kanan
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(-26, 42, -49.7);
	glVertex3f(-26, 47, -49.7);
	glVertex3f(-31, 47, -49.7);
	glVertex3f(-31, 42, -49.7);
	glEnd();
	glBegin(GL_QUADS);//kaca kanan
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(-26, 35, -49.7);
	glVertex3f(-26, 41, -49.7);
	glVertex3f(-31, 41, -49.7);
	glVertex3f(-31, 35, -49.7);
	glEnd();
	glBegin(GL_QUADS);//kaca kanan
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(-26, 28, -49.7);
	glVertex3f(-26, 34, -49.7);
	glVertex3f(-31, 34, -49.7);
	glVertex3f(-31, 28, -49.7);
	glEnd();
	glBegin(GL_QUADS);//kaca kanan
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(-26, 21, -49.7);
	glVertex3f(-26, 27, -49.7);
	glVertex3f(-31, 27, -49.7);
	glVertex3f(-31, 21, -49.7);
	glEnd();
	glBegin(GL_QUADS);//kaca kanan
	glColor3f(0.180, 0.184, 0.176);
	glVertex3f(-26, 14, -49.7);
	glVertex3f(-26, 20, -49.7);
	glVertex3f(-31, 20, -49.7);
	glVertex3f(-31, 14, -49.7);
	glEnd();
	//tembok kamar
	glBegin(GL_QUADS);
	glColor3f(0.796, 0.772, 0.486);
	glVertex3f(6, 0, -50);
	glVertex3f(6, 65, -50);
	glVertex3f(6, 65, -100);
	glVertex3f(6, 0, -100);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.796, 0.772, 0.486);
	glVertex3f(70.2, 0, -100);
	glVertex3f(70.2, 65, -100);
	glVertex3f(21, 65, -100);
	glVertex3f(21, 0, -100);
	glEnd();


	//tembok wc
	glBegin(GL_QUADS);
	glColor3f(0.796, 0.772, 0.486);
	glVertex3f(70.2, 0, -150);
	glVertex3f(70.2, 65, -150);
	glVertex3f(-5, 65, -150);
	glVertex3f(-5, 0, -150);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.796, 0.772, 0.486);
	glVertex3f(21, 54, -100);
	glVertex3f(21, 65, -100);
	glVertex3f(6, 65, -100);
	glVertex3f(6, 54, -100);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.796, 0.772, 0.486);
	glVertex3f(21, 0, -115);
	glVertex3f(21, 65, -115);
	glVertex3f(21, 65, -150);
	glVertex3f(21, 0, -150);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.796, 0.772, 0.486);
	glVertex3f(21, 49, -100);
	glVertex3f(21, 65, -100);
	glVertex3f(21, 65, -115);
	glVertex3f(21, 49, -115);
	glEnd();
	//pintu kamar
	glBegin(GL_QUADS);
	glColor3f(0.364, 0.117, 0.015);
	glVertex3f(21, 0, -100);
	glVertex3f(21, 54, -100);
	glVertex3f(6, 54, -100);
	glVertex3f(6, 0, -100);
	glEnd();
	glBegin(GL_QUADS);//daun pintu
	glColor3f(0.219, 0.023, 0.023);
	glVertex3f(20, 10, -100.1);
	glVertex3f(20, 48, -100.1);
	glVertex3f(7, 48, -100.1);
	glVertex3f(7, 10, -100.1);
	glEnd();
	glBegin(GL_QUADS);//daun pintu
	glColor3f(0.686, 0.203, 0.015);
	glVertex3f(19, 11, -100.2);
	glVertex3f(19, 47, -100.2);
	glVertex3f(8, 47, -100.2);
	glVertex3f(8, 11, -100.2);
	glEnd();
	glBegin(GL_LINES);//gagang pintu
	glColor3f(0.545, 0.509, 0.494);
	glVertex3f(10, 30, -100.2);
	glVertex3f(10, 30, -100.4);
	glEnd();
	glBegin(GL_QUADS);// ventilasi
	glColor3f(0, 0, 0);
	glVertex3f(20, 49, -100.1);
	glVertex3f(20, 53, -100.1);
	glVertex3f(7, 53, -100.1);
	glVertex3f(7, 49, -100.1);
	glEnd();

	//pintu wc
	glBegin(GL_QUADS);
	glColor3f(0.364, 0.117, 0.015);
	glVertex3f(21, 0, -100);
	glVertex3f(21, 49, -100);
	glVertex3f(21, 49, -115);
	glVertex3f(21, 0, -115);
	glEnd();
	glBegin(GL_QUADS);//daun pintu
	glColor3f(0.219, 0.023, 0.023);
	glVertex3f(20.9, 9, -101);
	glVertex3f(20.9, 48, -101);
	glVertex3f(20.9, 48, -114);
	glVertex3f(20.9, 9, -114);
	glEnd();
	glBegin(GL_QUADS);//daun pintu
	glColor3f(0.686, 0.203, 0.015);
	glVertex3f(20.8, 10, -102);
	glVertex3f(20.8, 47, -102);
	glVertex3f(20.8, 47, -113);
	glVertex3f(20.8, 10, -113);
	glEnd();


	glBegin(GL_QUADS);//rak sepatu
	glColor3f(0.745, 0.262, 0.035);
	glVertex3f(20, 15, -136);
	glVertex3f(20, 15, -146);
	glVertex3f(-5, 15, -146);
	glVertex3f(-5, 15, -136);
	glEnd();
	glBegin(GL_QUADS);//rak sepatu
	glColor3f(0.745, 0.262, 0.035);
	glVertex3f(20, 21, -136);
	glVertex3f(20, 21, -146);
	glVertex3f(-5, 21, -146);
	glVertex3f(-5, 21, -136);
	glEnd();
	glBegin(GL_QUADS);//rak sepatu
	glColor3f(0.745, 0.262, 0.035);
	glVertex3f(20, 27, -136);
	glVertex3f(20, 27, -146);
	glVertex3f(-5, 27, -146);
	glVertex3f(-5, 27, -136);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.129, 0.133, 0.125);
	glVertex3f(-4, 0, -137);
	glVertex3f(-4, 27, -137);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.129, 0.133, 0.125);
	glVertex3f(19, 0, -137);
	glVertex3f(19, 27, -137);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.129, 0.133, 0.125);
	glVertex3f(19, 0, -145);
	glVertex3f(19, 27, -145);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.129, 0.133, 0.125);
	glVertex3f(-4, 0, -145);
	glVertex3f(-4, 27, -145);
	glEnd();


	glBegin(GL_QUADS);//mesin cuci
	glColor3f(0.898, 0.898, 0.901);
	glVertex3f(20, 33, -200);
	glVertex3f(20, 33, -216);
	glVertex3f(-5, 33, -216);
	glVertex3f(-5, 33, -200);
	glEnd();
	glBegin(GL_QUADS);//mesin cuci
	glColor3f(0.898, 0.898, 0.901);
	glVertex3f(20, 0, -200);
	glVertex3f(20, 0, -216);
	glVertex3f(20, 33, -216);
	glVertex3f(20, 33, -200);
	glEnd();
	glBegin(GL_QUADS);//mesin cuci
	glColor3f(0.898, 0.898, 0.901);
	glVertex3f(-5, 0, -200);
	glVertex3f(-5, 0, -216);
	glVertex3f(-5, 33, -216);
	glVertex3f(-5, 33, -200);
	glEnd();
	glBegin(GL_QUADS);//mesin cuci
	glColor3f(0.898, 0.898, 0.901);
	glVertex3f(20, 0, -200);
	glVertex3f(20, 33, -200);
	glVertex3f(-5, 33, -200);
	glVertex3f(-5, 0, -200);
	glEnd();
	glBegin(GL_QUADS);//mesin cuci
	glColor3f(0.211, 0.015, 0.643);
	glVertex3f(19, 33.1, -201);
	glVertex3f(19, 33.1, -213);
	glVertex3f(8, 33.1, -213);
	glVertex3f(8, 33.1, -201);
	glEnd();
	glBegin(GL_QUADS);//mesin cuci
	glColor3f(0, 0, 0);
	glVertex3f(20, 0, -216.1);
	glVertex3f(20, 35, -216.1);
	glVertex3f(-5, 35, -216.1);
	glVertex3f(-5, 0, -216.1);
	glEnd();
	glBegin(GL_QUADS);//mesin cuci
	glColor3f(0.211, 0.015, 0.643);
	glVertex3f(20, 35, -214);
	glVertex3f(20, 35, -216);
	glVertex3f(-5, 35, -216);
	glVertex3f(-5, 35, -214);
	glEnd();
	glBegin(GL_QUADS);//mesin cuci
	glColor3f(0.211, 0.015, 0.643);
	glVertex3f(20, 32, -214);
	glVertex3f(20, 35, -214);
	glVertex3f(-5, 35, -214);
	glVertex3f(-5, 32, -214);
	glEnd();

	//kasur
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(12, 30, -40);
	glVertex3f(66, 30, -40);
	glVertex3f(66, 30, -65);
	glVertex3f(12, 30, -65);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(12, 0, -40);
	glVertex3f(66, 0, -40);
	glVertex3f(66, 30, -40);
	glVertex3f(12, 30, -40);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(12, 0, -65);
	glVertex3f(66, 0, -65);
	glVertex3f(66, 30, -65);
	glVertex3f(12, 30, -65);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(66, 0, -40);
	glVertex3f(66, 0, -65);
	glVertex3f(66, 30, -65);
	glVertex3f(66, 30, -40);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.733, 0.278, 0.027);
	glVertex3f(12, 0, -40);
	glVertex3f(12, 0, -65);
	glVertex3f(12, 45, -65);
	glVertex3f(12, 45, -40);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.733, 0.278, 0.027);
	glVertex3f(9, 0, -40);
	glVertex3f(9, 0, -65);
	glVertex3f(9, 45, -65);
	glVertex3f(9, 45, -40);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.733, 0.278, 0.027);
	glVertex3f(9, 0, -40);
	glVertex3f(9, 45, -40);
	glVertex3f(12, 45, -40);
	glVertex3f(12, 0, -40);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.733, 0.278, 0.027);
	glVertex3f(9, 0, -65);
	glVertex3f(9, 45, -65);
	glVertex3f(12, 45, -65);
	glVertex3f(12, 0, -65);
	glEnd();

	//lemari
	glBegin(GL_QUADS);
	glColor3f(0.733, 0.278, 0.027);
	glVertex3f(30, 0, -85);
	glVertex3f(63, 0, -85);
	glVertex3f(63, 50, -85);
	glVertex3f(30, 50, -85);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.733, 0.278, 0.027);
	glVertex3f(30, 0, -98);
	glVertex3f(63, 0, -98);
	glVertex3f(63, 50, -98);
	glVertex3f(30, 50, -98);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.733, 0.278, 0.027);
	glVertex3f(30, 0, -98);
	glVertex3f(30, 0, -85);
	glVertex3f(30, 50, -85);
	glVertex3f(30, 50, -98);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.733, 0.278, 0.027);
	glVertex3f(63, 0, -98);
	glVertex3f(63, 0, -85);
	glVertex3f(63, 50, -85);
	glVertex3f(63, 50, -98);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.733, 0.278, 0.027);
	glVertex3f(30, 50, -98);
	glVertex3f(30, 50, -85);
	glVertex3f(63, 50, -85);
	glVertex3f(63, 50, -98);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.505, 0.168, 0.011);
	glVertex3f(46, 0, -84.9);
	glVertex3f(47, 0, -84.9);
	glVertex3f(47, 50, -84.9);
	glVertex3f(46, 50, -84.9);
	glEnd();

	//bak mandi
	glBegin(GL_QUADS);
	glColor3f(0.007, 0.545, 0.752);
	glVertex3f(55, 0, -130);
	glVertex3f(55, 0, -150);
	glVertex3f(55, 30, -150);
	glVertex3f(55, 30, -130);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.007, 0.545, 0.752);
	glVertex3f(55, 0, -130);
	glVertex3f(70, 0, -130);
	glVertex3f(70, 30, -130);
	glVertex3f(55, 30, -130);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.007, 0.545, 0.752);
	glVertex3f(55, 8.1, -130);
	glVertex3f(70, 8.1, -130);
	glVertex3f(70, 8.1, -150);
	glVertex3f(55, 8.1, -150);
	glEnd();
	//listrik
	glBegin(GL_QUADS);
	glColor3f(0.501, 0.501, 0.501);
	glVertex3f(15, 40, -34.9);
	glVertex3f(15, 50, -34.9);
	glVertex3f(10, 50, -34.9);
	glVertex3f(10, 40, -34.9);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.501, 0.501, 0.501);
	glVertex3f(15, 40, -33);
	glVertex3f(15, 50, -33);
	glVertex3f(10, 50, -33);
	glVertex3f(10, 40, -33);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.501, 0.501, 0.501);
	glVertex3f(10, 40, -34.9);
	glVertex3f(10, 50, -34.9);
	glVertex3f(10, 50, -33);
	glVertex3f(10, 40, -33);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.501, 0.501, 0.501);
	glVertex3f(15, 40, -34.9);
	glVertex3f(15, 50, -34.9);
	glVertex3f(15, 50, -33);
	glVertex3f(15, 40, -33);
	glEnd();

	glPopMatrix();

	ground();

	cout << "X_GESER = " << x_geser << "    Y_GESER = " << y_geser << "    Z_GESER = " << z_geser << endl;
	glFlush();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	camera();
	draw();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(50, 16.0 / 9.0, 2, 10000);
	glMatrixMode(GL_MODELVIEW);

}

void timer(int)
{
	glutPostRedisplay();
	glutWarpPointer(width / 2, height / 2);
	glutTimerFunc(1000 / FPS, timer, 0);
}

void passive_motion(int x, int y)
{
	int dev_x, dev_y;
	dev_x = (width / 2) - x;
	dev_y = (height / 2) - y;

	yaw += (float)dev_x / 20.0;
	pitch += (float)dev_y / 20.0;
}

void camera()
{

	if (motion.Forward)
	{
		camX += cos((yaw + 90) * TO_RADIANS) * 2;
		camZ -= sin((yaw + 90) * TO_RADIANS) * 2;
	}
	if (motion.Backward)
	{
		camX += cos((yaw + 90 + 180) * TO_RADIANS) * 2;
		camZ -= sin((yaw + 90 + 180) * TO_RADIANS) * 2;
	}
	if (motion.Left)
	{
		camX += cos((yaw + 90 + 90) * TO_RADIANS) * 2;
		camZ -= sin((yaw + 90 + 90) * TO_RADIANS) * 2;
	}
	if (motion.Right)
	{
		camX += cos((yaw + 90 - 90) * TO_RADIANS) * 2;
		camZ -= sin((yaw + 90 - 90) * TO_RADIANS) * 2;
	}
	if (motion.Naik)
	{
		terbang -= 2.0;
	}
	if (motion.Turun)
	{
		terbang += 2.0;
	}

	if (pitch >= 70)
		pitch = 70;
	if (pitch <= -90)
		pitch = -90;


	glRotatef(-pitch, 1.0, 0.0, 0.0);
	glRotatef(-yaw, 0.0, 1.0, 0.0);

	glTranslatef(-camX, -terbang, -350 - camZ);
	if (terbang < 25)
		terbang = 24;
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'W':
	case 'w':
		motion.Forward = true;
		break;
	case 'A':
	case 'a':
		motion.Left = true;
		break;
	case 'S':
	case 's':
		motion.Backward = true;
		break;
	case 'D':
	case 'd':
		motion.Right = true;
		break;
	case 'E':
	case 'e':
		motion.Naik = true;
		break;
	case 'Q':
	case 'q':
		motion.Turun = true;
		break;
	case '6':
		x_geser += 0.5;
		break;
	case '4':
		x_geser -= 0.5;
		break;
	case '8':
		y_geser += 0.5;
		break;
	case '2':
		y_geser -= 0.5;
		break;
	case '9':
		z_geser -= 0.5;
		break;
	case '1':
		z_geser += 0.5;
		break;
	case '`':
		exit(1);
	}
}

void keyboard_up(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'W':
	case 'w':
		motion.Forward = false;
		break;
	case 'A':
	case 'a':
		motion.Left = false;
		break;
	case 'S':
	case 's':
		motion.Backward = false;
		break;
	case 'D':
	case 'd':
		motion.Right = false;
		break;
	case 'E':
	case 'e':
		motion.Naik = false;
		break;
	case 'Q':
	case 'q':
		motion.Turun = false;
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("London Metropolitan University");

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutPassiveMotionFunc(passive_motion);
	glutTimerFunc(0, timer, 0);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard_up);

	glutMainLoop();
	return 0;
}
