#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <cmath>
#include <string>
#include <cstdio>

#define PI 3.14159265358979323846

// ========================================
// PAGE CONTROL
// ========================================
int currentPage = 0;

// ========================================
// COVER PAGE VARIABLES
// ========================================
float cover_cloud1_x = -400.0f;
float cover_cloud2_x = 100.0f;
float cover_cloud3_x = 350.0f;
float cover_bird1_x = -300.0f, cover_bird1_y = 200.0f;
float cover_bird2_x = 100.0f, cover_bird2_y = 220.0f;
float cover_bird3_x = 300.0f, cover_bird3_y = 180.0f;
float cover_wing_pos = 0.0f;
int cover_wing_dir = 1;
float cover_smoke_y = 0.0f;
float cover_sun_glow = 50.0f;
int cover_glow_dir = 1;
float cover_tree_sway = 0.0f;
int cover_sway_dir = 1;
float cover_water_ripple = 0.0f;
float cover_leaf_fall_y = 0.0f;

// ========================================
// SHAHARIYER PAGE VARIABLES
// ========================================
float cloudMove = 0;
float birdMove1 = -500;
float birdMove2 = -200;
float birdMove3 = 100;
float bigBoatMove1 = 0;
float bigBoatMove2 = 0;
float wheelAngle = 0.0f;
float hUpX = -417;
float hUpY = -271;
float hUpTargetY = -200;
int humanDir = 0;
bool wheelRun = true;

// ========================================
// ABIR PAGE VARIABLES
// ========================================
float abir_cloud1_x = -350, abir_cloud2_x = 0, abir_cloud3_x = 300;
float abir_flag_wave = 0;
float abir_birdX[2] = {-500, -200};
float abir_birdY[2] = {220, 250};
float abir_birdSpeed = 0.8f;
float abir_wingAngle = 0.0f;
bool abir_wingUp = true;
float abir_bellAngle = 0.0f;
bool abir_bellRing = false;
bool abir_bellDir = true;

float abir_movingX = -180, abir_movingY = -480;
int abir_moving_state = 0;
float abir_movingX2 = 140, abir_movingY2 = -100;
float abir_movingX3 = 100, abir_movingY3 = -100;
int abir_moving_state2 = 0, abir_moving_state3 = 0;

float abir_footballX = -380, abir_footballY = -110;
float abir_footballRadius = 7;
int abir_footballDir = 1;

// ========================================
// LABIB PAGE VARIABLES
// ========================================
float labib_sun_glow = 50.0f;
int labib_glow_direction = 1;
float labib_cloud1_x = -350.0f;
float labib_cloud2_x = 0.0f;
float labib_cloud3_x = 300.0f;
float labib_bird1_x = -200, labib_bird1_y = 220;
float labib_bird2_x = 100, labib_bird2_y = 260;
float labib_bird3_x = 400, labib_bird3_y = 200;
float labib_wing_pos = 0;
int labib_wing_dir = 1;
float labib_smokeTime = 0.0f;
float labib_woman_x = 0.0f;
float labib_khunti_left_limit = 25.0f;
float labib_khunti_right_limit = 238.0f;

// ========================================
// SADEK PAGE VARIABLES
// ========================================
GLfloat sadek_positionc1 = 0.0f;
GLfloat sadek_speedc1 = 1.0f;
GLfloat sadek_positionc2 = 0.0f;
GLfloat sadek_speedc2 = 1.0f;
GLfloat sadek_positionc3 = 0.0f;
GLfloat sadek_speedc3 = 1.0f;
GLfloat sadek_positionc4 = 0.0f;
GLfloat sadek_speedc4 = 2.0f;
GLfloat sadek_positionc5 = 0.0f;
GLfloat sadek_speedc5 = 3.0f;
GLfloat sadek_j22 = 0.0f;
GLfloat sadek_j33 = 0.0f;
bool isSoundMuted = false;

// ========================================
// NOOR PAGE VARIABLES
// ========================================
bool noor_isRaining = false;
bool noor_isNight = false;
bool noor_lightOn = false;
GLfloat noor_manMove = 0.0f;
GLfloat noor_cloudPos1 = -100.0f;
GLfloat noor_cloudPos2 = 200.0f;
GLfloat noor_cloudSpeed = 0.5f;
GLfloat noor_wavePos = 0.0f;
GLfloat noor_speed = 0.05f;
GLfloat noor_boatPos = 0.0f;
GLfloat noor_boatSpeed = 2.0f;
GLfloat noor_birdPos = -350.0f;
GLfloat noor_birdSpeed = 1.2f;

// ========================================
// COVER PAGE FUNCTIONS
// ========================================
void cover_init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -300, 300);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glShadeModel(GL_SMOOTH);
}

void cover_drawCircle(float x, float y, float r) {
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.14159 / 180;
        glVertex2f(x + cos(angle) * r, y + sin(angle) * r);
    }
    glEnd();
}

void cover_drawText(float x, float y, const char* text, void* font) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void cover_drawVillageBackground() {
    glBegin(GL_QUADS);
    glColor3ub(170, 190, 210);
    glVertex2f(-500, 300);
    glVertex2f(500, 300);
    glColor3ub(235, 245, 255);
    glVertex2f(500, 50);
    glVertex2f(-500, 50);
    glEnd();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4ub(255, 220, 100, (int)(cover_sun_glow * 0.3));
    cover_drawCircle(-380, 240, 65);

    glColor4ub(255, 220, 100, (int)(cover_sun_glow * 0.5));
    cover_drawCircle(-380, 240, 50);

    glColor4ub(255, 220, 100, (int)(cover_sun_glow * 0.8));
    cover_drawCircle(-380, 240, 35);

    glDisable(GL_BLEND);

    glColor3ub(255, 200, 50);
    cover_drawCircle(-380, 240, 25);

    glLineWidth(2.0f);
    glColor3ub(255, 220, 100);
    for(int i = 0; i < 12; i++) {
        float angle = i * 30.0f * 3.14159f / 180.0f;
        glBegin(GL_LINES);
        glVertex2f(-380, 240);
        glVertex2f(-380 + cos(angle) * 45, 240 + sin(angle) * 45);
        glEnd();
    }

    glColor3ub(255, 255, 255);
    cover_drawCircle(cover_cloud1_x, 250, 20);
    cover_drawCircle(cover_cloud1_x + 20, 255, 25);
    cover_drawCircle(cover_cloud1_x + 40, 250, 18);

    cover_drawCircle(cover_cloud2_x, 220, 30);
    cover_drawCircle(cover_cloud2_x + 35, 230, 40);
    cover_drawCircle(cover_cloud2_x + 70, 225, 35);

    cover_drawCircle(cover_cloud3_x, 260, 35);
    cover_drawCircle(cover_cloud3_x + 40, 268, 42);
    cover_drawCircle(cover_cloud3_x + 80, 262, 38);

    glBegin(GL_POLYGON);
    glColor3ub(75, 95, 82);
    glVertex2f(-500, 50);
    glVertex2f(-400, 80);
    glVertex2f(-300, 70);
    glVertex2f(-200, 90);
    glVertex2f(-100, 75);
    glVertex2f(0, 95);
    glVertex2f(100, 80);
    glVertex2f(200, 100);
    glVertex2f(300, 85);
    glVertex2f(400, 95);
    glVertex2f(500, 75);
    glVertex2f(500, 50);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(120, 180, 80);
    glVertex2f(-500, 50);
    glVertex2f(500, 50);
    glColor3ub(80, 140, 60);
    glVertex2f(500, -100);
    glVertex2f(-500, -100);
    glEnd();

    glColor3ub(140, 120, 90);
    glBegin(GL_POLYGON);
    glVertex2f(-150, 50);
    glVertex2f(150, 50);
    glVertex2f(100, -100);
    glVertex2f(-100, -100);
    glEnd();

    glColor3ub(160, 120, 80);
    glBegin(GL_QUADS);
    glVertex2f(-430, 15);
    glVertex2f(-370, 15);
    glVertex2f(-370, 55);
    glVertex2f(-430, 55);
    glEnd();

    glColor3ub(180, 80, 60);
    glBegin(GL_TRIANGLES);
    glVertex2f(-440, 55);
    glVertex2f(-360, 55);
    glVertex2f(-400, 85);
    glEnd();

    glColor3ub(150, 110, 70);
    glBegin(GL_QUADS);
    glVertex2f(320, 10);
    glVertex2f(380, 10);
    glVertex2f(380, 50);
    glVertex2f(320, 50);
    glEnd();

    glColor3ub(170, 70, 50);
    glBegin(GL_TRIANGLES);
    glVertex2f(310, 50);
    glVertex2f(390, 50);
    glVertex2f(350, 80);
    glEnd();

    glColor3ub(145, 105, 65);
    glBegin(GL_QUADS);
    glVertex2f(-200, 20);
    glVertex2f(-150, 20);
    glVertex2f(-150, 55);
    glVertex2f(-200, 55);
    glEnd();

    glColor3ub(165, 75, 55);
    glBegin(GL_TRIANGLES);
    glVertex2f(-210, 55);
    glVertex2f(-140, 55);
    glVertex2f(-175, 82);
    glEnd();

    for(int t = 0; t < 3; t++) {
        float treeX = -250 + (t * 225);
        float treeScale = (t == 1) ? 1.0f : 0.8f;
        float sway = (t % 2 == 0) ? cover_tree_sway : -cover_tree_sway;

        glPushMatrix();
        glTranslatef(treeX, -100, 0);
        glScalef(treeScale, treeScale, 1.0f);
        glRotatef(sway, 0, 0, 1);

        glColor3ub(101, 67, 33);
        glBegin(GL_QUADS);
        glVertex2f(-5, 0);
        glVertex2f(5, 0);
        glVertex2f(3, 80);
        glVertex2f(-3, 80);
        glEnd();

        glLineWidth(1.5f);
        glColor3ub(80, 55, 25);
        for(int r = 10; r < 75; r += 8) {
            glBegin(GL_LINES);
            glVertex2f(-5, r);
            glVertex2f(5, r);
            glEnd();
        }

        glColor3ub(50, 120, 50);
        cover_drawCircle(0, 85, 22);
        cover_drawCircle(-15, 78, 16);
        cover_drawCircle(15, 78, 16);
        cover_drawCircle(-12, 92, 14);
        cover_drawCircle(12, 92, 14);

        glPopMatrix();
    }

    glColor3ub(50, 50, 50);
    glLineWidth(2.5f);

    glBegin(GL_LINES);
    glVertex2f(cover_bird1_x, cover_bird1_y);
    glVertex2f(cover_bird1_x - 10, cover_bird1_y + (6 * cover_wing_pos));
    glVertex2f(cover_bird1_x, cover_bird1_y);
    glVertex2f(cover_bird1_x + 10, cover_bird1_y + (6 * cover_wing_pos));
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(cover_bird2_x, cover_bird2_y);
    glVertex2f(cover_bird2_x - 12, cover_bird2_y + (7 * cover_wing_pos));
    glVertex2f(cover_bird2_x, cover_bird2_y);
    glVertex2f(cover_bird2_x + 12, cover_bird2_y + (7 * cover_wing_pos));
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(cover_bird3_x, cover_bird3_y);
    glVertex2f(cover_bird3_x - 8, cover_bird3_y + (5 * cover_wing_pos));
    glVertex2f(cover_bird3_x, cover_bird3_y);
    glVertex2f(cover_bird3_x + 8, cover_bird3_y + (5 * cover_wing_pos));
    glEnd();

    glColor3ub(140, 100, 70);
    glBegin(GL_QUADS);
    glVertex2f(-70, -100);
    glVertex2f(70, -100);
    glVertex2f(70, -20);
    glVertex2f(-70, -20);
    glEnd();

    glColor3ub(80, 50, 30);
    glBegin(GL_QUADS);
    glVertex2f(-25, -100);
    glVertex2f(25, -100);
    glVertex2f(25, -35);
    glVertex2f(-25, -35);
    glEnd();

    glColor3ub(100, 150, 200);
    glBegin(GL_QUADS);
    glVertex2f(-55, -50);
    glVertex2f(-35, -50);
    glVertex2f(-35, -30);
    glVertex2f(-55, -30);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(35, -50);
    glVertex2f(55, -50);
    glVertex2f(55, -30);
    glVertex2f(35, -30);
    glEnd();

    glColor3ub(160, 60, 40);
    glBegin(GL_TRIANGLES);
    glVertex2f(-80, -20);
    glVertex2f(80, -20);
    glVertex2f(0, 30);
    glEnd();

    glColor3ub(120, 80, 60);
    glBegin(GL_QUADS);
    glVertex2f(30, 30);
    glVertex2f(50, 30);
    glVertex2f(50, 55);
    glVertex2f(30, 55);
    glEnd();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for(int s = 0; s < 4; s++) {
        float offset = s * 20.0f;
        float currentY = 60 + cover_smoke_y - offset;
        if(currentY > 60) {
            float xWave = sin((cover_smoke_y + offset) * 0.05f) * 10.0f;
            float alpha = 150 - (cover_smoke_y - offset);
            if(alpha > 0 && alpha < 200) {
                glColor4ub(200, 200, 200, (int)alpha);
                cover_drawCircle(40 + xWave, currentY, 8 + s * 2);
            }
        }
    }
    glDisable(GL_BLEND);
}

void cover_drawDecorativeBorder() {
    glColor3ub(101, 67, 33);
    glLineWidth(12.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-490, 290);
    glVertex2f(490, 290);
    glVertex2f(490, -290);
    glVertex2f(-490, -290);
    glEnd();

    glColor3ub(139, 90, 43);
    glLineWidth(6.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-480, 280);
    glVertex2f(480, 280);
    glVertex2f(480, -280);
    glVertex2f(-480, -280);
    glEnd();

    glColor3ub(160, 120, 80);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-470, 270);
    glVertex2f(470, 270);
    glVertex2f(470, -270);
    glVertex2f(-470, -270);
    glEnd();
}

void cover_drawCoverContent() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_QUADS);
    glColor4ub(255, 255, 255, 130);
    glVertex2f(-460, 260);
    glVertex2f(460, 260);
    glColor4ub(255, 255, 255, 150);
    glVertex2f(460, -260);
    glVertex2f(-460, -260);
    glEnd();

    glColor4ub(245, 250, 255, 80);

    glColor3ub(0, 51, 102);
    cover_drawText(-220, 215, "American International University-Bangladesh", GLUT_BITMAP_TIMES_ROMAN_24);

    glColor3ub(0, 102, 51);
    cover_drawText(-125, 190, "Faculty of Science & Technology", GLUT_BITMAP_HELVETICA_18);

    glLineWidth(1.0f);
    glColor3ub(180, 180, 180);
    glBegin(GL_LINES);
    glVertex2f(-350, 170);
    glVertex2f(350, 170);
    glEnd();

    glColor3ub(139, 0, 0);
    cover_drawText(-90, 140, "Computer Graphics", GLUT_BITMAP_TIMES_ROMAN_24);

    glColor3ub(60, 60, 60);
    cover_drawText(-50, 115, "Section: H", GLUT_BITMAP_HELVETICA_18);

    glLineWidth(1.0f);
    glColor3ub(180, 180, 180);
    glBegin(GL_LINES);
    glVertex2f(-300, 95);
    glVertex2f(300, 95);
    glEnd();

    glColor3ub(25, 25, 112);
    cover_drawText(-70, 70, "PROJECT TITLE", GLUT_BITMAP_HELVETICA_18);

    glColor3ub(0, 0, 128);
    cover_drawText(-190, 45, "Village Scene, Computer Graphics Project", GLUT_BITMAP_TIMES_ROMAN_24);
    cover_drawText(-120, 20, "Using C++ With OpenGL", GLUT_BITMAP_TIMES_ROMAN_24);

    glLineWidth(1.0f);
    glColor3ub(180, 180, 180);
    glBegin(GL_LINES);
    glVertex2f(-300, -5);
    glVertex2f(300, -5);
    glEnd();

    glColor3ub(0, 100, 0);
    cover_drawText(-60, -25, "Submitted To", GLUT_BITMAP_HELVETICA_18);

    glColor3ub(139, 0, 0);
    cover_drawText(-120, -50, "MAHFUJUR RAHMAN", GLUT_BITMAP_TIMES_ROMAN_24);

    glLineWidth(1.0f);
    glColor3ub(180, 180, 180);
    glBegin(GL_LINES);
    glVertex2f(-300, -75);
    glVertex2f(300, -75);
    glEnd();

    glColor3ub(0, 0, 139);
    cover_drawText(-125, -95, "Submitted By (Group Members)", GLUT_BITMAP_HELVETICA_18);

    glColor3ub(60, 60, 60);
    cover_drawText(-340, -130, "1.", GLUT_BITMAP_HELVETICA_18);
    glColor3ub(0, 51, 102);
    cover_drawText(-320, -130, "HEDAYET ULLAH PATWARY", GLUT_BITMAP_HELVETICA_18);
    glColor3ub(120, 120, 120);
    cover_drawText(-320, -147, "ID: 22-47904-2", GLUT_BITMAP_HELVETICA_12);

    glColor3ub(60, 60, 60);
    cover_drawText(-340, -175, "2.", GLUT_BITMAP_HELVETICA_18);
    glColor3ub(0, 51, 102);
    cover_drawText(-320, -175, "SHEIKH NOOR UDDIN BASHAR", GLUT_BITMAP_HELVETICA_18);
    glColor3ub(120, 120, 120);
    cover_drawText(-320, -192, "ID: 22-47639-3", GLUT_BITMAP_HELVETICA_12);

    glColor3ub(60, 60, 60);
    cover_drawText(-340, -220, "3.", GLUT_BITMAP_HELVETICA_18);
    glColor3ub(0, 51, 102);
    cover_drawText(-320, -220, "MD SADEK HOSEN", GLUT_BITMAP_HELVETICA_18);
    glColor3ub(120, 120, 120);
    cover_drawText(-320, -237, "ID: 23-50435-1", GLUT_BITMAP_HELVETICA_12);

    glColor3ub(60, 60, 60);
    cover_drawText(160, -130, "4.", GLUT_BITMAP_HELVETICA_18);
    glColor3ub(0, 51, 102);
    cover_drawText(180, -130, "MD. ABIR AHMED", GLUT_BITMAP_HELVETICA_18);
    glColor3ub(120, 120, 120);
    cover_drawText(180, -147, "ID: 23-55385-3", GLUT_BITMAP_HELVETICA_12);

    glColor3ub(60, 60, 60);
    cover_drawText(160, -175, "5.", GLUT_BITMAP_HELVETICA_18);
    glColor3ub(0, 51, 102);
    cover_drawText(180, -175, "MD. SHAHRIAR JAMAN", GLUT_BITMAP_HELVETICA_18);
    glColor3ub(120, 120, 120);
    cover_drawText(180, -192, "ID: 23-50382-1", GLUT_BITMAP_HELVETICA_12);
}

void cover_display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    cover_drawVillageBackground();
    cover_drawDecorativeBorder();
    cover_drawCoverContent();

    glFlush();
    glutSwapBuffers();
}

// ========================================
// SHAHARIYER PAGE FUNCTIONS
// ========================================
void shah_init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -300, 300);
}

void drawFilledCircle(float cx, float cy, float r, int segments = 120) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; i++) {
        float ang = 2.0f * PI * i / segments;
        glVertex2f(cx + r * cosf(ang), cy + r * sinf(ang));
    }
    glEnd();
}

void drawCloud(float x, float y, float s) {
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(x,y,18 * s);
    drawFilledCircle(x + 20 * s,  y + 8 * s, 22 * s);
    drawFilledCircle(x + 45 * s,  y, 18 * s);
    drawFilledCircle(x + 25 * s,  y - 10*s,  20 * s);
}

void drawHill(float x, float y, float w, float h) {
    glBegin(GL_TRIANGLES);
        glVertex2f(x,        y);
        glVertex2f(x + w/2,  y + h);
        glVertex2f(x + w,    y);
    glEnd();
}

void drawBird(float x, float y, float s) {
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(x,y);
        glVertex2f(x + 10*s, y + 6*s);
        glVertex2f(x + 10*s,y + 6*s);
        glVertex2f(x + 20*s,y);
    glEnd();
}

void drawRect(float x1, float y1, float x2, float y2) {
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

void drawTriangle(float x1,float y1,float x2,float y2,float x3,float y3) {
    glBegin(GL_TRIANGLES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glVertex2f(x3,y3);
    glEnd();
}

void Tree(float x, float y, float s)
{
    glColor3f(0.50f, 0.28f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2f(x - 10*s, y);
        glVertex2f(x + 10*s, y);
        glVertex2f(x + 10*s, y + 130*s);
        glVertex2f(x - 10*s, y + 130*s);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(x - 10*s, y + 90*s);
        glVertex2f(x +  2*s, y + 90*s);
        glVertex2f(x - 22*s, y + 115*s);
        glVertex2f(x - 30*s, y + 115*s);

        glVertex2f(x -  2*s, y + 95*s);
        glVertex2f(x + 10*s, y + 95*s);
        glVertex2f(x + 30*s, y + 120*s);
        glVertex2f(x + 22*s, y + 120*s);
    glEnd();

    glColor3f(0.55f, 0.65f, 0.20f);
    drawFilledCircle(x,y + 180*s, 60*s);
    drawFilledCircle(x - 45*s,y + 150*s, 45*s);
    drawFilledCircle(x + 45*s,y + 150*s, 45*s);
    drawFilledCircle(x - 20*s,y + 205*s, 38*s);
    drawFilledCircle(x + 25*s,y + 205*s, 38*s);
}

void Nagordola(int cx, int cy, float angle)
{
    glColor3f(0.45f, 0.25f, 0.10f);
    glLineWidth(10);
    glBegin(GL_LINES);
        glVertex2i(cx - 70, cy - 120); glVertex2i(cx, cy );
        glVertex2i(cx + 70, cy - 120); glVertex2i(cx, cy );
        glVertex2i(cx - 100, cy - 120); glVertex2i(cx + 100, cy - 120);
    glEnd();

    glPushMatrix();
    glTranslatef((float)cx, (float)cy, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glColor3f(0,0,0);
    glLineWidth(4);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i += 10)
    {
        float a = i * PI / 180;
        glVertex2f(75 * cos(a), 75 * sin(a));
    }
    glEnd();

    glBegin(GL_LINES);
    for (int i = 0; i < 360; i += 45)
    {
        float a = i * PI / 180;
        glVertex2f(0, 0);
        glVertex2f(75 * cos(a), 75 * sin(a));
    }
    glEnd();

    glColor3f(0.3f, 0.3f, 0.3f);
    drawFilledCircle(0, 0, 6);

    int r = 75;
    for (int i = 0; i < 360; i += 45)
    {
        float a = i * PI / 180;
        float sx = r * cos(a);
        float sy = r * sin(a);

        glPushMatrix();
        glTranslatef(sx, sy, 0.0f);
        glRotatef(-angle, 0.0f, 0.0f, 1.0f);

        glColor3f(0,0,0);
        glBegin(GL_LINES);
            glVertex2i(0, 0);
            glVertex2i(0, -10);
        glEnd();

        glColor3f(0.9f, 0.2f, 0.2f);
        glBegin(GL_QUADS);
            glVertex2i(-8, -10);
            glVertex2i( 8, -10);
            glVertex2i( 8, -22);
            glVertex2i(-8, -22);
        glEnd();

        glPopMatrix();
    }

    glPopMatrix();
}

void House()
{
    glColor3f(0.85f, 0.70f, 0.35f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-500.0,-20.0);
    glVertex2f(-398.0,-84.1);
    glVertex2f(-500.0,-94.5);
    glEnd();

    glColor3f(0.75f, 0.60f, 0.30f);
    glBegin(GL_QUADS);
    glVertex2f(-408.0,-84.98);
    glVertex2f(-400.0,-160.0);
    glVertex2f(-500.0,-180.5);
    glVertex2f(-500.0,-94.5);
    glEnd();

    glColor3f(0.25f, 0.15f, 0.08f);
    glBegin(GL_QUADS);
    glVertex2f(-450.25,-128.5);
    glVertex2f(-424.0,-122.3);
    glVertex2f(-422.,-165.8);
    glVertex2f(-450.0,-170.33);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-500.0,-127.0);
    glVertex2f(-477.0,-126.3);
    glVertex2f(-475.7,-149.33);
    glVertex2f(-500.0,-151.4);
    glEnd();

    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
        glVertex2i(-390, -38);
        glVertex2i(-308, -25);
        glVertex2i(-266, -45);
        glVertex2i(-344, -63);
    glEnd();

    glColor3f(0.50f, 0.28f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2i(-319, -57);
        glVertex2i(-315, -56);
        glVertex2i(-313, -97);
        glVertex2i(-319, -96);
    glEnd();

    glColor3f(0.50f, 0.28f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2i(-272, -47);
        glVertex2i(-268, -45);
        glVertex2i(-269, -132);
        glVertex2i(-273, -132);
    glEnd();

    glColor3f(0.50f, 0.28f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2i(-386, -40);
        glVertex2i(-382, -42);
        glVertex2i(-382, -137);
        glVertex2i(-385, -137);
    glEnd();

    glColor3f(0.50f, 0.0f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2i(-374, -109);
        glVertex2i(-346, -119);
        glVertex2i(-346, -148);
        glVertex2i(-372, -140);
    glEnd();

    glColor3f(0.50f, 0.0f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2i(-345, -120);
        glVertex2i(-280, -105);
        glVertex2i(-278, -132);
        glVertex2i(-343, -149);
    glEnd();

    glColor3f(0.50f, 0.5f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2i(-374, -109);
        glVertex2i(-319, -97);
        glVertex2i(-280, -105);
        glVertex2i(-344, -120);
    glEnd();

    glColor3f(0.65f, 0.35f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2i(-354, -108);
        glVertex2i(-322, -101);
        glVertex2i(-302, -108);
        glVertex2i(-339, -116);
    glEnd();

    glPointSize(6);
    glBegin(GL_POINTS);
        glColor3f(1,0,0);
        glVertex2i(-340, -110);
        glVertex2i(-330, -108);
        glColor3f(1.0f, 0.6f, 0.0f);
        glVertex2i(-320, -110);
        glVertex2i(-315, -107);
        glColor3f(0.0f, 0.7f, 0.0f);
        glVertex2i(-325, -113);
    glEnd();

    glColor3f(0.50f, 0.28f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2i(-348, -60);
        glVertex2i(-344, -63);
        glVertex2i(-343, -152);
        glVertex2i(-347, -152);
    glEnd();

    glColor3f(1, 0.5, 0.8);
    glBegin(GL_QUADS);
        glVertex2i(-220, -38);
        glVertex2i(-138, -25);
        glVertex2i(-96,  -45);
        glVertex2i(-174, -63);
    glEnd();

    glColor3f(0.50f, 0.28f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2i(-149, -57);
        glVertex2i(-145, -56);
        glVertex2i(-143, -97);
        glVertex2i(-149, -96);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2i(-102, -47);
        glVertex2i(-98,  -45);
        glVertex2i(-99,  -132);
        glVertex2i(-103, -132);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2i(-216, -40);
        glVertex2i(-212, -42);
        glVertex2i(-212, -137);
        glVertex2i(-215, -137);
    glEnd();

    glColor3f(0.50f, 0.0f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2i(-204, -109);
        glVertex2i(-176, -119);
        glVertex2i(-176, -148);
        glVertex2i(-202, -140);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2i(-175, -120);
        glVertex2i(-110, -105);
        glVertex2i(-108, -132);
        glVertex2i(-173, -149);
    glEnd();

    glColor3f(0.50f, 0.5f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2i(-204, -109);
        glVertex2i(-149, -97);
        glVertex2i(-110, -105);
        glVertex2i(-174, -120);
    glEnd();

    glColor3f(0.65f, 0.35f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2i(-184, -108);
        glVertex2i(-152, -101);
        glVertex2i(-132, -108);
        glVertex2i(-169, -116);
    glEnd();

    glPointSize(6);
    glBegin(GL_POINTS);
        glColor3f(1,0,0);
        glVertex2i(-170, -110);
        glVertex2i(-160, -108);
        glColor3f(1,0.6f,0);
        glVertex2i(-150, -110);
        glVertex2i(-145, -107);
        glColor3f(0,0.7f,0);
        glVertex2i(-155, -113);
    glEnd();

    glColor3f(0.50f, 0.28f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2i(-178, -60);
        glVertex2i(-174, -63);
        glVertex2i(-173, -152);
        glVertex2i(-177, -152);
    glEnd();

    glColor3f(0.72f, 0.55f, 0.35f);
    glBegin(GL_TRIANGLES);
    glVertex2f(351.0,-149.0);
    glVertex2f(373.0,-205.0);
    glVertex2f(317.0,-205.0);
    glEnd();

    glColor3f(0.85f, 0.70f, 0.35f);
    glBegin(GL_QUADS);
    glVertex2f(340.0,-122.0);
    glVertex2f(351.0,-149.0);
    glVertex2f(317.0,-205.0);
    glVertex2f(288.0,-205.0);
    glEnd();

    glColor3f(0.85f, 0.70f, 0.35f);
    glBegin(GL_QUADS);
    glVertex2f(340.0,-122.0);
    glVertex2f(500.0,-121.5);
    glVertex2f(500.0,-205.0);
    glVertex2f(373.0,-205.0);
    glEnd();

    glColor3f(0.65f, 0.48f, 0.30f);
    glBegin(GL_QUADS);
    glVertex2f(373.0,-205.0);
    glVertex2f(500.0,-205.0);
    glVertex2f(500.0,-300.0);
    glVertex2f(372.5,-300.0);
    glEnd();

    glColor3f(0.72f, 0.55f, 0.35f);
    glBegin(GL_QUADS);
    glVertex2f(317.0,-205.0);
    glVertex2f(373.0,-205.0);
    glVertex2f(372.5,-300.0);
    glVertex2f(318.0,-272.0);
    glEnd();

    glColor3f(0.90f, 0.90f, 0.95f);
    glBegin(GL_QUADS);
    glVertex2f(333.5,-227.99);
    glVertex2f(355.7,-231.7);
    glVertex2f(355.73,-260.6);
    glVertex2f(333.31,-254.0);
    glEnd();

    glColor3f(0.30f, 0.15f, 0.08f);
    glBegin(GL_QUADS);
    glVertex2f(449.0,-229.0);
    glVertex2f(500.0,-229.0);
    glVertex2f(500.0,-300.0);
    glVertex2f(450.0,-300.0);
    glEnd();
}

void Boat(int x, int y)
{
    glColor3f(0.55f, 0.30f, 0.12f);
    glBegin(GL_POLYGON);
        glVertex2i(x - 60, y);
        glVertex2i(x + 60, y);
        glVertex2i(x + 40, y - 20);
        glVertex2i(x - 40, y - 20);
    glEnd();

    glColor3f(0,0,0);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
        glVertex2i(x - 60, y);
        glVertex2i(x + 60, y);
        glVertex2i(x + 40, y - 20);
        glVertex2i(x - 40, y - 20);
    glEnd();

    glColor3f(0.70f, 0.45f, 0.20f);
    glBegin(GL_QUADS);
        glVertex2i(x - 25, y - 5);
        glVertex2i(x + 25, y - 5);
        glVertex2i(x + 20, y - 15);
        glVertex2i(x - 20, y - 15);
    glEnd();
}

void BoatOnly(int x, int y)
{
    glColor3f(0.50f, 0.25f, 0.10f);
    glBegin(GL_POLYGON);
        glVertex2i(x - 55, y);
        glVertex2i(x + 55, y);
        glVertex2i(x + 40, y - 18);
        glVertex2i(x - 40, y - 18);
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
        glVertex2i(x - 55, y);
        glVertex2i(x + 55, y);
        glVertex2i(x + 40, y - 18);
        glVertex2i(x - 40, y - 18);
    glEnd();
}

void Human(int x, int y, float r, float g, float b)
{
    glColor3f(1.0f, 0.8f, 0.6f);
    drawFilledCircle(x, y + 24, 6);

    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2i(x - 10, y + 18);
    glVertex2i(x + 10, y + 18);
    glVertex2i(x + 10, y - 10);
    glVertex2i(x - 10, y - 10);
    glEnd();

    glColor3f(1.0f, 0.8f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2i(x - 18, y + 12);
    glVertex2i(x - 10, y + 12);
    glVertex2i(x - 10, y);
    glVertex2i(x - 18, y);

    glVertex2i(x + 10, y + 12);
    glVertex2i(x + 18, y + 12);
    glVertex2i(x + 18, y);
    glVertex2i(x + 10, y);
    glEnd();

    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2i(x - 8, y - 10);
        glVertex2i(x - 2, y - 10);
        glVertex2i(x - 2, y - 30);
        glVertex2i(x - 8, y - 30);

        glVertex2i(x + 2, y - 10);
        glVertex2i(x + 8, y - 10);
        glVertex2i(x + 8, y - 30);
        glVertex2i(x + 2, y - 30);
    glEnd();
}

void big_boat(){
    glColor3f(0.50f, 0.25f, 0.10f);
    glBegin(GL_QUADS);
        glVertex2f(-27, 39.16);
        glVertex2f(100, 40);
        glVertex2f(62.8, 17.7);
        glVertex2f(15.4, 17.1);
    glEnd();

    glColor3f(0.85f, 0.70f, 0.35f);
    glBegin(GL_TRIANGLES);
     glVertex2f(19.8,66.4);
    glVertex2f(32.3,39.5);
     glVertex2f(8.8,39.7);
    glEnd();

    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(19.8,66.4);
    glVertex2f(63.7, 66.4);
    glVertex2f(80, 39.5);
    glVertex2f(32.3,39.5);
    glEnd();
}

void big_boat_2(){
    glColor3f(0.50f, 0.25f, 0.10f);
    glBegin(GL_QUADS);
        glVertex2f(-87, 119.16);
        glVertex2f(40,  120);
        glVertex2f(2.8, 97.7);
        glVertex2f(-44.6, 97.1);
    glEnd();

    glColor3f(0.85f, 0.70f, 0.35f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-40.2, 146.4);
        glVertex2f(-27.7, 119.5);
        glVertex2f(-51.2, 119.7);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-40.2, 146.4);
        glVertex2f(3.7,   146.4);
        glVertex2f(20,    119.5);
        glVertex2f(-27.7, 119.5);
    glEnd();
}

void shah_display() {
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.5, 0.8, 1.0);
    glBegin(GL_QUADS);
        glVertex2i(-500, 150);
        glVertex2i(500, 150);
        glVertex2i(500, 300);
        glVertex2i(-500, 300);
    glEnd();

    glColor3f(1.0f, 0.85f, 0.10f);
    drawFilledCircle(380, 250, 35);

    glColor3f(1.0f, 0.65f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 120; i++) {
        float ang = 2.0f * PI * i / 120;
        glVertex2f(380 + 35 * cosf(ang), 250 + 35 * sinf(ang));
    }
    glEnd();

    drawCloud(-350 + cloudMove, 240, 1.2f);
    drawCloud(-120 + cloudMove, 265, 1.0f);
    drawCloud( 120 + cloudMove, 235, 1.1f);
    drawCloud( 250 + cloudMove, 270, 0.9f);

    glColor3f(0.75f, 0.60f, 0.45f);
    glBegin(GL_QUADS);
        glVertex2i(-500, -300);
        glVertex2i(500, -300);
        glVertex2i(500, -200);
        glVertex2i(-500, -200);
    glEnd();

    glColor3f(0.75f, 0.60f, 0.45f);
    glBegin(GL_POLYGON);
    glVertex2i(-500,59);
    glVertex2i(-213, 44);
    glVertex2i(-36, -23);
    glVertex2i(100, -100);
    glVertex2i(200, -200);
    glVertex2i(-500,-200);
    glEnd();

    glColor3f(0.5f, 0.85f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-500, 150);
    glVertex2f( 500, 150);
    glVertex2i(500, -200);
    glVertex2i(200, -200);
    glVertex2i(100, -100);
    glVertex2i(-36, -23);
    glVertex2i(-213, 44);
    glVertex2i(-500,59);
    glEnd();

    glColor3f(0.10f, 0.65f, 0.15f);
    drawHill(-520, 150, 180, 60);
    drawHill(-380, 150, 220, 80);
    drawHill(-200, 150, 200, 70);
    drawHill( -40, 150, 220, 85);
    drawHill( 160, 150, 190, 65);
    drawHill( 310, 150, 230, 90);
    drawHill( 500, 150, 200, 60);

    glColor3f(0.10f, 0.10f, 0.10f);
    drawBird(birdMove1, 265 + 6*sinf(birdMove1 * 0.02f), 1.0f);
    drawBird(birdMove1 + 40, 250 + 6*sinf(birdMove1 * 0.02f), 0.8f);
    drawBird(birdMove2, 275 + 5*sinf(birdMove2 * 0.025f), 1.1f);
    drawBird(birdMove2 + 35, 260 + 5*sinf(birdMove2 * 0.025f), 0.9f);
    drawBird(birdMove3, 255 + 4*sinf(birdMove3 * 0.03f), 0.9f);
    drawBird(birdMove3 + 30, 245 + 4*sinf(birdMove3 * 0.03f), 0.75f);

    Boat(90,-100 );
    Boat(110, -110);
    Boat(133, -124);
    Nagordola(-15, -90, wheelAngle);

    glPushMatrix();
    glTranslatef(bigBoatMove1, 0, 0);
    big_boat();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(bigBoatMove2, 0, 0);
    big_boat_2();
    glPopMatrix();

    Tree(-460, -60, 1.15f);
    Tree(-360, -41, 0.95f);
    Tree(431, -188, 1.50f);
    Human(-350, -100, 1.0f, 0.6f, 0.1f);
    Human(-170, -95, 0.10f, 0.60f, 0.60f);
    House();
    Human(-300, -120, 0.2f, 0.4f, 0.8f);
    Human(-270, -130, 1.0f, 0.2f, 0.2f);
    Human(-150, -130, 1.0f, 0.4f, 0.7f);
    Human(10, -230, 0.2f, 0.8f, 0.3f);
    Human(40, -210, 0.65f, 0.35f, 0.80f);
    Human(-30, -230, 1.0f, 0.6f, 0.1f);
    Human(-10, -260, 0.90f, 0.75f, 0.20f);
    Human(-321, -211, 0.55f, 0.80f, 0.95f);
    Human((int)hUpX, (int)hUpY, 0.10f, 0.60f, 0.60f);

    glFlush();
    glutSwapBuffers();
}

// Global drawText function for Abir page
void abir_drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

// ========================================
// ABIR PAGE FUNCTIONS
// ========================================

void abir_drawCircle(float x, float y, float r) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float a = 2 * PI * i / 100;
        glVertex2f(x + cos(a) * r, y + sin(a) * r);
    }
    glEnd();
}

void abir_drawSun() {
    GLfloat x17 = 120.0f;
    GLfloat y17 = 250.0f;
    GLfloat radius17 = 40.0f;
    int triangleAmount = 100;
    GLfloat twicePi = 2.0f * PI;

    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x17, y17);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(x17 + (radius17 * cos(i * twicePi / triangleAmount)),
                   y17 + (radius17 * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    glColor4f(1.0f, 1.0f, 0.0f, 0.3f);
    for (int i = 0; i < 360; i += 15) {
        float angle = i * PI / 180.0f;
        float x1 = x17 + cos(angle) * 40;
        float y1 = y17 + sin(angle) * 40;
        float x2 = x17 + cos(angle) * 120;
        float y2 = y17 + sin(angle) * 120;
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    }
}

void abir_drawTree(float baseX, float baseY) {
    float trunkTop = baseY + 140;
    glColor3f(0.4, 0.2, 0);
    glBegin(GL_QUADS);
    glVertex2f(baseX - 10, baseY);
    glVertex2f(baseX + 10, baseY);
    glVertex2f(baseX + 10, trunkTop);
    glVertex2f(baseX - 10, trunkTop);
    glEnd();

    glColor3f(0, 0.6, 0);
    abir_drawCircle(baseX, trunkTop + 50, 55);
    abir_drawCircle(baseX - 45, trunkTop + 35, 45);
    abir_drawCircle(baseX + 45, trunkTop + 35, 45);
    abir_drawCircle(baseX, trunkTop + 15, 35);
    abir_drawCircle(baseX - 35, trunkTop, 30);
    abir_drawCircle(baseX + 35, trunkTop, 30);
}

void abir_drawBird(float x, float y, float wing) {
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x - 15, y + wing);
    glVertex2f(x, y);
    glVertex2f(x + 15, y + wing);
    glEnd();
}

void abir_drawStudentSimpleHead(float x, float y) {
    glColor3f(1, 0.8, 0.4);
    abir_drawCircle(x, y + 60, 10);
    glBegin(GL_QUADS);
    glVertex2f(x - 3, y + 55);
    glVertex2f(x + 3, y + 55);
    glVertex2f(x + 3, y + 50);
    glVertex2f(x - 3, y + 50);
    glEnd();

    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    glVertex2f(x - 12, y + 45);
    glVertex2f(x + 12, y + 45);
    glVertex2f(x + 10, y + 15);
    glVertex2f(x - 10, y + 15);
    glEnd();

    glColor3f(1, 0.8, 0.4);
    glBegin(GL_POLYGON);
    glVertex2f(x - 10, y + 42);
    glVertex2f(x - 18, y + 38);
    glVertex2f(x - 22, y + 25);
    glVertex2f(x - 18, y + 15);
    glVertex2f(x - 12, y + 20);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(x + 10, y + 42);
    glVertex2f(x + 18, y + 38);
    glVertex2f(x + 22, y + 25);
    glVertex2f(x + 18, y + 15);
    glVertex2f(x + 12, y + 20);
    glEnd();

    glColor3f(0, 0, 0.7);
    glBegin(GL_POLYGON);
    glVertex2f(x - 10, y + 15);
    glVertex2f(x + 10, y + 15);
    glVertex2f(x + 14, y - 10);
    glVertex2f(x - 14, y - 10);
    glEnd();

    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex2f(x - 7, y - 10);
    glVertex2f(x - 2, y - 10);
    glVertex2f(x - 2, y - 40);
    glVertex2f(x - 7, y - 40);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(x + 2, y - 10);
    glVertex2f(x + 7, y - 10);
    glVertex2f(x + 7, y - 40);
    glVertex2f(x + 2, y - 40);
    glEnd();

    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_QUADS);
    glVertex2f(x - 7, y - 40);
    glVertex2f(x - 2, y - 40);
    glVertex2f(x - 2, y - 45);
    glVertex2f(x - 7, y - 45);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(x + 2, y - 40);
    glVertex2f(x + 7, y - 40);
    glVertex2f(x + 7, y - 45);
    glVertex2f(x + 2, y - 45);
    glEnd();
}

void abir_drawStudent(float x, float y) {
    abir_drawStudentSimpleHead(-420, -200);
    abir_drawStudentSimpleHead(abir_movingX, abir_movingY);

    glColor3f(1, 0.8, 0.4);
    abir_drawCircle(x, y + 60, 10);
    glColor3f(1, 1, 1);
    abir_drawCircle(x - 4, y + 62, 2);
    abir_drawCircle(x + 4, y + 62, 2);
    glColor3f(0, 0, 0);
    abir_drawCircle(x - 4, y + 62, 1);
    abir_drawCircle(x + 4, y + 62, 1);

    glColor3f(1, 0.8, 0.4);
    glBegin(GL_POLYGON);
    glVertex2f(x - 3, y + 52);
    glVertex2f(x + 3, y + 52);
    glVertex2f(x + 5, y + 48);
    glVertex2f(x + 6, y + 45);
    glVertex2f(x - 6, y + 45);
    glVertex2f(x - 5, y + 48);
    glEnd();

    glColor3f(1, 0.8, 0.4);
    glBegin(GL_QUADS);
    glVertex2f(x - 3, y + 55);
    glVertex2f(x + 3, y + 55);
    glVertex2f(x + 3, y + 50);
    glVertex2f(x - 3, y + 50);
    glEnd();

    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    glVertex2f(x - 12, y + 45);
    glVertex2f(x + 12, y + 45);
    glVertex2f(x + 10, y + 15);
    glVertex2f(x - 10, y + 15);
    glEnd();

    glColor3f(1, 0.8, 0.4);
    glBegin(GL_POLYGON);
    glVertex2f(x - 10, y + 42);
    glVertex2f(x - 18, y + 38);
    glVertex2f(x - 22, y + 25);
    glVertex2f(x - 18, y + 15);
    glVertex2f(x - 12, y + 20);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(x + 10, y + 42);
    glVertex2f(x + 18, y + 38);
    glVertex2f(x + 22, y + 25);
    glVertex2f(x + 18, y + 15);
    glVertex2f(x + 12, y + 20);
    glEnd();

    glColor3f(0, 0, 0.7);
    glBegin(GL_POLYGON);
    glVertex2f(x - 10, y + 15);
    glVertex2f(x + 10, y + 15);
    glVertex2f(x + 14, y - 10);
    glVertex2f(x - 14, y - 10);
    glEnd();

    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex2f(x - 7, y - 10);
    glVertex2f(x - 2, y - 10);
    glVertex2f(x - 2, y - 40);
    glVertex2f(x - 7, y - 40);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(x + 2, y - 10);
    glVertex2f(x + 7, y - 10);
    glVertex2f(x + 7, y - 40);
    glVertex2f(x + 2, y - 40);
    glEnd();

    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_QUADS);
    glVertex2f(x - 7, y - 40);
    glVertex2f(x - 2, y - 40);
    glVertex2f(x - 2, y - 45);
    glVertex2f(x - 7, y - 45);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(x + 2, y - 40);
    glVertex2f(x + 7, y - 40);
    glVertex2f(x + 7, y - 45);
    glVertex2f(x + 2, y - 45);
    glEnd();
}

void abir_clouds() {
    glColor3ub(240, 245, 255);
    abir_drawCircle(abir_cloud1_x, 250, 20);
    abir_drawCircle(abir_cloud1_x + 20, 255, 25);
    abir_drawCircle(abir_cloud1_x + 40, 250, 18);
    abir_drawCircle(abir_cloud2_x, 220, 30);
    abir_drawCircle(abir_cloud2_x + 35, 230, 40);
    abir_drawCircle(abir_cloud2_x + 70, 225, 35);
    abir_drawCircle(abir_cloud2_x + 35, 205, 25);
    abir_drawCircle(abir_cloud3_x, 260, 45);
    abir_drawCircle(abir_cloud3_x + 50, 275, 55);
    abir_drawCircle(abir_cloud3_x + 100, 265, 48);
    abir_drawCircle(abir_cloud3_x + 50, 245, 35);
}

void abir_drawSchool() {

    glColor3f(1.0f, 0.85f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(-300, -100);
    glVertex2f(400, -100);
    glVertex2f(400, 50);
    glVertex2f(-300, 50);
    glEnd();

    glColor3f(0.8f, 0.1f, 0.1f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-320, 50);
    glVertex2f(420, 50);
    glVertex2f(50, 130);
    glEnd();

    glColor3f(0.4f, 0.2, 0.1f);
    int doorX[4] = {-240, -80, 80, 240};
    for (int i = 0; i < 4; i++) {
        glBegin(GL_QUADS);
        glVertex2f(doorX[i], -100);
        glVertex2f(doorX[i] + 50, -100);
        glVertex2f(doorX[i] + 50, 0);
        glVertex2f(doorX[i], 0);
        glEnd();
    }

    glColor3f(0.6f, 0.8, 1.0f);
    int winX[3] = {-160, 0, 160};
    for (int i = 0; i < 3; i++) {
        glBegin(GL_QUADS);
        glVertex2f(winX[i], -60);
        glVertex2f(winX[i] + 60, -60);
        glVertex2f(winX[i] + 60, -30);
        glVertex2f(winX[i], -30);
        glEnd();
    }
}

void abir_drawSchoolNameBoard() {

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-80, 60);
    glVertex2f(180, 60);
    glVertex2f(180, 95);
    glVertex2f(-80, 95);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-80, 60); glVertex2f(180, 60);
    glVertex2f(180, 95); glVertex2f(-80, 95);
    glEnd();
    glColor3f(0.1f, 0.1f, 0.1f);
    abir_drawText(-60, 72, "Khantonagar Primary School ");
}

void abir_drawGoalPosts() {
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex2f(-450, -280);
    glVertex2f(-444, -280);
    glVertex2f(-444, -220);
    glVertex2f(-450, -220);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-390, -280);
    glVertex2f(-384, -280);
    glVertex2f(-384, -220);
    glVertex2f(-390, -220);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-450, -220);
    glVertex2f(-384, -220);
    glVertex2f(-384, -214);
    glVertex2f(-450, -214);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-450, -120);
    glVertex2f(-444, -120);
    glVertex2f(-444, -60);
    glVertex2f(-450, -60);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-390, -120);
    glVertex2f(-384, -120);
    glVertex2f(-384, -60);
    glVertex2f(-390, -60);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-450, -60);
    glVertex2f(-384, -60);
    glVertex2f(-384, -54);
    glVertex2f(-450, -54);
    glEnd();
}

void abir_drawFootball() {
    glColor3f(1, 1, 1);
    abir_drawCircle(abir_footballX, abir_footballY, abir_footballRadius);
}

void abir_drawBell() {
    glPushMatrix();
    glTranslatef(350, 0, 0);
    glRotatef(abir_bellAngle, 0, 0, 1);

    glColor3f(0.9f, 0.8f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(-10, 0);
    glVertex2f(10, 0);
    glVertex2f(16, -20);
    glVertex2f(-16, -20);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-5, 5);
    glVertex2f(5, 5);
    glVertex2f(5, 0);
    glVertex2f(-5, 0);
    glEnd();

    glColor3f(0.3f, 0.3, 0.3);
    abir_drawCircle(0, -18, 3);
    glPopMatrix();
}

void abir_drawFlag() {
    glColor3f(0.4, 0.4, 0.4);
    glBegin(GL_QUADS);
    glVertex2f(-180, -100);
    glVertex2f(-174, -100);
    glVertex2f(-174, 240);
    glVertex2f(-180, 240);
    glEnd();

    glColor3f(0, 0.6, 0);
    glBegin(GL_QUADS);
    glVertex2f(-174, 210);
    glVertex2f(-24 + sin(abir_flag_wave) * 15, 210);
    glVertex2f(-24 + sin(abir_flag_wave) * 15, 120);
    glVertex2f(-174, 120);
    glEnd();
    glColor3f(1, 0, 0);
    abir_drawCircle(-174 + 80, 165, 25);
}

void abir_Grass() {
    glColor3f(0.3f, 0.7, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(-500, -50);
    glVertex2f(500, -50);
    glVertex2f(500, -300);
    glVertex2f(-500, -300);
    glEnd();
}

void abir_display() {
    glClearColor(0.7, 0.9, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    abir_drawSun();
    abir_clouds();
    abir_drawBird(abir_birdX[0], abir_birdY[0], abir_wingAngle);
    abir_drawBird(abir_birdX[1], abir_birdY[1], abir_wingAngle + 2);
    abir_Grass();

    abir_drawTree(-440, -100);
    abir_drawTree(-380, -100);
    abir_drawTree(480, -100);
    abir_drawSchool();
    abir_drawSchoolNameBoard();
    abir_drawBell();
    abir_drawFlag();
    abir_drawGoalPosts();
    abir_drawFootball();
    abir_drawStudent(-420, -200);
    abir_drawStudent(-420, -80);
    abir_drawStudent(-350, -80);
    abir_drawStudent(-300, -80);
    abir_drawStudent(-250, -80);
    abir_drawStudent(abir_movingX, abir_movingY);
    abir_drawStudent(abir_movingX2, abir_movingY2);
    abir_drawStudent(abir_movingX3, abir_movingY3);



    glFlush();
    glutSwapBuffers();
}

// ========================================
// LABIB PAGE FUNCTIONS
// ========================================

void labib_drawSunCircle(float x, float y, float r) {
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.14159 / 180;
        glVertex2f(x + cos(angle) * r, y + sin(angle) * r);
    }
    glEnd();
}

void labib_sun() {
    // 1. Outer Glow (Pulsing)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4ub(255, 255, 200, (int)labib_sun_glow);
    labib_drawSunCircle(-400, 240, 50);

    // 2. Main Sun
    glColor3ub(255, 255, 230);
    labib_drawSunCircle(-400, 240, 25);

    glDisable(GL_BLEND);
}

// cloud shape helper function
void labib_drawCloudPart(float x, float y, float r) {
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.14159 / 180;
        glVertex2f(x + cos(angle) * r, y + sin(angle) * r);
    }
    glEnd();
}

void labib_clouds() {
    glColor4ub(240, 245, 255, 220);

    // Cloud 1 - Small Size
    labib_drawCloudPart(labib_cloud1_x, 250, 20);
    labib_drawCloudPart(labib_cloud1_x + 20, 255, 25);
    labib_drawCloudPart(labib_cloud1_x + 40, 250, 18);

    // Cloud 2 - Medium Size
    labib_drawCloudPart(labib_cloud2_x, 220, 30);
    labib_drawCloudPart(labib_cloud2_x + 35, 230, 40);
    labib_drawCloudPart(labib_cloud2_x + 70, 225, 35);
    labib_drawCloudPart(labib_cloud2_x + 35, 205, 25);

    // Cloud 3 - Large Size
    labib_drawCloudPart(labib_cloud3_x, 260, 45);
    labib_drawCloudPart(labib_cloud3_x + 50, 275, 55);
    labib_drawCloudPart(labib_cloud3_x + 100, 265, 48);
    labib_drawCloudPart(labib_cloud3_x + 50, 245, 35);
}

void labib_birds() {
    glLineWidth(2.0);
    glColor3ub(30, 30, 30);

    // Bird 1 (Moving Right)
    glBegin(GL_LINES);
    glVertex2f(labib_bird1_x, labib_bird1_y);
    glVertex2f(labib_bird1_x - 10, labib_bird1_y + (5 * labib_wing_pos));
    glVertex2f(labib_bird1_x, labib_bird1_y);
    glVertex2f(labib_bird1_x + 10, labib_bird1_y + (5 * labib_wing_pos));
    glEnd();

    // Bird 2 (Moving Left - Slightly Different Size)
    glBegin(GL_LINES);
    glVertex2f(labib_bird2_x, labib_bird2_y);
    glVertex2f(labib_bird2_x - 15, labib_bird2_y + (8 * labib_wing_pos));
    glVertex2f(labib_bird2_x, labib_bird2_y);
    glVertex2f(labib_bird2_x + 15, labib_bird2_y + (8 * labib_wing_pos));
    glEnd();

    // Bird 3 (Moving Right - Small Bird)
    glBegin(GL_LINES);
    glVertex2f(labib_bird3_x, labib_bird3_y);
    glVertex2f(labib_bird3_x - 8, labib_bird3_y + (4 * labib_wing_pos));
    glVertex2f(labib_bird3_x, labib_bird3_y);
    glVertex2f(labib_bird3_x + 8, labib_bird3_y + (4 * labib_wing_pos));
    glEnd();
}

// SKY Function
void labib_sky(){
    glBegin(GL_QUADS);

    glColor3ub(170, 190, 210);
    glVertex2f(-500, 300);
    glVertex2f(500, 300);

    glColor3ub(235, 245, 255);
    glVertex2f(500, 64);
    glVertex2f(-500, 65.81);

    glEnd();
    labib_sun();
    labib_clouds();
    labib_birds();
}

//BackTree
void labib_backtree() {
    // 1. MAIN BODY - ENHANCED WINTER COLOR PALETTE
    glBegin(GL_QUAD_STRIP);

    // Pair 1
    glColor3ub(25, 40, 48);
    glVertex2f(-500, 50);
    glColor3ub(75, 95, 82);
    glVertex2f(-500, 116);

    // Pair 2
    glColor3ub(28, 43, 50);
    glVertex2f(-459, 44);
    glColor3ub(80, 100, 88);
    glVertex2f(-485, 112);

    // Pair 3
    glColor3ub(30, 45, 52);
    glVertex2f(-390, 43);
    glColor3ub(82, 102, 90);
    glVertex2f(-471, 113);

    // Pair 4
    glColor3ub(33, 48, 54);
    glVertex2f(-301, 32);
    glColor3ub(88, 108, 94);
    glVertex2f(-446, 90);

    // Pair 5
    glColor3ub(35, 50, 56);
    glVertex2f(-232, 23);
    glColor3ub(90, 112, 98);
    glVertex2f(-186, 74);

    // Pair 6
    glColor3ub(38, 53, 58);
    glVertex2f(-92, 4);
    glColor3ub(93, 118, 103);
    glVertex2f(-125, 88);

    // Pair 7
    glColor3ub(38, 53, 58);
    glVertex2f(33, -6);
    glColor3ub(95, 120, 105);
    glVertex2f(-64, 94);

    // Pair 8
    glColor3ub(40, 56, 63);
    glVertex2f(150, -45);
    glColor3ub(98, 123, 108);
    glVertex2f(31, 101);

    // Pair 9
    glColor3ub(42, 58, 65);
    glVertex2f(300, -95);
    glColor3ub(105, 130, 115);
    glVertex2f(200, 100);

    // Pair 10
    glColor3ub(38, 53, 58);
    glVertex2f(416, -102);
    glColor3ub(102, 127, 112);
    glVertex2f(303, 159);

    // Pair 11: High Peak
    glColor3ub(35, 50, 56);
    glVertex2f(450, -115);
    glColor3ub(112, 137, 122);
    glVertex2f(364, 179);

    // Pair 12
    glColor3ub(30, 45, 52);
    glVertex2f(500, -126);
    glColor3ub(88, 108, 93);
    glVertex2f(487, 98);

    // Pair 13
    glColor3ub(28, 43, 50);
    glVertex2f(500, -130);
    glColor3ub(82, 102, 88);
    glVertex2f(500, 64);

    glEnd();

    // 2. ENHANCED MIST LAYER (Multiple layers for depth)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Upper mist layer
    glBegin(GL_QUADS);
    glColor4ub(240, 245, 255, 50);
    glVertex2f(-500, 200);
    glVertex2f(500, 200);
    glColor4ub(255, 255, 255, 0);
    glVertex2f(500, 100);
    glVertex2f(-500, 100);
    glEnd();

    // Middle mist layer
    glBegin(GL_QUADS);
    glColor4ub(255, 255, 255, 35);
    glVertex2f(-500, 150);
    glVertex2f(500, 150);
    glColor4ub(255, 255, 255, 0);
    glVertex2f(500, 60);
    glVertex2f(-500, 60);
    glEnd();
    glDisable(GL_BLEND);

    // WINTER HIGHLIGHT
    glLineWidth(1.5);
    glBegin(GL_LINE_STRIP);
    glColor3ub(145, 155, 150);
    glVertex2f(-500, 116);
    glVertex2f(-485, 112);
    glVertex2f(-471, 113);
    glVertex2f(-446, 90);
    glVertex2f(-186, 74);
    glVertex2f(-125, 88);
    glVertex2f(-64, 94);
    glVertex2f(31, 101);
    glVertex2f(200, 100);
    glVertex2f(303, 159);
    glVertex2f(364, 179);
    glVertex2f(487, 98);
    glVertex2f(500, 64);
    glEnd();

    glDisable(GL_BLEND);
}

//River
void labib_river() {
    glBegin(GL_POLYGON);

    // 1. Durer ongsho - Deep Cold Blue
    glColor3ub(45, 75, 115);
    glVertex2f(-500, 31);
    glVertex2f(-500, 50);
    glVertex2f(-459, 44);
    glVertex2f(-390, 43);
    glVertex2f(-301, 32);

    // 2. Majher ongsho - Pale Winter Blue
    glColor3ub(100, 130, 165);
    glVertex2f(-232, 23);
    glVertex2f(-92, 4);
    glVertex2f(33, -6);
    glVertex2f(416, -102);
    glVertex2f(500, -126);

    // 3. Nicher ongsho - Dark Cold Water
    glColor3ub(40, 65, 100);
    glVertex2f(500, -300);
    glVertex2f(427, -275);
    glVertex2f(273, -238);
    glVertex2f(51, -164);

    // 4. Parer ongsho - Frosty Blue
    glColor3ub(130, 155, 180);
    glVertex2f(-1.7, -112);
    glVertex2f(-29, -60);
    glVertex2f(-61, -40);
    glVertex2f(-128, -29);
    glVertex2f(-260, -2.2);

    glEnd();
}
//Ground
void labib_ground(){
    glBegin(GL_POLYGON);

    // 1. Durer ongsho - Pale Cold Brown
    glColor3ub(140, 130, 115);
    glVertex2f(-500, -300);
    glVertex2f(-500, 31);

    // 2. Nodir parer ongsho - Dull Mud Color
    glColor3ub(120, 110, 95);
    glVertex2f(-260, -2.2);
    glVertex2f(-128, -29);
    glVertex2f(-61, -40);
    glVertex2f(-29, -60);

    // 3. Samner ongsho - grey-brown
    glColor3ub(100, 95, 85);
    glVertex2f(-1.7, -112);
    glVertex2f(51, -164);
    glVertex2f(273, -238);
    glVertex2f(427, -275);
    glVertex2f(500, -300);
    glVertex2f(-500, -300);

    glEnd();
}

//Building
void labib_building() {

    // SIDE WALL (LEFT)
    glBegin(GL_POLYGON);
    glColor3ub(140, 140, 135);
    glVertex2f(-410, 17);
    glVertex2f(-320, 0);
    glVertex2f(-320, 90);
    glVertex2f(-408, 89);
    glEnd();

    // FRONT WALL (SHUTTER SIDE)
    glBegin(GL_POLYGON);
    glColor3ub(175, 175, 165);
    glVertex2f(-320, 0);
    glVertex2f(-209, 9);
    glVertex2f(-207, 89);
    glVertex2f(-320, 90);
    glEnd();

    // CEILING
    glBegin(GL_POLYGON);
    glColor3ub(120, 120, 115);
    glVertex2f(-408, 89);
    glVertex2f(-319, 90);
    glVertex2f(-388, 104);
    glVertex2f(-408, 101);
    glEnd();

    // UPPER BLOCK
    glBegin(GL_POLYGON);
    glColor3ub(150, 150, 145);
    glVertex2f(-408, 101);
    glVertex2f(-408, 141);
    glVertex2f(-387, 144);
    glVertex2f(-387, 100);
    glEnd();

    // SLANTING ROOF
    glBegin(GL_POLYGON);
    glColor3ub(110, 110, 105);
    glVertex2f(-387, 144);
    glVertex2f(-265, 121);
    glVertex2f(-266, 90);
    glVertex2f(-387, 90);
    glEnd();

    // BALCONY SLAB
    glBegin(GL_POLYGON);
    glColor3ub(80, 80, 80);
    glVertex2f(-433, 101);
    glVertex2f(-433, 93);
    glVertex2f(-208, 95);
    glVertex2f(-207, 89);
    glVertex2f(-319, 90);
    glVertex2f(-408, 101);
    glEnd();

    // SHOP SHUTTER
    glBegin(GL_POLYGON);
    glColor3ub(100, 90, 80);
    glVertex2f(-356, 19);
    glVertex2f(-329, 14);
    glVertex2f(-328, 80);
    glVertex2f(-354, 81);
    glEnd();

    // shutter lines
    glColor3ub(70, 60, 50);
    glBegin(GL_LINES);
    for (int i = 25; i <= 75; i += 5) {
        glVertex2f(-355, i);
        glVertex2f(-329, i - 1);
    }
    glEnd();

    // WINDOW
    glBegin(GL_POLYGON);
    glColor3ub(40, 40, 55);
    glVertex2f(-392, 23);
    glVertex2f(-380, 20);
    glVertex2f(-380, 80);
    glVertex2f(-392, 80);
    glEnd();
}

void labib_hut() {
    // DOOR INTERIOR
    glBegin(GL_POLYGON);
    glColor3ub(10, 10, 10);
    glVertex2f(-308, -13);
    glVertex2f(-210, -13);
    glColor3ub(80, 70, 60);
    glVertex2f(-215, -194);
    glVertex2f(-310, -200);
    glEnd();

    // LEFT SIDE WALL
    glBegin(GL_QUADS);
    glColor3ub(85, 75, 65);
    glVertex2f(-317, -17);
    glVertex2f(-321, -197);
    glVertex2f(-370, -190);
    glVertex2f(-370, -60);
    glEnd();

    // RIGHT SIDE WALL
    glBegin(GL_POLYGON);
    glColor3ub(110, 95, 80);
    glVertex2f(-208, -195);
    glVertex2f(-92, -193);
    glVertex2f(-96, -38);
    glVertex2f(-148, -15);
    glVertex2f(-205, -14);
    glEnd();

    // FRONT ROOF
    glBegin(GL_POLYGON);
    glColor3ub(155, 135, 95);
    glVertex2f(-232, 46);
    glVertex2f(-96, -38);
    glVertex2f(-148, -15);
    glVertex2f(-205, -14);
    glVertex2f(-308, -13);
    glVertex2f(-317, -17);
    glEnd();

    // RIGHT ROOF
    glBegin(GL_POLYGON);
    glColor3ub(135, 115, 80);
    glVertex2f(-232, 46);
    glVertex2f(-106, 3);
    glVertex2f(-51, -14);
    glVertex2f(-19, -30);
    glVertex2f(-96, -38);
    glVertex2f(-150, -30);
    glEnd();

    glColor3ub(160, 145, 100);

    // Vertical Bamboos (1 to 4)
    glBegin(GL_QUADS);
    glVertex2f(-375, -61);
    glVertex2f(-370, -60);
    glVertex2f(-370, -190);
    glVertex2f(-377, -191);
    glVertex2f(-308, -13);
    glVertex2f(-311, -200);
    glVertex2f(-321, -197);
    glVertex2f(-317, -17);
    glVertex2f(-205, -14);
    glVertex2f(-208, -195);
    glVertex2f(-215, -194);
    glVertex2f(-211, -13);
    glVertex2f(-90, -37);
    glVertex2f(-96, -38);
    glVertex2f(-92, -193);
    glVertex2f(-86, -193);
    glEnd();

    // Horizontal Bamboos (5 to 8)
    glColor3ub(140, 125, 90);
    glBegin(GL_QUADS);
    glVertex2f(-370, -80);
    glVertex2f(-370, -88);
    glVertex2f(-319, -86);
    glVertex2f(-319, -77);
    glVertex2f(-395, -145);
    glVertex2f(-395, -153);
    glVertex2f(-310, -157);
    glVertex2f(-310, -150);
    glVertex2f(-206, -93);
    glVertex2f(-206, -100);
    glVertex2f(-94, -104);
    glVertex2f(-94, -95);
    glVertex2f(-207, -150);
    glVertex2f(-207, -158);
    glVertex2f(-93, -157);
    glVertex2f(-93, -152);
    glEnd();

    // LEFT ROOF
    glBegin(GL_POLYGON);
    glColor3ub(145, 125, 90);
    glVertex2f(-232, 46);
    glVertex2f(-370, -60);
    glVertex2f(-409, -87);
    glVertex2f(-394, -59);
    glVertex2f(-317, -0.6);
    glEnd();
}

void labib_firePlace() {
    // Main Platform Surface
    glBegin(GL_POLYGON);
    glColor3ub(150, 130, 110);
    glVertex2f(-400, -300);
    glVertex2f(350, -300);
    glVertex2f(240, -210);
    glVertex2f(-50, -215);
    glVertex2f(-250, -220);
    glVertex2f(-400, -220);
    glEnd();

    //  Depth Detail
    glBegin(GL_QUADS);
    glColor3ub(110, 95, 80);
    glVertex2f(-400, -300);
    glVertex2f(-400, -220);
    glVertex2f(-410, -230);
    glVertex2f(-410, -305);
    glEnd();

    // Right Side
    glBegin(GL_QUADS);
    glColor3ub(120, 105, 90);
    glVertex2f(350, -300);
    glVertex2f(240, -210);
    glVertex2f(255, -220);
    glVertex2f(365, -305);
    glEnd();
}

void labib_dateTree() {
    // CURVED TREE TRUNK
    glBegin(GL_QUAD_STRIP);
    glColor3ub(70, 45, 30);
    glVertex2f(20, -195);
    glVertex2f(50, -195);
    glVertex2f(25, -100);
    glVertex2f(55, -100);
    glVertex2f(40, 0);
    glVertex2f(70, 0);
    glVertex2f(65, 100);
    glVertex2f(95, 100);
    glVertex2f(85, 160);
    glVertex2f(115, 160);
    glEnd();

    // PERFECTLY ALIGNED TRUNK TEXTURE
    glLineWidth(1.0);
    glColor3ub(40, 25, 15);
    glBegin(GL_LINES);
    for (int i = -190; i <= 155; i += 8) {
        float xShift = 0;
        // Curve mapping formula for alignment
        if (i < 0) xShift = 30 + (i + 200) * 0.12;
        else xShift = 54 + (i * 0.25);

        // line-er width (length)
        glVertex2f(xShift - 8, i);
        glVertex2f(xShift + 12, i - 2);
    }
    glEnd();

    // ROSH-ER HARI
    float potX = 85, potY = 85;

    // Pot Body
    glBegin(GL_POLYGON);
    glColor3ub(165, 85, 45);
    for (int i = 0; i <= 360; i += 20) {
        float angle = i * 3.14159 / 180;
        glVertex2f(potX + cos(angle) * 14, potY + sin(angle) * 14);
    }
    glEnd();

    // LARGE PALM LEAVES
    float tx = 100, ty = 160;

    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3ub(20, 70, 30);

    // Boro pata
    for(int j=0; j<12; j++) {
        float angleOffset = j * 30 * 3.14159 / 180;
        for(int k=0; k<20; k++) {
            float length = 115 + (k * 1.5);
            float spikeAngle = angleOffset + (k * 0.04);
            glVertex2f(tx, ty);
            glVertex2f(tx + cos(spikeAngle) * length, ty + sin(spikeAngle) * length);
        }
    }

    // JHULANO PATA (Drooping)
    glColor3ub(15, 60, 20);
    for(int j=190; j<350; j+=40) {
        float angleOffset = j * 3.14159 / 180;
        for(int k=0; k<20; k++) {
            float length = 145;
            float spikeAngle = angleOffset + (k * 0.03);
            glVertex2f(tx, ty);
            glVertex2f(tx + cos(spikeAngle) * length, ty + sin(spikeAngle) * (length * 0.82));
        }
    }
    glEnd();
}

void labib_dateTree2(){
    glPushMatrix();
        glTranslatef(-200, 50, 0);
        glScalef(0.5, 0.5, 1.0);
        labib_dateTree();
    glPopMatrix();
}

void labib_dateTree3(){
    glPushMatrix();
        glTranslatef(-480, 80, 0);
        glScalef(0.3, 0.3, 1.0);
        labib_dateTree();
    glPopMatrix();
}

//grass
void labib_grass() {
    srand(50);

    float base_x = -450;
    float base_y = -100;

    for (int i = 0; i < 30; i++) {
        float xOffset = (rand() % 24) - 12;
        float h = 12 + (rand() % 18);
        float bend = (rand() % 14) - 7;

        glBegin(GL_TRIANGLES);
        // Base
        glColor3ub(45, 60, 25);
        glVertex2f(base_x + xOffset - 4, base_y);
        glVertex2f(base_x + xOffset + 4, base_y);

        // Tip
        glColor3ub(130, 150, 80);
        glVertex2f(base_x + xOffset + bend, base_y + h);
        glEnd();
    }
}

void labib_grass2(){
    glPushMatrix();

    glTranslatef(-200, 65, 0);
    glScalef(0.5, 0.5, 1.0);

    labib_grass();
    glPopMatrix();
}

void labib_grass3(){
    glPushMatrix();

    glTranslatef(-220, 62, 0);
    glScalef(0.5, 0.5, 1.0);

    labib_grass();
    glPopMatrix();
}

void labib_grass4(){
    glPushMatrix();

    glTranslatef(-240, 68, 0);
    glScalef(0.5, 0.5, 1.0);

    labib_grass();
    glPopMatrix();
}

void labib_grass5(){
    glPushMatrix();

    glTranslatef(-220, 50, 0);
    glScalef(0.4, 0.4, 1.0);

    labib_grass();
    glPopMatrix();
}

void labib_grass6(){
    glPushMatrix();

    glTranslatef(-315, 65, 0);
    glScalef(0.4, 0.4, 1.0);

    labib_grass();
    glPopMatrix();
}

void labib_mudStove()
{
    glShadeModel(GL_SMOOTH);

    // MAIN BODY (BASE)
    glBegin(GL_POLYGON);

    glColor3ub(85, 60, 40);
    glVertex2f(-265, -287);
    glVertex2f(-212, -292);

    glColor3ub(110, 80, 55);
    glVertex2f(-180, -291);
    glVertex2f(-140, -280);

    glColor3ub(145, 110, 80);
    glVertex2f(-135, -260);
    glVertex2f(-151, -204);
    glVertex2f(-158, -187);

    glColor3ub(95, 70, 50);
    glVertex2f(-255, -242);

    glEnd();

    // UPPER CURVE
    glBegin(GL_POLYGON);

    glColor3ub(95, 70, 50);
    glVertex2f(-255, -242);
    glVertex2f(-248, -217);
    glVertex2f(-243, -195);
    glVertex2f(-233, -178);

    glColor3ub(130, 100, 75);
    glVertex2f(-228, -173);
    glVertex2f(-220, -172);
    glVertex2f(-211, -172);
    glVertex2f(-200, -170);

    glColor3ub(170, 135, 100);
    glVertex2f(-190, -165);
    glVertex2f(-183, -162);
    glVertex2f(-177, -165);
    glVertex2f(-170, -171);
    glVertex2f(-158, -187);

    glEnd();

    // INNER HOLE (DEPTH)
    glBegin(GL_POLYGON);

    glColor3ub(20, 10, 5);
    glVertex2f(-219, -185);
    glVertex2f(-206, -191);
    glVertex2f(-196, -190);
    glVertex2f(-183, -181);
    glVertex2f(-173, -176);
    glVertex2f(-165, -180);

    glColor3ub(45, 30, 20);
    glVertex2f(-185, -165);
    glVertex2f(-210, -175);

    glEnd();

    // FRONT MOUTH (FUEL)
    glBegin(GL_POLYGON);

    glColor3ub(10, 5, 2);
    glVertex2f(-233, -178);
    glVertex2f(-226, -178);
    glVertex2f(-219, -185);
    glVertex2f(-235, -205);

    glEnd();
}

void labib_smoke() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float stoveX[] = {-215.0f, -190.0f};

    for (int b = 0; b < 2; b++) {
        for (int i = 0; i < 5; i++) {

            // Dhowa upper logic
            float yOffset = fmod(i * 25.0f + labib_smokeTime * 20.0f, 130.0f);

            float currentY = -185.0f + yOffset;

            // "S" Shape curve logic
            float s_curve = sin(labib_smokeTime + (currentY * 0.06f)) * 12.0f;
            float xPos = stoveX[b] + s_curve;

            // Fading effect (Alpha)
            float alpha = (130.0f - yOffset) / 130.0f;

            // REALISTIC PUFFY SHAPE
            glBegin(GL_POLYGON);
            glColor4f(0.8f, 0.8f, 0.8f, alpha * 0.45f);

            glVertex2f(xPos - 5, currentY);
            glVertex2f(xPos + 5, currentY);
            glVertex2f(xPos + 12, currentY + 7);
            glVertex2f(xPos + 8, currentY + 15);
            glVertex2f(xPos, currentY + 20);
            glVertex2f(xPos - 8, currentY + 15);
            glVertex2f(xPos - 12, currentY + 7);
            glEnd();
        }
    }
    glDisable(GL_BLEND);
}

//date juice pot
void labib_dateJuicePot() {
    glShadeModel(GL_SMOOTH);

    // Surface
    glBegin(GL_POLYGON);
    glColor3ub(101, 67, 33);
    glVertex2f(-5.48, -215.43);
    glVertex2f(22.93, -244.49);
    glColor3ub(204, 119, 34);
    glVertex2f(238.22, -217.79);
    glVertex2f(200.00, -200.00);
    glEnd();

    // THE LEFT SIDE WALL
    glBegin(GL_POLYGON);
    glColor3ub(45, 45, 45);
    glVertex2f(-30.90, -182.46);
    glVertex2f(-8.47, -236.63);
    glVertex2f(30.40, -275.89);
    glVertex2f(22.93, -244.49);
    glEnd();

    // BACK WALL
    glBegin(GL_POLYGON);
    glColor3ub(50, 50, 50);
    glVertex2f(-30.90, -182.46);
    glVertex2f(206.08, -166.75);
    glVertex2f(200.00, -200.00);
    glVertex2f(-5.48, -215.43);
    glEnd();

    // RIGHT WALL
    glBegin(GL_POLYGON);
    glColor3ub(70, 70, 70);
    glVertex2f(206.08, -166.75);
    glVertex2f(299.52, -209.15);
    glVertex2f(238.22, -217.79);
    glVertex2f(200.00, -200.00);
    glEnd();

    // FRONT WALL
    glBegin(GL_POLYGON);
    glColor3ub(100, 100, 100);
    glVertex2f(22.93, -244.49);
    glVertex2f(299.52, -209.15);
    glVertex2f(270.36, -247.63);
    glVertex2f(30.40, -275.89);
    glEnd();

    // BOTTOM BASE / STAND
    glBegin(GL_POLYGON);
    glColor3ub(105, 75, 50);
    glVertex2f(40.87, -300.00);
    glVertex2f(41, -300.00);
    glVertex2f(269.62, -271.97);
    glVertex2f(270.36, -247.63);
    glVertex2f(30.40, -275.89);
    glVertex2f(-8.47, -236.63);
    glVertex2f(-2.49, -257.05);
    glVertex2f(40.87, -300.00);
    glEnd();
}

void labib_front_wall(){
    // FRONT WALL
    glBegin(GL_POLYGON);
    glColor3ub(100, 100, 100);
    glVertex2f(22.93, -244.49);
    glVertex2f(299.52, -209.15);
    glVertex2f(270.36, -247.63);
    glVertex2f(30.40, -275.89);
    glEnd();
}

//steam
void labib_steam(){
    glPushMatrix();
    glTranslatef(250.0f, -165.0f, 0.0f);
    glScalef(0.3f, 0.3f, 1.0f);
    float t = labib_smokeTime;
    labib_smokeTime *= 0.5;
    labib_smoke();
    labib_smokeTime = t;
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200.0f, -160.0f, 0.0f);
    glScalef(0.3f, 0.3f, 1.0f);
    float t2 = labib_smokeTime;
    labib_smokeTime *= 0.5;
    labib_smoke();
    labib_smokeTime = t2;
    glPopMatrix();

    glPushMatrix();
    glTranslatef(150.0f, -180.0f, 0.0f);
    glScalef(0.3f, 0.3f, 1.0f);
    float t3 = labib_smokeTime;
    labib_smokeTime *= 0.5;
    labib_smoke();
    labib_smokeTime = t3;
    glPopMatrix();

    glPushMatrix();
    glTranslatef(100.0f, -170.0f, 0.0f);
    glScalef(0.3f, 0.3f, 1.0f);
    float t4 = labib_smokeTime;
    labib_smokeTime *= 0.5;
    labib_smoke();
    labib_smokeTime = t4;
    glPopMatrix();
}

void labib_cookingWoman() {
    glShadeModel(GL_SMOOTH);

    //LOWER BODY (Shari - Natural Draping)
    glBegin(GL_POLYGON);
    glColor3ub(160, 25, 25);
    glVertex2f(-110.0 + labib_woman_x, -240.0);
    glVertex2f(-25.0 + labib_woman_x, -240.0);
    glColor3ub(180, 30, 30);
    glVertex2f(-30.0 + labib_woman_x, -155.0);
    glVertex2f(-50.0 + labib_woman_x, -150.0);
    glVertex2f(-100.0 + labib_woman_x, -152.0);
    glEnd();

    // Shari Pleats (Front detail)
    glLineWidth(1.5);
    glColor3ub(100, 15, 15);
    glBegin(GL_LINES);
    for (float x = -95.0; x < -35.0; x += 8.0) {
        glVertex2f(x + labib_woman_x, -150.0);
        glVertex2f(x - 2.0 + labib_woman_x, -240.0);
    }
    glEnd();

    // UPPER BODY (Blouse/Shari Anchol)
    glBegin(GL_POLYGON);
    glColor3ub(140, 20, 20);
    glVertex2f(-100.0 + labib_woman_x, -152.0);
    glVertex2f(-30.0 + labib_woman_x, -155.0);
    glVertex2f(-32.0 + labib_woman_x, -120.0);
    glColor3ub(180, 30, 30);
    glVertex2f(-38.0 + labib_woman_x, -105.0);
    glVertex2f(-65.0 + labib_woman_x, -98.0);
    glVertex2f(-92.0 + labib_woman_x, -105.0);
    glVertex2f(-98.0 + labib_woman_x, -120.0);
    glEnd();

    // GHOMTA (Veil behind head)
    glBegin(GL_POLYGON);
    glColor3ub(200, 50, 50);
    glVertex2f(-85.0 + labib_woman_x, -70.0);
    glVertex2f(-45.0 + labib_woman_x, -70.0);
    glColor3ub(180, 40, 40);
    glVertex2f(-42.0 + labib_woman_x, -95.0);
    glVertex2f(-50.0 + labib_woman_x, -110.0);
    glVertex2f(-80.0 + labib_woman_x, -110.0);
    glVertex2f(-88.0 + labib_woman_x, -95.0);
    glEnd();

    // Ghomta border detail
    glLineWidth(2.0);
    glColor3ub(220, 180, 50);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-85.0 + labib_woman_x, -70.0);
    glVertex2f(-45.0 + labib_woman_x, -70.0);
    glVertex2f(-42.0 + labib_woman_x, -95.0);
    glEnd();

    //  NECK
    glBegin(GL_QUADS);
    glColor3ub(235, 185, 140);
    glVertex2f(-72.0 + labib_woman_x, -98.0);
    glVertex2f(-58.0 + labib_woman_x, -98.0);
    glVertex2f(-60.0 + labib_woman_x, -88.0);
    glVertex2f(-70.0 + labib_woman_x, -88.0);
    glEnd();

    //  HAIR (Visible part - Behind head only)
    glColor3ub(20, 15, 10);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-65.0 + labib_woman_x, -75.0);
    for (int i = 0; i <= 12; i++) {
        float angle = 3.14159f * (1.15 + i * 0.2 / 12);
        glVertex2f(-65.0 + labib_woman_x + cos(angle) * 15, -75.0 + sin(angle) * 15);
    }
    glEnd();

    // Hair bun
    glColor3ub(25, 20, 15);
    labib_drawSunCircle(-78.0 + labib_woman_x, -78.0, 6);


    //  HEAD
    glColor3ub(235, 185, 140);
    labib_drawSunCircle(-65.0 + labib_woman_x, -75.0, 14);

    // Eyes
    glColor3ub(0, 0, 0);
    labib_drawSunCircle(-70.0 + labib_woman_x, -76.0, 2.5);
    labib_drawSunCircle(-60.0 + labib_woman_x, -76.0, 2.5);

    // Eye whites
    glColor3ub(255, 255, 255);
    labib_drawSunCircle(-70.0 + labib_woman_x, -76.0, 1.8);
    labib_drawSunCircle(-60.0 + labib_woman_x, -76.0, 1.8);

    // Pupils
    glColor3ub(50, 30, 20);
    labib_drawSunCircle(-70.0 + labib_woman_x, -76.0, 1.0);
    labib_drawSunCircle(-60.0 + labib_woman_x, -76.0, 1.0);

    // Eyebrows
    glLineWidth(1.5);
    glColor3ub(20, 15, 10);
    glBegin(GL_LINES);
    glVertex2f(-73.0 + labib_woman_x, -73.0);
    glVertex2f(-67.0 + labib_woman_x, -72.5); // Left eyebrow
    glVertex2f(-63.0 + labib_woman_x, -72.5);
    glVertex2f(-57.0 + labib_woman_x, -73.0); // Right eyebrow
    glEnd();

    // Nose (subtle)
    glBegin(GL_LINE_STRIP);
    glColor3ub(200, 150, 110);
    glVertex2f(-65.0 + labib_woman_x, -78.0);
    glVertex2f(-64.0 + labib_woman_x, -81.0);
    glVertex2f(-62.0 + labib_woman_x, -82.0);
    glEnd();

    // Lips (small smile)
    glLineWidth(2.0);
    glColor3ub(180, 80, 80);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-70.0 + labib_woman_x, -84.0);
    glVertex2f(-67.0 + labib_woman_x, -85.0);
    glVertex2f(-65.0 + labib_woman_x, -85.2);
    glVertex2f(-63.0 + labib_woman_x, -85.0);
    glVertex2f(-60.0 + labib_woman_x, -84.0);
    glEnd();

    // Bindi (forehead dot)
    glColor3ub(180, 0, 0);
    labib_drawSunCircle(-65.0 + labib_woman_x, -70.0, 1.5);

    // RIGHT ARM (reaching toward pot)
    // Upper arm
    glBegin(GL_POLYGON);
    glColor3ub(220, 175, 130);
    glVertex2f(-92.0 + labib_woman_x, -108.0);
    glVertex2f(-88.0 + labib_woman_x, -110.0);
    glVertex2f(-82.0 + labib_woman_x, -130.0);
    glVertex2f(-87.0 + labib_woman_x, -132.0);
    glVertex2f(-95.0 + labib_woman_x, -115.0);
    glEnd();

    // Lower arm (forearm)
    glBegin(GL_POLYGON);
    glColor3ub(210, 165, 120);
    glVertex2f(-82.0 + labib_woman_x, -130.0);
    glVertex2f(-87.0 + labib_woman_x, -132.0);
    glVertex2f(-95.0 + labib_woman_x, -158.0);
    glVertex2f(-88.0 + labib_woman_x, -160.0);
    glEnd();

    // Right hand (palm and fingers)
    glColor3ub(220, 175, 130);
    // Palm
    glBegin(GL_POLYGON);
    glVertex2f(-95.0 + labib_woman_x, -158.0);
    glVertex2f(-88.0 + labib_woman_x, -160.0);
    glVertex2f(-87.0 + labib_woman_x, -172.0);
    glVertex2f(-94.0 + labib_woman_x, -170.0);
    glEnd();

    // Fingers (simplified)
    glLineWidth(3.0);
    glColor3ub(200, 155, 110);
    glBegin(GL_LINES);
    // Thumb
    glVertex2f(-94.0 + labib_woman_x, -165.0);
    glVertex2f(-98.0 + labib_woman_x, -168.0);
    // Index finger
    glVertex2f(-92.0 + labib_woman_x, -170.0);
    glVertex2f(-93.0 + labib_woman_x, -177.0);
    // Middle finger
    glVertex2f(-90.0 + labib_woman_x, -171.0);
    glVertex2f(-90.0 + labib_woman_x, -179.0);
    // Ring finger
    glVertex2f(-88.0 + labib_woman_x, -170.0);
    glVertex2f(-87.0 + labib_woman_x, -177.0);
    glEnd();

    //LEFT ARM (holding khunti)
    glBegin(GL_POLYGON);
    glColor3ub(220, 175, 130);
    glVertex2f(-38.0 + labib_woman_x, -108.0);
    glVertex2f(-45.0 + labib_woman_x, -110.0);
    glVertex2f(-55.0 + labib_woman_x, -135.0);
    glVertex2f(-65.0 + labib_woman_x, -140.0);
    glVertex2f(-60.0 + labib_woman_x, -130.0);
    glVertex2f(-50.0 + labib_woman_x, -115.0);
    glEnd();

    // Hand holding khunti
    glColor3ub(210, 165, 120);
    labib_drawSunCircle(-65.0 + labib_woman_x, -142.0, 5);
}

void labib_khunti() {
    // KHUNTI HANDLE (Wooden Stick)
    // Main stick body
    glBegin(GL_QUADS);
    glColor3ub(90, 55, 30);
    glVertex2f(-67.0 + labib_woman_x, -142.0);
    glVertex2f(-63.0 + labib_woman_x, -142.0);
    glColor3ub(70, 45, 25);
    glVertex2f(100.0 + labib_woman_x, -208.0);
    glVertex2f(96.0 + labib_woman_x, -212.0);
    glEnd();

    // Wood grain detail
    glLineWidth(1.0);
    glColor3ub(60, 35, 20);
    glBegin(GL_LINES);
    for (int i = 0; i < 8; i++) {
        float t = i / 8.0;
        float x1 = -65.0 + labib_woman_x + t * 163.0;
        float y1 = -142.0 + t * (-68.0);
        glVertex2f(x1, y1);
        glVertex2f(x1 + 2, y1 - 1);
    }
    glEnd();

    // KHUNTI BLADE
    glBegin(GL_POLYGON);
    glColor3ub(75, 50, 30);
    glVertex2f(92.0 + labib_woman_x, -208.0);
    glVertex2f(108.0 + labib_woman_x, -208.0);
    glVertex2f(118.0 + labib_woman_x, -218.0);
    glVertex2f(115.0 + labib_woman_x, -230.0);
    glVertex2f(100.0 + labib_woman_x, -235.0);
    glVertex2f(85.0 + labib_woman_x, -230.0);
    glVertex2f(82.0 + labib_woman_x, -218.0);
    glEnd();

    // Blade edge highlight
    glLineWidth(2.0);
    glColor3ub(100, 70, 45);
    glBegin(GL_LINE_STRIP);
    glVertex2f(85.0 + labib_woman_x, -230.0);
    glVertex2f(100.0 + labib_woman_x, -235.0);
    glVertex2f(115.0 + labib_woman_x, -230.0);
    glEnd();

    // Blade texture lines
    glLineWidth(0.5);
    glColor3ub(55, 35, 20);
    glBegin(GL_LINES);
    glVertex2f(95.0 + labib_woman_x, -212.0);
    glVertex2f(95.0 + labib_woman_x, -228.0);
    glVertex2f(100.0 + labib_woman_x, -212.0);
    glVertex2f(100.0 + labib_woman_x, -230.0);
    glVertex2f(105.0 + labib_woman_x, -212.0);
    glVertex2f(105.0 + labib_woman_x, -228.0);
    glEnd();
}

void labib_display() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    labib_sky();
    labib_backtree();
    labib_river();
    labib_ground();
    labib_dateTree3();
    labib_building();
    labib_grass();
    labib_dateTree2();
    labib_grass2();
    labib_grass3();
    labib_grass4();
    labib_grass5();
    labib_grass6();
    labib_hut();
    labib_dateTree();
    labib_cookingWoman();
    labib_firePlace();
    labib_mudStove();
    labib_smoke();
    labib_dateJuicePot();
    labib_khunti();
    labib_front_wall();
    labib_steam();

    glFlush();
    glutSwapBuffers();
}

// ========================================
// SADEK PAGE DRAWING FUNCTIONS
// ========================================

void sadek_display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // top side background sky
    glBegin(GL_QUADS);
    glColor3ub(212, 241, 252);
    glVertex2f(-500.0f, -150.0f);
    glVertex2f(500.0f, -150.0f);
    glVertex2f(500.0f, 300.0f);
    glVertex2f(-500.0f, 300.0f);
    glEnd();

    // bird
    glPushMatrix();
    glTranslatef(sadek_positionc4, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3ub(3, 6, 8);
    glVertex2f(-250.0f, 231.0f);
    glVertex2f(-235.0f, 225.0f);
    glVertex2f(-235.0f, 222.0f);
    glVertex2f(-250.0f, 231.0f);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(3, 6, 8);
    glVertex2f(-220.0f, 231.0f);
    glVertex2f(-235.0f, 225.0f);
    glVertex2f(-235.0f, 222.0f);
    glVertex2f(-220.0f, 231.0f);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(3, 6, 8);
    glVertex2f(-200.0f, 231.0f);
    glVertex2f(-185.0f, 225.0f);
    glVertex2f(-185.0f, 222.0f);
    glVertex2f(-200.0f, 231.0f);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(3, 6, 8);
    glVertex2f(-170.0f, 231.0f);
    glVertex2f(-185.0f, 225.0f);
    glVertex2f(-185.0f, 222.0f);
    glVertex2f(-170.0f, 231.0f);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(3, 6, 8);
    glVertex2f(-225.0f, 246.0f);
    glVertex2f(-210.0f, 240.0f);
    glVertex2f(-210.0f, 237.0f);
    glVertex2f(-225.0f, 246.0f);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(3, 6, 8);
    glVertex2f(-195.0f, 246.0f);
    glVertex2f(-210.0f, 240.0f);
    glVertex2f(-210.0f, 237.0f);
    glVertex2f(-195.0f, 246.0f);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(3, 6, 8);
    glVertex2f(-225.0f, 216.0f);
    glVertex2f(-210.0f, 210.0f);
    glVertex2f(-210.0f, 207.0f);
    glVertex2f(-225.0f, 216.0f);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(3, 6, 8);
    glVertex2f(-195.0f, 216.0f);
    glVertex2f(-210.0f, 210.0f);
    glVertex2f(-210.0f, 207.0f);
    glVertex2f(-195.0f, 216.0f);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(3, 6, 8);
    glVertex2f(250.0f, 231.0f);
    glVertex2f(235.0f, 225.0f);
    glVertex2f(235.0f, 222.0f);
    glVertex2f(250.0f, 231.0f);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(3, 6, 8);
    glVertex2f(220.0f, 231.0f);
    glVertex2f(235.0f, 225.0f);
    glVertex2f(235.0f, 222.0f);
    glVertex2f(220.0f, 231.0f);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(3, 6, 8);
    glVertex2f(200.0f, 231.0f);
    glVertex2f(185.0f, 225.0f);
    glVertex2f(185.0f, 222.0f);
    glVertex2f(200.0f, 231.0f);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(3, 6, 8);
    glVertex2f(170.0f, 231.0f);
    glVertex2f(185.0f, 225.0f);
    glVertex2f(185.0f, 222.0f);
    glVertex2f(170.0f, 231.0f);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(3, 6, 8);
    glVertex2f(225.0f, 246.0f);
    glVertex2f(210.0f, 240.0f);
    glVertex2f(210.0f, 237.0f);
    glVertex2f(225.0f, 246.0f);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(3, 6, 8);
    glVertex2f(195.0f, 246.0f);
    glVertex2f(210.0f, 240.0f);
    glVertex2f(210.0f, 237.0f);
    glVertex2f(195.0f, 246.0f);
    glEnd();
    glPopMatrix();

    // fixed cloud 1 circle R1
    int i;
    GLfloat x = -415.0f; GLfloat y = -25.5f; GLfloat radius = 56.70576f;
    int triangleAmount = 100;
    GLfloat twicePi = 2.0f * PI;
    glColor3ub(94, 198, 242);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)),
                    y + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    // circle T1
    GLfloat a = -478.955f, b = -38.496f, radius2 = 33.04f;
    glColor3ub(94, 198, 242);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(a, b);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(a + (radius2 * cos(i * twicePi / triangleAmount)),
                    b + (radius2 * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    // circle V1
    GLfloat c = -320.893f, d = -45.6558f, radius3 = 50.328008f;
    glColor3ub(94, 198, 242);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(c, d);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(c + (radius3 * cos(i * twicePi / triangleAmount)),
                    d + (radius3 * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    // circle z1
    GLfloat e = -195.4815f, f = -86.7906f, radius4 = 60.550708f;
    glColor3ub(94, 198, 242);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(e, f);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(e + (radius4 * cos(i * twicePi / triangleAmount)),
                    f + (radius4 * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    // fixed clound 2
    // circle B2
    GLfloat g = 191.0119f, h = -72.7185f, radius5 = 46.3268f;
    glColor3ub(94, 198, 242);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(g, h);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(g + (radius5 * cos(i * twicePi / triangleAmount)),
                    h + (radius5 * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    // circle D2
    GLfloat j = 279.0785f, k = -63.0384f, radius6 = 44.6772f;
    glColor3ub(94, 198, 242);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(j, k);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(j + (radius6 * cos(i * twicePi / triangleAmount)),
                    k + (radius6 * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    // circle F2
    GLfloat l = 350.6775f, m = -45.1671f, radius7 = 43.0164f;
    glColor3ub(94, 198, 242);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(l, m);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(l + (radius7 * cos(i * twicePi / triangleAmount)),
                    m + (radius7 * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    // circle H2
    GLfloat n = 422.973f, o = -33.2532f, radius8 = 69.9348f;
    glColor3ub(94, 198, 242);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(n, o);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(n + (radius8 * cos(i * twicePi / triangleAmount)),
                    o + (radius8 * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    // flying clound 1 k9
    // circle k9
    GLfloat w = -316.3497f, z = 92.7f, radius11 = 34.96f;
    glColor3ub(132, 213, 245);
    glPushMatrix();
    glTranslatef(sadek_positionc1, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(w, z);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(w + (radius11 * cos(i * twicePi / triangleAmount)),
                    z + (radius11 * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    // circle m9
    GLfloat a1 = -357.5f, b1 = 74.1f, radius12 = 35.36f;
    glColor3ub(132, 213, 245);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(a1, b1);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(a1 + (radius12 * cos(i * twicePi / triangleAmount)),
                    b1 + (radius12 * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    // circle L9
    GLfloat c1 = -305.0f, d1 = 67.2f, radius13 = 34.96f;
    glColor3ub(132, 213, 245);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(c1, d1);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(c1 + (radius13 * cos(i * twicePi / triangleAmount)),
                    d1 + (radius13 * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    // circle P9
    GLfloat e1 = -268.5f, f1 = 81.9f, radius14 = 34.96f;
    glColor3ub(132, 213, 245);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(e1, f1);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(e1 + (radius14 * cos(i * twicePi / triangleAmount)),
                    f1 + (radius14 * sin(i * twicePi / triangleAmount)));
    }
    glEnd();
    glPopMatrix();

    // flying clound 2
    // circle R9
    GLfloat g1 = 271.0f, h1 = 134.4f, radius15 = 39.32f;
    glColor3ub(132, 213, 245);
    glPushMatrix();
    glTranslatef(sadek_positionc2, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(g1, h1);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(g1 + (radius15 * cos(i * twicePi / triangleAmount)),
                    h1 + (radius15 * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    // circle T9
    GLfloat i1 = 216.0f, j1 = 120.6f, radius16 = 39.32f;
    glColor3ub(132, 213, 245);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(i1, j1);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(i1 + (radius16 * cos(i * twicePi / triangleAmount)),
                    j1 + (radius16 * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    // circle S9
    GLfloat k1 = 276.0f, l1 = 105.0f, radius17 = 39.32f;
    glColor3ub(132, 213, 245);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(k1, l1);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(k1 + (radius17 * cos(i * twicePi / triangleAmount)),
                    l1 + (radius17 * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    // circle w9
    GLfloat m1 = 330.0f, n1 = 121.5f, radius18 = 39.32f;
    glColor3ub(132, 213, 245);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(m1, n1);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(m1 + (radius18 * cos(i * twicePi / triangleAmount)),
                    n1 + (radius18 * sin(i * twicePi / triangleAmount)));
    }
    glEnd();
    glPopMatrix();

    // flying clound 3
    // circle A10
    GLfloat q1 = -39.6f, r1 = 227.7f, radius19 = 44.0f;
    glColor3ub(132, 213, 245);
    glPushMatrix();
    glTranslatef(sadek_positionc2, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(q1, r1);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(q1 + (radius19 * cos(i * twicePi / triangleAmount)),
                    r1 + (radius19 * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    // circle c10
    GLfloat s1 = -97.0f, tt1 = 211.2f, radius20 = 44.0f;
    glColor3ub(132, 213, 245);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(s1, tt1);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(s1 + (radius20 * cos(i * twicePi / triangleAmount)),
                    tt1 + (radius20 * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    // circle E10
    GLfloat w1 = -40.35f, x1 = 188.4f, radius21 = 44.0f;
    glColor3ub(132, 213, 245);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(w1, x1);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(w1 + (radius21 * cos(i * twicePi / triangleAmount)),
                    x1 + (radius21 * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    // circle G10
    GLfloat y1 = 25.8f, z1 = 214.5f, radius22 = 44.0f;
    glColor3ub(132, 213, 245);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(y1, z1);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(y1 + (radius22 * cos(i * twicePi / triangleAmount)),
                    z1 + (radius22 * sin(i * twicePi / triangleAmount)));
    }
    glEnd();
    glPopMatrix();

    // Turbine 1 tower
    glBegin(GL_QUADS);
    glColor3ub(192, 192, 192);
    glVertex2f(-113.29211668565f, -84.24334610511f);
    glVertex2f(-97.9155325006f, -85.08501176577f);
    glVertex2f(-100.0f, 12.0f);
    glVertex2f(-107.56038013520f, 11.55380850771f);
    glEnd();

    // Turbine 1 blades (rotating)
    glPushMatrix();
    glTranslatef(-104.16904000f, 14.00185872f, 0.0f);
    glRotatef(sadek_j22, 0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLES);
    glColor3ub(192, 192, 192);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-80.0f, -10.0f);
    glVertex2f(-80.0f, 10.0f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3ub(192, 192, 192);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(40.0f, -69.28f);
    glVertex2f(40.0f, -49.28f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3ub(192, 192, 192);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(40.0f, 69.28f);
    glVertex2f(40.0f, 49.28f);
    glEnd();
    glPopMatrix();

    GLfloat u = -104.16904000f, v = 14.00185872f, radius9 = 8.688282773500f;
    glColor3ub(192, 192, 192);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(u, v);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(u + (radius9 * cos(i * twicePi / triangleAmount)),
                    v + (radius9 * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    // TURBINE 2 tower
    glBegin(GL_QUADS);
    glColor3ub(192, 192, 192);
    glVertex2f(170.937168321f, -85.43983119843f);
    glVertex2f(184.90011136445f, -85.24359524214f);
    glVertex2f(181.81459249760f, -12.66200802261f);
    glVertex2f(175.98406344835f, -12.81511374342f);
    glEnd();

    // Turbine 2 blades (rotating)
    glPushMatrix();
    glTranslatef(178.8064555f, -11.69889f, 0.0f);
    glRotatef(sadek_j33, 0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glColor3ub(192, 192, 192);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-80.0f, -10.0f);
    glVertex2f(-80.0f, 10.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(192, 192, 192);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(40.0f, -69.28f);
    glVertex2f(40.0f, -49.28f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(192, 192, 192);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(40.0f, 69.28f);
    glVertex2f(40.0f, 49.28f);
    glEnd();
    glPopMatrix();

    GLfloat ss = 178.8064555f, ttt = -11.69889f, radius10 = 8.688282773500f;
    glColor3ub(192, 192, 192);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(ss, ttt);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(ss + (radius10 * cos(i * twicePi / triangleAmount)),
                    ttt + (radius10 * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    // WATER
    glBegin(GL_QUADS);
    glColor3ub(124, 204, 243);
    glVertex2f(-500.0f, -300.0f);
    glVertex2f(500.0f, -300.0f);
    glVertex2f(499.0069f, -163.2008f);
    glVertex2f(-500.0f, -163.5596f);
    glEnd();

    // water flow all line
    glPushMatrix();
    glTranslatef(sadek_positionc5, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glColor3ub(67, 171, 240);
    glVertex2f(-442.0465f, -208.2151f);
    glVertex2f(-370.9966f, -207.3559f);
    glVertex2f(-469.3099f, -186.7349f);
    glVertex2f(-390.8245f, -182.4388f);
    glVertex2f(-415.6094f, -174.7057f);
    glVertex2f(-329.6885f, -171.2691f);
    glVertex2f(-308.2083f, -192.7493f);
    glVertex2f(-223.1137f, -188.4533f);
    glVertex2f(-272.6834f, -211.6520f);
    glVertex2f(-192.5457f, -208.2151f);
    glVertex2f(-238.8108f, -171.2691f);
    glVertex2f(-134.7144f, -172.9876f);
    glVertex2f(-150.4115f, -191.0309f);
    glVertex2f(-67.7953f, -186.7349f);
    glVertex2f(-90.9278f, -203.9190f);
    glVertex2f(-17.3994f, -200.4822f);
    glVertex2f(18.1255f, -172.9876f);
    glVertex2f(103.2202f, -170.4099f);
    glVertex2f(64.3906f, -189.3125f);
    glVertex2f(156.9207f, -186.7349f);
    glVertex2f(126.3527f, -203.0598f);
    glVertex2f(223.8398f, -200.4822f);
    glVertex2f(211.4473f, -177.2836f);
    glVertex2f(313.0652f, -172.9876f);
    glVertex2f(284.1496f, -187.5941f);
    glVertex2f(385.7674f, -188.4533f);
    glVertex2f(362.6349f, -175.5652f);
    glVertex2f(459.2958f, -175.5652f);
    glVertex2f(313.4783f, -206.4967f);
    glVertex2f(407.6607f, -202.2007f);
    glVertex2f(440.7072f, -188.4533f);
    glVertex2f(490.2769f, -186.7349f);
    glEnd();
    glPopMatrix();

    // land
    glBegin(GL_QUADS); // water top side
    glColor3ub(212, 228, 203);
    glVertex2f(-500.0f, -163.5596f);
    glVertex2f(499.0069f, -163.2008f);
    glVertex2f(500.0f, -150.0f);
    glVertex2f(-500.0f, -150.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(124, 174, 60);
    glVertex2f(-499.5862f, -281.0895f);
    glVertex2f(343.1680f, -260.3094f);
    glVertex2f(-499.8971f, -207.5628f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(157, 203, 87);
    glVertex2f(-500.0f, -300.0f);
    glVertex2f(500.0f, -300.0f);
    glVertex2f(500.2145f, -249.1786f);
    glVertex2f(-499.5862f, -281.0895f);
    glEnd();

    // ground tree 1
    glBegin(GL_QUADS);
    glColor3ub(87, 40, 11);
    glVertex2f(-154.0303f, -274.6677f);
    glVertex2f(-146.4360f, -274.4420f);
    glVertex2f(-147.1393f, -262.0954f);
    glVertex2f(-153.5658f, -262.2376f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3ub(59, 135, 63);
    glVertex2f(-169.8698f, -264.9644f);
    glVertex2f(-133.6343f, -263.1591f);
    glVertex2f(-151.8605f, -215.5452f);
    glEnd();

    // ground tree 2
    glBegin(GL_QUADS);
    glColor3ub(87, 40, 11);
    glVertex2f(36.4946f, -263.0909f);
    glVertex2f(47.4333f, -263.2331f);
    glVertex2f(46.0659f, -247.1641f);
    glVertex2f(36.4946f, -247.4485f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(59, 135, 63);
    glVertex2f(16.9416f, -247.1641f);
    glVertex2f(65.7556f, -246.3108f);
    glVertex2f(40.0f, -180.0f);
    glEnd();

    // house side senirio green
    glBegin(GL_POLYGON);
    glColor3ub(145, 194, 69);
    glVertex2f(-500.0f, -150.0f);
    glVertex2f(500.0f, -150.0f);
    glVertex2f(500.2440f, -124.5443f);
    glVertex2f(-128.4136f, -119.1480f);
    glVertex2f(-349.9366f, -124.0963f);
    glVertex2f(-500.0f, -127.6839f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(207, 240, 184);
    glVertex2f(-500.0f, -127.6839f);
    glVertex2f(-349.9366f, -124.0963f);
    glVertex2f(-128.4136f, -119.1480f);
    glVertex2f(500.2440f, -124.5443f);
    glVertex2f(500.0f, -120.0f);
    glVertex2f(210.9663f, -86.4268f);
    glVertex2f(210.9663f, -86.4268f);
    glVertex2f(-128.5970f, -88.5328f);
    glVertex2f(-330.1647f, -103.6724f);
    glVertex2f(-500.0f, -120.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(116, 166, 73);
    glVertex2f(-500.0f, -120.0f);
    glVertex2f(-71.6392f, -85.2001f);
    glVertex2f(-500.0f, -60.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(116, 166, 73);
    glVertex2f(500.0f, -120.0f);
    glVertex2f(500.0f, -60.0f);
    glVertex2f(210.9663f, -86.4268f);
    glEnd();

    // house side tree 1
    glBegin(GL_POLYGON);
    glColor3ub(49, 122, 53);
    glVertex2f(-481.1114f, -134.0301f);
    glVertex2f(-453.2438f, -133.4832f);
    glVertex2f(-446.3948f, -125.3644f);
    glVertex2f(-467.2202f, -87.1613f);
    glVertex2f(-489.1489f, -126.0637f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(87, 40, 11);
    glVertex2f(-471.15396f, -152.0079f);
    glVertex2f(-465.0008f, -151.7169f);
    glVertex2f(-466.3889f, -119.8124f);
    glVertex2f(-471.1211f, -119.8124f);
    glEnd();

    // house side tree 2
    glBegin(GL_POLYGON);
    glColor3ub(49, 122, 53);
    glVertex2f(-400.11596f, -125.3644f);
    glVertex2f(-364.2499f, -124.7628f);
    glVertex2f(-352.0001f, -112.9612f);
    glVertex2f(-382.6978f, -61.5687f);
    glVertex2f(-412.1476f, -113.7398f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(87, 40, 11);
    glVertex2f(-385.6328f, -150.1220f);
    glVertex2f(-378.3851f, -150.4361f);
    glVertex2f(-381.3152f, -103.7060f);
    glVertex2f(-385.0754f, -103.7060f);
    glEnd();

    // house side tree 3
    glBegin(GL_QUADS);
    glColor3ub(87, 40, 11);
    glVertex2f(178.1742f, -151.0642f);
    glVertex2f(191.1596f, -150.7503f);
    glVertex2f(188.7437f, -135.3610f);
    glVertex2f(179.6842f, -136.6173f);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(49, 122, 53);
    glVertex2f(184.5159f, -139.7579f);
    glVertex2f(211.6946f, -133.1625f);
    glVertex2f(184.2139f, -55.5885f);
    glVertex2f(155.2233f, -133.7907f);
    glEnd();

    // house side tree 4
    glBegin(GL_QUADS);
    glColor3ub(87, 40, 11);
    glVertex2f(228.6058f, -151.3782f);
    glVertex2f(237.6654f, -152.0064f);
    glVertex2f(236.7594f, -139.7579f);
    glVertex2f(229.2098f, -139.7579f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(49, 122, 53);
    glVertex2f(232.2546f, -142.8104f);
    glVertex2f(253.9676f, -137.6491f);
    glVertex2f(231.5059f, -78.4400f);
    glVertex2f(210.7912f, -138.1383f);
    glEnd();

    // houes no 1
    glBegin(GL_QUADS);
    glColor3ub(220, 220, 220);
    glVertex2f(-287.6277f, -146.0362f);
    glVertex2f(-198.5703f, -145.8509f);
    glVertex2f(-198.71995f, -108.5016f);
    glVertex2f(-287.9839f, -108.2474f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(124, 116, 114);
    glVertex2f(-287.6277f, -149.3705f);
    glVertex2f(-198.5703f, -149.5558f);
    glVertex2f(-198.5703f, -145.8509f);
    glVertex2f(-287.6277f, -146.0362f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(124, 116, 114);
    glVertex2f(-249.9726f, -146.3735f);
    glVertex2f(-250.0455f, -121.9551f);
    glVertex2f(-229.5623f, -121.9551f);
    glVertex2f(-230.0929f, -146.3360f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(124, 116, 114);
    glVertex2f(-198.71995f, -108.5016f);
    glVertex2f(-162.7985f, -82.3344f);
    glVertex2f(-255.7049f, -80.1010f);
    glVertex2f(-293.8455f, -108.7025f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(238, 238, 238);
    glVertex2f(-198.5703f, -145.8509f);
    glVertex2f(-129.7099f, -145.7193f);
    glVertex2f(-129.7886f, -109.4080f);
    glVertex2f(-164.5629f, -84.3986f);
    glVertex2f(-198.71995f, -108.5016f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(124, 116, 114);
    glVertex2f(-128.8433f, -110.2899f);
    glVertex2f(-123.4313f, -108.9390f);
    glVertex2f(-162.7985f, -82.3344f);
    glVertex2f(-164.5629f, -84.3986f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(124, 116, 114);
    glVertex2f(-198.5703f, -145.8509f);
    glVertex2f(-198.5703f, -149.5558f);
    glVertex2f(-122.1002f, -149.9737f);
    glVertex2f(-122.3946f, -146.6057f);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(166, 218, 226);
    glVertex2f(-178.8808f, -140.1078f);
    glVertex2f(-148.9899f, -139.6792f);
    glVertex2f(-149.2758f, -112.9115f);
    glVertex2f(-179.0283f, -112.8853f);
    glEnd();

    // HOUSE 2
    glBegin(GL_POLYGON);
    glColor3ub(238, 238, 238);
    glVertex2f(-85.3702f, -144.8892f);
    glVertex2f(-6.3295f, -144.8892f);
    glVertex2f(-8.2284f, -78.7323f);
    glVertex2f(-46.4433f, -52.0721f);
    glVertex2f(-83.9461f, -77.7449f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(122, 122, 122);
    glVertex2f(-85.84496f, -150.0731f);
    glVertex2f(-6.3295f, -150.31996f);
    glVertex2f(-6.3295f, -144.8892f);
    glVertex2f(-85.3702f, -144.8892f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(111, 111, 111);
    glVertex2f(-54.2700f, -144.3149f);
    glVertex2f(-31.5868f, -144.0149f);
    glVertex2f(-32.1756f, -105.3702f);
    glVertex2f(-53.8652f, -105.4471f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(248, 248, 248);
    glVertex2f(-6.3295f, -144.8892f);
    glVertex2f(139.6467f, -144.6423f);
    glVertex2f(139.1720f, -77.4981f);
    glVertex2f(-8.2284f, -78.7323f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(196, 196, 199);
    glVertex2f(-6.3295f, -150.31996f);
    glVertex2f(147.5732f, -149.9959f);
    glVertex2f(147.1480f, -144.0260f);
    glVertex2f(-6.3295f, -144.8892f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(108, 103, 101);
    glVertex2f(-8.2284f, -78.7323f);
    glVertex2f(148.6579f, -77.2505f);
    glVertex2f(104.7548f, -47.1350f);
    glVertex2f(-48.6612f, -47.8199f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(104, 99, 97);
    glVertex2f(-83.9461f, -77.7449f);
    glVertex2f(-45.4224f, -50.8846f);
    glVertex2f(-47.1692f, -46.8547f);
    glVertex2f(-91.5450f, -77.9600f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(77, 169, 184);
    glVertex2f(19.3670f, -131.0001f);
    glVertex2f(42.3293f, -130.3081f);
    glVertex2f(42.1307f, -116.2413f);
    glVertex2f(19.6998f, -115.7720f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(77, 169, 184);
    glVertex2f(58.0648f, -130.5699f);
    glVertex2f(80.9325f, -130.3081f);
    glVertex2f(81.4126f, -115.8624f);
    glVertex2f(57.9703f, -115.7720f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(77, 169, 184);
    glVertex2f(97.5718f, -131.0001f);
    glVertex2f(119.3593f, -130.6474f);
    glVertex2f(119.4559f, -115.4777f);
    glVertex2f(97.9046f, -115.0798f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(77, 169, 184);
    glVertex2f(97.6248f, -106.6371f);
    glVertex2f(120.0355f, -106.8380f);
    glVertex2f(120.1321f, -92.4720f);
    glVertex2f(97.6248f, -92.3715f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(77, 169, 184);
    glVertex2f(58.1164f, -106.9385f);
    glVertex2f(80.4305f, -106.2352f);
    glVertex2f(80.5997f, -93.6218f);
    glVertex2f(57.9703f, -92.2376f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(77, 169, 184);
    glVertex2f(19.4453f, -107.1404f);
    glVertex2f(42.1200f, -106.9788f);
    glVertex2f(41.5317f, -92.7699f);
    glVertex2f(19.2842f, -92.6729f);
    glEnd();

    // house 3
    glBegin(GL_QUADS);
    glColor3ub(234, 234, 234);
    glVertex2f(264.5735f, -146.5714f);
    glVertex2f(376.1965f, -146.5714f);
    glVertex2f(377.0668f, -104.9337f);
    glVertex2f(263.9207f, -104.9337f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(224, 224, 224);
    glVertex2f(376.1965f, -146.5714f);
    glVertex2f(448.6907f, -146.4565f);
    glVertex2f(447.7776f, -105.0634f);
    glVertex2f(412.0185f, -80.0854f);
    glVertex2f(377.0668f, -104.9337f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(88, 85, 84);
    glVertex2f(256.3902f, -150.5113f);
    glVertex2f(376.2251f, -149.6711f);
    glVertex2f(376.1965f, -146.5714f);
    glVertex2f(256.3485f, -146.5560f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(80, 78, 77);
    glVertex2f(376.1965f, -146.5714f);
    glVertex2f(376.2251f, -149.6711f);
    glVertex2f(448.6197f, -149.4038f);
    glVertex2f(448.6907f, -146.4565f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(101, 96, 94);
    glVertex2f(295.6342f, -76.0911f);
    glVertex2f(256.7111f, -104.5476f);
    glVertex2f(377.0668f, -104.9337f);
    glVertex2f(415.7201f, -76.9397f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(160, 156, 161);
    glVertex2f(412.0185f, -80.0854f);
    glVertex2f(447.7776f, -105.0634f);
    glVertex2f(455.2600f, -104.4398f);
    glVertex2f(415.7201f, -76.9397f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(103, 103, 103);
    glVertex2f(403.8757f, -122.3875f);
    glVertex2f(403.8757f, -146.8655f);
    glVertex2f(427.6117f, -147.2804f);
    glVertex2f(427.4122f, -121.7652f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(160, 156, 161);
    glVertex2f(293.2223f, -134.6902f);
    glVertex2f(343.2883f, -134.4567f);
    glVertex2f(342.8393f, -115.5440f);
    glVertex2f(292.9978f, -115.5440f);
    glEnd();

    glFlush();
    glutSwapBuffers();
}

// ========================================
// NOOR PAGE DRAWING FUNCTIONS
// ========================================

void noor_man() {
    glPushMatrix();
    glTranslatef(sin(noor_manMove) * 30, cos(noor_manMove) * 15, 0);

    glColor3ub(173, 161, 161);
    glBegin(GL_QUADS);
    glVertex2i(40, -210);
    glVertex2i(40, -170);
    glVertex2i(45, -170);
    glVertex2i(45, -210);
    glEnd();

    glColor3ub(173, 161, 161);
    glBegin(GL_QUADS);
    glVertex2i(60, -210);
    glVertex2i(60, -170);
    glVertex2i(65, -170);
    glVertex2i(65, -210);
    glEnd();

    glColor3ub(99, 34, 34);
    glBegin(GL_QUADS);
    glVertex2i(20, -170);
    glVertex2i(80, -170);
    glVertex2i(80, -144);
    glVertex2i(20, -144);
    glEnd();

    glColor3ub(179, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2i(20, -144);
    glVertex2i(80, -144);
    glVertex2i(50, -115);
    glEnd();

    glColor3ub(138, 87, 78);
    glBegin(GL_TRIANGLES);
    glVertex2i(50, -115.8);
    glVertex2i(74.7122603167787, -125.1999832664694);
    glVertex2i(90.3262737681194, -127.2146946795451);
    glEnd();

    glColor3ub(138, 87, 78);
    glBegin(GL_TRIANGLES);
    glVertex2i(90.3262737681194, -127.2146946795451);
    glVertex2i(84.0303006022562, -132.6292316021859);
    glVertex2i(49.9061260432777, -143.5842249107847);
    glEnd();

    // Yarn
    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2i(77.9, -123.6);
    glVertex2i(80.8, -124.5);
    glVertex2i(302, 178);
    glVertex2i(300, 180);
    glEnd();

    // Kite
    glColor3ub(231, 245, 78);
    glBegin(GL_TRIANGLES);
    glVertex2i(300, 178);
    glVertex2i(270, 205);
    glVertex2i(330, 205);
    glEnd();

    glColor3ub(230, 41, 197);
    glBegin(GL_TRIANGLES);
    glVertex2i(300, 230);
    glVertex2i(270, 205);
    glVertex2i(330, 205);
    glEnd();

    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(50.0 + 23 * cos(angle), -100.0 + 23 * sin(angle));
    }
    glEnd();
    glPopMatrix();
}

void noor_sun() {
    if (!noor_isNight) {
        // Sun
        glColor3ub(255, 255, 0);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 100; i++) {
            float angle = 2 * 3.1416f * i / 100;
            glVertex2f(0.0f + 32 * cos(angle), 250.0f + 32 * sin(angle));
        }
        glEnd();

        // Glow when light ON
        if (noor_lightOn) {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(1.0f, 1.0f, 0.0f, 0.3f);
            glBegin(GL_POLYGON);
            for (int i = 0; i < 100; i++) {
                float angle = 2 * 3.1416f * i / 100;
                glVertex2f(0.0f + 45 * cos(angle), 250.0f + 45 * sin(angle));
            }
            glEnd();
            glDisable(GL_BLEND);
        }
    } else {
        // Moon
        glColor3ub(220, 220, 220);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 100; i++) {
            float angle = 2 * 3.1416f * i / 100;
            glVertex2f(0.0f + 28 * cos(angle), 250.0f + 28 * sin(angle));
        }
        glEnd();

        // Moon glow when light ON
        if (noor_lightOn) {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(0.8f, 0.8f, 1.0f, 0.3f);
            glBegin(GL_POLYGON);
            for (int i = 0; i < 100; i++) {
                float angle = 2 * 3.1416f * i / 100;
                glVertex2f(0.0f + 40 * cos(angle), 250.0f + 40 * sin(angle));
            }
            glEnd();
            glDisable(GL_BLEND);
        }
    }
}

void noor_cloud() {
    glPushMatrix();
    glTranslatef(noor_cloudPos1, 0.0f, 0.0f);

    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(-350.0f + 27 * cos(angle), 260.0f + 27 * sin(angle));
    }
    glEnd();

    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(-324.0f + 29 * cos(angle), 260.0f + 29 * sin(angle));
    }
    glEnd();

    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(-300.0f + 26 * cos(angle), 260.0f + 26 * sin(angle));
    }
    glEnd();
    glPopMatrix();

    // 2nd Cloud
    glPushMatrix();
    glTranslatef(noor_cloudPos2, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(240.0f + 27 * cos(angle), 250.0f + 27 * sin(angle));
    }
    glEnd();

    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(270.0f + 29 * cos(angle), 250.0f + 29 * sin(angle));
    }
    glEnd();

    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(305.0f + 26 * cos(angle), 250.0f + 26 * sin(angle));
    }
    glEnd();

    glPopMatrix();
}

void noor_river() {
    glColor3ub(120, 204, 250);
    glBegin(GL_QUADS);
    glVertex2i(-500, 160);
    glVertex2i(-500, -300);
    glVertex2i(500, -300);
    glVertex2i(500, 160);
    glEnd();

    // Moving Waves
    glColor3ub(255, 255, 255);

    for (int y = -260; y <= 120; y += 40) {
        glBegin(GL_LINE_STRIP);
        for (int x = -500; x <= 500; x += 10) {
            float wave = sin((x * 0.05f) + noor_wavePos) * 5;
            glVertex2f(x, y + wave);
        }
        glEnd();
    }
}

void noor_boat1() {
    glPushMatrix();
    glTranslatef(noor_boatPos, 0.0f, 0.0f);

    glColor3ub(204, 211, 255);
    glBegin(GL_QUADS);
    glVertex2i(200, 110);
    glVertex2i(230, 85);
    glVertex2i(440, 85);
    glVertex2i(480, 110);
    glEnd();

    glColor3ub(161, 0, 75);
    glBegin(GL_TRIANGLES);
    glVertex2i(250, 110);
    glVertex2i(300, 150);
    glVertex2i(300, 110);
    glEnd();

    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2i(300, 150);
    glVertex2i(300, 110);
    glVertex2i(305, 110);
    glVertex2i(305, 150);
    glEnd();

    glColor3ub(64, 0, 161);
    glBegin(GL_QUADS);
    glVertex2i(350, 110);
    glVertex2i(350, 140);
    glVertex2i(355, 140);
    glVertex2i(355, 110);
    glEnd();

    glColor3ub(247, 232, 0);
    glBegin(GL_QUADS);
    glVertex2i(385, 110);
    glVertex2i(385, 140);
    glVertex2i(390, 140);
    glVertex2i(390, 110);
    glEnd();

    glPopMatrix();
}

void noor_boat23() {
    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2i(151, -78);
    glVertex2i(187.8527498833496, -99.8489041468435);
    glVertex2i(310.9419779347717, -99.8489041468435);
    glVertex2i(346.3021561749983, -77.6928430975898);
    glEnd();

    glColor3ub(232, 109, 109);
    glBegin(GL_QUADS);
    glVertex2i(180, -78);
    glVertex2i(207.32322777512, -55.7605806447933);
    glVertex2i(299.9758467083723, -55.5367820483362);
    glVertex2i(319.8939217930569, -77.2452459046756);
    glEnd();

    // 2nd Boat
    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2i(150, -200);
    glVertex2i(190, -220);
    glVertex2i(280, -220);
    glVertex2i(310, -200);
    glVertex2i(280, -184);
    glVertex2i(190, -184);
    glEnd();

    glColor3ub(143, 130, 103);
    glBegin(GL_TRIANGLES);
    glVertex2i(155, -200);
    glVertex2i(187.5942785607597, -187.4638184473088);
    glVertex2i(186.6731128251513, -216.0490688575709);
    glEnd();

    glColor3ub(143, 130, 103);
    glBegin(GL_QUADS);
    glVertex2i(191.5781072227604, -186.7709786800044);
    glVertex2i(229.5393277462848, -186.8345056746612);
    glVertex2i(229.6982276014332, -216.2309788771189);
    glVertex2i(191.4910112031296, -216.3836243462493);
    glEnd();

    glColor3ub(143, 130, 103);
    glBegin(GL_QUADS);
    glVertex2i(237.9037319294142, -186.7967459824215);
    glVertex2i(276.0626877673477, -186.5999894333075);
    glVertex2i(276.0969853047771, -216.3898787322673);
    glVertex2i(238, -216);
    glEnd();

    glColor3ub(143, 130, 103);
    glBegin(GL_TRIANGLES);
    glVertex2i(281.8173800901213, -187.4701050952548);
    glVertex2i(281.8173800901213, -215.5953794565252);
    glVertex2i(305.1756587969418, -199.8642937968316);
    glEnd();
}

void noor_sky() {
    if (!noor_isNight) {
        // Day sky
        glColor3ub(91, 167, 235);   // light blue
    } else {
        // Night sky
        glColor3ub(20, 20, 60);     // dark blue
    }

    glBegin(GL_QUADS);
    glVertex2i(-500, 300);
    glVertex2i(-500, 160);
    glVertex2i(500, 160);
    glVertex2i(500, 300);
    glEnd();
}

void noor_mountain() {
    glColor3ub(58, 161, 45);
    glBegin(GL_POLYGON);
    glVertex2i(-500, 160);
    glVertex2i(-464.746784273134, 181.383633805202);
    glVertex2i(-422.990525723646, 202.1808941591226);
    glVertex2i(-340.4285336108089, 222.8213921873319);
    glVertex2i(-266.1227407092555, 202.1808941591226);
    glVertex2i(-232.0659189627102, 180.5083712295028);
    glVertex2i(-200, 160);
    glEnd();

    // Mountain 2nd
    glColor3ub(58, 161, 45);
    glBegin(GL_POLYGON);
    glVertex2i(-200, 160);
    glVertex2i(-175, 180);
    glVertex2i(-145.3758272442313, 191.860645145018);
    glVertex2i(-100, 200);
    glVertex2i(-62.8138351313942, 192.8926700464284);
    glVertex2i(-33.9171378919012, 180.5083712295028);
    glVertex2i(0, 160);
    glEnd();

    // Mountain 3rd
    glColor3ub(58, 161, 45);
    glBegin(GL_POLYGON);
    glVertex2i(0, 160);
    glVertex2i(38.3246052068313, 184.6364708351447);
    glVertex2i(78.5735763618393, 201.1488692577121);
    glVertex2i(158.039493770445, 215.757342384511);
    glVertex2i(239.5694609818717, 198.0527945534808);
    glVertex2i(278.7864072354693, 180.5083712295028);
    glVertex2i(305, 160);
    glEnd();

    // Mountain 4th
    glColor3ub(58, 161, 45);
    glBegin(GL_POLYGON);
    glVertex2i(305, 160);
    glVertex2i(334.6436888828833, 178.5722583979312);
    glVertex2i(370.466040832668, 189.6601292395312);
    glVertex2i(400, 195);
    glVertex2i(437.8461790239297, 189.6601292395312);
    glVertex2i(463.4335732737759, 180.2780846812543);
    glVertex2i(500, 160);
    glEnd();
}

void noor_ground() {
    glColor3ub(105, 240, 84);
    glBegin(GL_QUADS);
    glVertex2i(-500, 20);
    glVertex2i(-500, -300);
    glVertex2i(100, -300);
    glVertex2i(100, 20);
    glEnd();

    glColor3ub(105, 240, 84);
    glBegin(GL_TRIANGLES);
    glVertex2i(100, 20);
    glVertex2i(150, 0);
    glVertex2i(100, -30);
    glEnd();

    glColor3ub(105, 240, 84);
    glBegin(GL_TRIANGLES);
    glVertex2i(100, -100);
    glVertex2i(160, -70);
    glVertex2i(100, -30);
    glEnd();

    glColor3ub(105, 240, 84);
    glBegin(GL_TRIANGLES);
    glVertex2i(100, -100);
    glVertex2i(130, -130);
    glVertex2i(100, -150);
    glEnd();

    glColor3ub(105, 240, 84);
    glBegin(GL_QUADS);
    glVertex2i(100, -250);
    glVertex2i(150, -236);
    glVertex2i(150, -168);
    glVertex2i(100, -150);
    glEnd();

    glColor3ub(105, 240, 84);
    glBegin(GL_TRIANGLES);
    glVertex2i(100, -250);
    glVertex2i(150, -280);
    glVertex2i(100, -300);
    glEnd();

    glColor3ub(219, 169, 103);
    glBegin(GL_QUADS);
    glVertex2i(160, -70);
    glVertex2i(159, -74);
    glVertex2i(103, -102);
    glVertex2i(100, -100);
    glEnd();

    glColor3ub(219, 169, 103);
    glBegin(GL_QUADS);
    glVertex2i(148, -6);
    glVertex2i(105, -30);
    glVertex2i(100, -30);
    glVertex2i(150, 0);
    glEnd();

    glColor3ub(219, 169, 103);
    glBegin(GL_QUADS);
    glVertex2i(130, -134);
    glVertex2i(106, -150);
    glVertex2i(100, -150);
    glVertex2i(130, -130);
    glEnd();

    glColor3ub(219, 169, 103);
    glBegin(GL_QUADS);
    glVertex2i(148, -240);
    glVertex2i(106, -251);
    glVertex2i(100, -250);
    glVertex2i(150, -236);
    glEnd();

    glColor3ub(219, 169, 103);
    glBegin(GL_QUADS);
    glVertex2i(149, -283);
    glVertex2i(105, -300);
    glVertex2i(100, -300);
    glVertex2i(150, -280);
    glEnd();
}

void noor_village1() {
    glColor3ub(219, 169, 103);
    glBegin(GL_QUADS);
    glVertex2i(-80, -60);
    glVertex2i(80, -60);
    glVertex2i(80, 40);
    glVertex2i(-80, 40);
    glEnd();

    glColor3ub(230, 44, 109);
    glBegin(GL_QUADS);
    glVertex2i(-120, 40);
    glVertex2i(120, 40);
    glVertex2i(80, 85);
    glVertex2i(-80, 85);
    glEnd();

    // Window 1
    glColor3ub(115, 91, 222);
    glBegin(GL_QUADS);
    glVertex2i(-60, 10);
    glVertex2i(-30, 10);
    glVertex2i(-30, -20);
    glVertex2i(-60, -20);
    glEnd();

    // Window 2
    glColor3ub(115, 91, 222);
    glBegin(GL_QUADS);
    glVertex2i(40, 10);
    glVertex2i(70, 10);
    glVertex2i(70, -10);
    glVertex2i(40, -10);
    glEnd();

    // Door 1
    glColor3ub(209, 42, 6);
    glBegin(GL_QUADS);
    glVertex2i(-10, -60);
    glVertex2i(-10, 10);
    glVertex2i(20, 10);
    glVertex2i(20, -60);
    glEnd();
}

void noor_village2() {
    glColor3ub(154, 245, 245);
    glBegin(GL_QUADS);
    glVertex2i(-250, -80);
    glVertex2i(-70, -80);
    glVertex2i(-70, 20);
    glVertex2i(-250, 20);
    glEnd();

    glColor3ub(245, 231, 39);
    glBegin(GL_QUADS);
    glVertex2i(-300, 20);
    glVertex2i(-250, 70);
    glVertex2i(-70, 70);
    glVertex2i(-20, 20);
    glEnd();

    // Window 1
    glColor3ub(12, 41, 237);
    glBegin(GL_QUADS);
    glVertex2i(-240, 0);
    glVertex2i(-200, 0);
    glVertex2i(-200, -40);
    glVertex2i(-240, -40);
    glEnd();

    // Window 2
    glColor3ub(12, 41, 237);
    glBegin(GL_QUADS);
    glVertex2i(-120, -12);
    glVertex2i(-86, -12);
    glVertex2i(-85, -40);
    glVertex2i(-120, -40);
    glEnd();

    // Door 1
    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2i(-180, -80);
    glVertex2i(-180, 0);
    glVertex2i(-140, 0);
    glVertex2i(-140, -80);
    glEnd();
}

void noor_tree() {
    glColor3ub(102, 7, 7);
    glBegin(GL_QUADS);
    glVertex2i(-400, -100);
    glVertex2i(-400, 40);
    glVertex2i(-350, 40);
    glVertex2i(-350, -100);
    glEnd();

    glColor3ub(102, 7, 7);
    glBegin(GL_TRIANGLES);
    glVertex2i(-400, 30);
    glVertex2i(-420, 60);
    glVertex2i(-390, 40);
    glEnd();

    glColor3ub(102, 7, 7);
    glBegin(GL_QUADS);
    glVertex2i(-380, 40);
    glVertex2i(-380, 60);
    glVertex2i(-370, 60);
    glVertex2i(-370, 40);
    glEnd();

    glColor3ub(102, 7, 7);
    glBegin(GL_TRIANGLES);
    glVertex2i(-360, 40);
    glVertex2i(-330, 60);
    glVertex2i(-350, 30);
    glEnd();

    // Peak
    glColor3ub(102, 7, 7);
    glBegin(GL_TRIANGLES);
    glVertex2i(-400, -90);
    glVertex2i(-390, -100);
    glVertex2i(-430, -120);
    glEnd();

    glColor3ub(102, 7, 7);
    glBegin(GL_TRIANGLES);
    glVertex2i(-370, -120);
    glVertex2i(-390, -100);
    glVertex2i(-360, -100);
    glEnd();

    glColor3ub(102, 7, 7);
    glBegin(GL_TRIANGLES);
    glVertex2i(-350, -90);
    glVertex2i(-320, -120);
    glVertex2i(-360, -100);
    glEnd();

    // Leaves
    glColor3ub(34, 139, 34);

    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(-380 + 60 * cos(angle), 110 + 60 * sin(angle));
    }
    glEnd();

    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(-430 + 45 * cos(angle), 90 + 45 * sin(angle));
    }
    glEnd();

    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(-330 + 45 * cos(angle), 90 + 45 * sin(angle));
    }
    glEnd();

    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(-380 + 40 * cos(angle), 160 + 40 * sin(angle));
    }
    glEnd();
}

void noor_bird() {
    glPushMatrix();
    glTranslatef(noor_birdPos, 0.0f, 0.0f);

    glColor3ub(223, 223, 237);
    glBegin(GL_POLYGON);
    glVertex2i(-240, 260);
    glVertex2i(-235, 257);
    glVertex2i(-220, 256);
    glVertex2i(-213.5, 257.5);
    glVertex2i(-205, 261);
    glVertex2i(-212, 264);
    glEnd();

    glColor3ub(0, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2i(-219, 263);
    glVertex2i(-223.998, 262.286);
    glVertex2i(-228, 274);
    glEnd();

    glColor3ub(0, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2i(-221.5, 262.6);
    glVertex2i(-226, 262);
    glVertex2i(-234, 272);
    glEnd();

    // Bird 2
    glColor3ub(223, 223, 237);
    glBegin(GL_POLYGON);
    glVertex2i(-180, 260);
    glVertex2i(-165.111274483683, 251.8894051197357);
    glVertex2i(-150, 250);
    glVertex2i(-130, 255);
    glVertex2i(-115, 260);
    glVertex2i(-125, 265);
    glEnd();

    glColor3ub(0, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2i(-140.2006508780443, 263.618680535182);
    glVertex2i(-155, 285);
    glVertex2i(-150, 262);
    glEnd();

    glColor3ub(0, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2i(-145.0091121683544, 263.1765486971623);
    glVertex2i(-170, 285);
    glVertex2i(-156.9176891968369, 262.0546857933332);
    glEnd();

    glPopMatrix();
}

void noor_rain() {
    if (!noor_isRaining) return;

    glColor3ub(0, 0, 255); // blue rain

    for (int i = 0; i < 200; i++) {
        int x = rand() % 1000 - 500;
        int y = rand() % 600 - 300;

        glBegin(GL_LINES);
        glVertex2i(x, y);
        glVertex2i(x + 2, y - 10);
        glEnd();
    }
}

void noor_display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    noor_sky();
    noor_mountain();
    noor_sun();

    noor_cloud();
    noor_river();
    noor_boat1();
    noor_boat23();
    noor_ground();
    noor_village1();
    noor_village2();
    noor_tree();
    noor_bird();
    noor_man();
    noor_rain();

    glFlush();
    glutSwapBuffers();
}

// ========================================
// MAIN DISPLAY CONTROLLER
// ========================================
void display() {
    if (currentPage == 0) {
        cover_display();
    } else if (currentPage == 1) {
        shah_display();
    } else if (currentPage == 2) {
        abir_display();
    } else if (currentPage == 3) {
        labib_display();
    } else if (currentPage == 4) {
        sadek_display();
    } else if (currentPage == 5) {
        noor_display();
    }
}

// ========================================
// ANIMATION UPDATE
// ========================================
void update(int value)
{
    // Cover page animations
    if (currentPage == 0) {
        cover_cloud1_x += 0.2f;
        cover_cloud2_x += 0.4f;
        cover_cloud3_x += 0.6f;

        if (cover_cloud1_x > 600) cover_cloud1_x = -600;
        if (cover_cloud2_x > 600) cover_cloud2_x = -600;
        if (cover_cloud3_x > 600) cover_cloud3_x = -600;

        cover_bird1_x += 0.8f;
        cover_bird2_x -= 1.2f;
        cover_bird3_x += 0.5f;

        if (cover_bird1_x > 600) cover_bird1_x = -600;
        if (cover_bird2_x < -600) cover_bird2_x = 600;
        if (cover_bird3_x > 600) cover_bird3_x = -600;

        if (cover_wing_dir == 1) {
            cover_wing_pos += 0.15f;
            if (cover_wing_pos >= 1.0f) cover_wing_dir = 0;
        } else {
            cover_wing_pos -= 0.15f;
            if (cover_wing_pos <= 0.0f) cover_wing_dir = 1;
        }

        cover_smoke_y += 1.5f;
        if (cover_smoke_y > 120) cover_smoke_y = 0;

        if (cover_glow_dir == 1) {
            cover_sun_glow += 0.5f;
            if (cover_sun_glow >= 100.0f) cover_glow_dir = 0;
        } else {
            cover_sun_glow -= 0.5f;
            if (cover_sun_glow <= 30.0f) cover_glow_dir = 1;
        }

        if (cover_sway_dir == 1) {
            cover_tree_sway += 0.08f;
            if (cover_tree_sway >= 2.5f) cover_sway_dir = 0;
        } else {
            cover_tree_sway -= 0.08f;
            if (cover_tree_sway <= -2.5f) cover_sway_dir = 1;
        }

        cover_water_ripple += 0.05f;
        if (cover_water_ripple > 6.28f) cover_water_ripple = 0;

        cover_leaf_fall_y += 0.5f;
        if (cover_leaf_fall_y > 100) cover_leaf_fall_y = 0;
    }

    // Shahariyer page animations
    if (currentPage == 1) {
        cloudMove += 0.2f;
        if (cloudMove > 1200) cloudMove = -1200;

        birdMove1 += 2.0f;
        birdMove2 += 1.4f;
        birdMove3 += 1.8f;
        if (birdMove1 > 650) birdMove1 = -650;
        if (birdMove2 > 650) birdMove2 = -650;
        if (birdMove3 > 650) birdMove3 = -650;

        bigBoatMove1 += 0.3f;
        if (bigBoatMove1 > 700) bigBoatMove1 = 700;

        bigBoatMove2 -= 0.2f;
        if (bigBoatMove2 < -700) bigBoatMove2 = 700;

        float step = 1.5f;
        if (humanDir == 1) hUpY += step;
        if (humanDir == 2) hUpY -= step;
        if (humanDir == 3) hUpX -= step;
        if (humanDir == 4) hUpX += step;

        if (wheelRun)
        {
            wheelAngle += 0.4f;
            if (wheelAngle >= 360) wheelAngle -= 360;
        }
    }

    // Abir page animations
    if (currentPage == 2) {
        abir_cloud1_x += 0.2; if (abir_cloud1_x > 600) abir_cloud1_x = -600;
        abir_cloud2_x += 0.4; if (abir_cloud2_x > 600) abir_cloud2_x = -600;
        abir_cloud3_x += 0.6; if (abir_cloud3_x > 600) abir_cloud3_x = -600;
        abir_flag_wave += 0.03;

        for (int i = 0; i < 2; i++) {
            abir_birdX[i] += abir_birdSpeed;
            if (abir_birdX[i] > 520) abir_birdX[i] = -520;
        }

        if (abir_moving_state == 1) {
            if (abir_movingY < -80) abir_movingY += 0.5;
            if (abir_movingX < -80) abir_movingX += 0.5;
        }
        if (abir_moving_state2 == 1) abir_movingY2 -= 0.5;
        if (abir_moving_state3 == 1) abir_movingY3 -= 0.5;

        if (abir_footballDir == 1) {
            abir_footballY += 0.5;
            if (abir_footballY >= -120) abir_footballDir = -1;
        } else {
            abir_footballY -= 0.5;
            if (abir_footballY <= -220) abir_footballDir = 1;
        }
        abir_footballX = -420;

        if (abir_bellRing) {
            if (abir_bellDir) {
                abir_bellAngle += 1.5f;
                if (abir_bellAngle > 15) abir_bellDir = false;
            } else {
                abir_bellAngle -= 1.5f;
                if (abir_bellAngle < -15) abir_bellDir = true;
            }
        } else {
            abir_bellAngle = 0;
        }

        if (abir_wingUp) {
            abir_wingAngle += 0.4f;
            if (abir_wingAngle > 8) abir_wingUp = false;
        } else {
            abir_wingAngle -= 0.4f;
            if (abir_wingAngle < -4) abir_wingUp = true;
        }
    }

    // Labib page animations
    if (currentPage == 3) {
        labib_cloud1_x += 0.2f;
        labib_cloud2_x += 0.4f;
        labib_cloud3_x += 0.6f;
        if (labib_cloud1_x > 600) labib_cloud1_x = -600;
        if (labib_cloud2_x > 600) labib_cloud2_x = -600;
        if (labib_cloud3_x > 600) labib_cloud3_x = -600;

        if (labib_glow_direction == 1) {
            labib_sun_glow += 0.5f;
            if (labib_sun_glow >= 100.0f) labib_glow_direction = 0;
        } else {
            labib_sun_glow -= 0.5f;
            if (labib_sun_glow <= 30.0f) labib_glow_direction = 1;
        }

        if (labib_wing_dir == 1) {
            labib_wing_pos += 0.15f;
            if (labib_wing_pos >= 1.0f) labib_wing_dir = 0;
        } else {
            labib_wing_pos -= 0.15f;
            if (labib_wing_pos <= 0.0f) labib_wing_dir = 1;
        }

        labib_bird1_x += 0.8f;
        labib_bird2_x -= 1.2f;
        labib_bird3_x += 0.5f;

        if (labib_bird1_x > 600)  labib_bird1_x = -600;
        if (labib_bird2_x < -600) labib_bird2_x = 600;
        if (labib_bird3_x > 600)  labib_bird3_x = -600;

        labib_smokeTime += 0.04f;
    }

    if (currentPage == 4) {
        if(sadek_positionc1 > 1000) sadek_positionc1 = -1000.0f;
        sadek_positionc1 += sadek_speedc1;

        if(sadek_positionc2 > 1000) sadek_positionc2 = -1000.0f;
        sadek_positionc2 += sadek_speedc2;

        if(sadek_positionc3 > 1000) sadek_positionc3 = -1000.0f;
        sadek_positionc3 += sadek_speedc3;

        if(sadek_positionc4 > 1000) sadek_positionc4 = -1000.0f;
        sadek_positionc4 += sadek_speedc4;

        if(sadek_positionc5 > 150) sadek_positionc5 = -500.0f;
        sadek_positionc5 += sadek_speedc5;

        sadek_j22 += 0.8f;
        sadek_j33 += 0.8f;
    }

    // Noor page animations
    if (currentPage == 5) {
        // River wave
        if (noor_wavePos > 1000) {
            noor_wavePos = 0;
        }
        noor_wavePos += noor_speed;

        // Cloud
        noor_cloudPos1 += noor_cloudSpeed;
        if (noor_cloudPos1 > 600) {
            noor_cloudPos1 = -600;
        }

        noor_cloudPos2 += noor_cloudSpeed * 0.8f;
        if (noor_cloudPos2 > 600) {
            noor_cloudPos2 = -600;
        }

        // Bird
        noor_birdPos += noor_birdSpeed;
        if (noor_birdPos > 600) {
            noor_birdPos = -350;
        }

        // Boat movement
        noor_boatPos -= noor_boatSpeed;
        if (noor_boatPos < -900) {
            noor_boatPos = 350;
        }

        noor_manMove += 0.02f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void playSound()
{
    if (isSoundMuted) {
        PlaySound(NULL, NULL, 0);
        return;
    }

    if (currentPage == 0 || currentPage == 1) {
        PlaySound("village_festival.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    } else if (currentPage == 2) {
        PlaySound("Abir.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    } else if (currentPage == 3) {
        PlaySound("videoplayback.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    } else if (currentPage == 4) {
        PlaySound("a.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    } else if (currentPage == 5) {
        PlaySound("Noor.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    }
}

// ========================================
// KEYBOARD CONTROLS
// ========================================
void handleKeypress(unsigned char key, int x, int y)
{
    // Global Navigation
    if (key == 13) { // Enter key
        if (currentPage < 5) {
            currentPage++;
            playSound();
        }
    }
    else if (key == 8) { // Backspace
        if (currentPage > 0) {
            currentPage--;
            playSound();
        }
    }

    // Sound controls (from Sadek)
    if (key == 'q' || key == 'Q') {
        isSoundMuted = true;
        playSound();
    } else if (key == 'u' || key == 'U') {
        isSoundMuted = false;
        playSound();
    }

    // Shahariyer page controls
    if (currentPage == 1) {
        switch (key)
        {
            case 'w':
            case 'W': humanDir = 1; break;
            case 's':
            case 'S': humanDir = 2; break;
            case 'a':
            case 'A': humanDir = 3; break;
            case 'd':
            case 'D': humanDir = 4; break;
            case ' ': humanDir = 0; break;
            case 'p':
            case 'P':
                wheelRun = !wheelRun;
                break;
        }
    }
    // Abir page controls
    else if (currentPage == 2) {
        if (key == 'm' || key == 'M') {
            abir_moving_state = 1;
            abir_moving_state2 = 1;
            abir_moving_state3 = 1;
        }
        if (key == 's' || key == 'S') {
            abir_moving_state = 0;
            abir_moving_state2 = 0;
            abir_moving_state3 = 0;
        }
        if (key == 'b' || key == 'B') {
            abir_bellRing = !abir_bellRing;
        }
    }
    // Labib page controls
    else if (currentPage == 3) {
        float khunti_center = 100.0f + labib_woman_x;
        if (key == 'r' || key == 'R') {
            if ((khunti_center + 5.0f) <= labib_khunti_right_limit) labib_woman_x += 5.0f;
        } else if (key == 'l' || key == 'L') {
            if ((khunti_center - 5.0f) >= labib_khunti_left_limit) labib_woman_x -= 5.0f;
        }
    }
    // Noor page controls
    else if (currentPage == 5) {
        if (key == '+') {
            if (noor_boatSpeed < 5.0f) {
                noor_boatSpeed += 0.2f;
            }
        } else if (key == '-') {
            if (noor_boatSpeed > 0.2f) {
                noor_boatSpeed -= 0.2f;
            }
        }
        if (key == 'n' || key == 'N') {
            noor_isNight = !noor_isNight;
        }
        if (key == 'l' || key == 'L') {
            noor_lightOn = !noor_lightOn;
        }
        if (key == 'r' || key == 'R') {
            noor_isRaining = true;
        }
        if (key == 's' || key == 'S') {
            noor_isRaining = false;
        }
    }
    glutPostRedisplay();
}

// ========================================
// NAVIGATION (ARROW KEYS)
// ========================================
void specialKeys(int key, int x, int y) {
    // Page navigation (Right arrow for next, Left arrow for previous)
    if (key == GLUT_KEY_RIGHT) {
        if (currentPage < 5) {
            currentPage++;
            playSound();
        }
    } else if (key == GLUT_KEY_LEFT) {
        if (currentPage > 0) {
            currentPage--;
            playSound();
        }
    }

    // Character movement (Up/Down arrows always handle movement)
    if (currentPage == 1) {
        if (key == GLUT_KEY_UP) {
            humanDir = 1;
        } else if (key == GLUT_KEY_DOWN) {
            humanDir = 2;
        }
    }
    // Noor page special controls
    else if (currentPage == 5) {
        if (key == GLUT_KEY_UP) {
            noor_speed += 0.02f;
        } else if (key == GLUT_KEY_DOWN) {
            if (noor_speed > 0.01f) {
                noor_speed -= 0.02f;
            }
        }
    }

    glutPostRedisplay();
}

// ========================================
// MAIN FUNCTION
// ========================================
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1100, 700);
    glutInitWindowPosition(150, 60);
    glutCreateWindow("Village Scene Project - Multi-Page");

    cover_init();

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutKeyboardFunc(handleKeypress);
    glutSpecialFunc(specialKeys);

    playSound();
    glutMainLoop();
    return 0;
}
