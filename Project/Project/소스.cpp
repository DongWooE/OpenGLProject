#include <iostream>  
#include <gl/glut.h>
#include <gl/glu.h>
#include <gl/gl.h>
#include<math.h>
#include<stdlib.h>
#define Pi 3.1415

bool mouseClick = true;

int window_width = 600;
int window_height = 600;
GLfloat move_y = 0.0;
GLfloat move_z = 0.0;
GLfloat const_att = 2.5;

const GLfloat red[] = { 0.8f, 0.0, 0.0, 1.0 };
const GLfloat blue[] = { 0.0, 0.2f, 1.0, 1.0 };
const GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat green[] = { 0.0, 0.4, 0.0, 1.0 };
const GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };
const GLfloat brown[] = { 0.545, 0.2705, 0.0745, 1.0 };
const GLfloat polished[] = { 100.0 };
const GLfloat dull[] = { 0.0 };
const GLfloat light_pos[] = { 3,10,0,1 };//x축의 양의 방향으로 3만큼 간 곳에 light 설치

GLfloat sphereColor[] = { 1.0, 1.0, 0.0, 1.0 }; // 공 색, 초기 값은 노란 색
GLfloat lookX = 0.0, lookY = 0.0, lookZ = 0.0;

GLfloat LightPosition[] = { 0.0, 0.0, 1.5, 1.0 };
GLUquadricObj* qobj = gluNewQuadric();
static int view = 0, viewValue = 0;  //3가지 시점으로 볼 수 있게 해주는 변수
GLfloat snowPos[2] = { 0, };
GLint snowAngle = 0;

void Reshape(int w, int h) {
    glViewport(0, 0, (GLint)w, (GLint)h);
    GLfloat WidthFactor = (GLfloat)w / 600;
    GLfloat HeightFactor = (GLfloat)h / 600;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-2.5 * WidthFactor, 2.5 * WidthFactor, -2.5 * HeightFactor, 2.5 * HeightFactor, -10.0, 10.0);
}

//Menu Callback
void MyMainMenu(int entryID) {
    if (entryID == 1)
        *sphereColor = *red;
    else if (entryID == 2)
        *sphereColor = *yellow;
    else if (entryID == 3)
        exit(0);
    glutPostRedisplay();
}

void MyInit() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glEnable(GL_DEPTH_TEST);

    /*Menu Callback*/
    //
    //
    GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
    glutAddMenuEntry("Change Sphere Color1", 1);
    glutAddMenuEntry("Change Sphere Color2", 2);
    glutAddMenuEntry("Exit", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void drawLines() {
    //트리 주위를 감는 선 그리기
    GLfloat Size[2], Angle;
    glColor3f(1.0, 0.0, 0.0);
    glGetFloatv(GL_POINT_SIZE_RANGE, Size);
    glPointSize(Size[0] * 10);
    glBegin(GL_POINTS);
    for (Angle = 0.0; Angle <= 2.0 * Pi; Angle += Pi / 20.0) {
        glVertex3f(0.5 * cos(Angle), 1.0 - Angle, 0.5 * sin(Angle));
    }
    glEnd();
}

void drawSnowman() {
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
    glTranslatef(snowPos[0], -2.5, snowPos[1]);
    glRotatef(snowAngle, 0, 1, 0);
    glPushMatrix();

    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glutSolidSphere(0.2, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0.19, 0);
    glRotatef(90, 1, 0, 0);
    glutSolidSphere(0.18, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown);
    glTranslatef(1 / sqrt(20), 1 / sqrt(20), 0);
    glRotatef(-45, 0, 0, 1);
    glScalef(1, 3, 1);
    glutSolidCube(0.1);
    glPopMatrix();

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown);
    glTranslatef(-1 / sqrt(20), 1 / sqrt(20), 0);
    glRotatef(45, 0, 0, 1);
    glScalef(1, 3, 1);
    glutSolidCube(0.1);
    glPopMatrix();

    glPopMatrix();
}

void draw_balls() {

    GLfloat angle;
    glPushMatrix();
    glTranslatef((0.8 + 0.1 * i) * cos(angle), 1.7 - 0.4 * i, (0.8 + i) * sin(angle));
    glutSolidSphere(0.1, 20, 20);
    glPopMatrix();


}

void MyDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glShadeModel(GL_FLAT);

    glLoadIdentity();

    gluLookAt(lookX, lookY, lookZ, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0); // 위치, 초점, 기울임

    //gluQuadricDrawStyle(qobj, GLU_LINE);

    /*제일 아래 갈색 나무 그리는 부분*/
    glRotatef(viewValue, 1, 1, 0);
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
    glTranslatef(0, -1, 0);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown);
    glRotatef(90.0, 1.0, 0.0, 0.0); //90도만큼 x축으로 회전
    gluCylinder(qobj, 0.3, 0.3, 0.8, 10, 8);//네 번째 parameter가 height
    glEnable(GL_LIGHTING);//다시 Enable Light
    //glLightfv(GL_LIGHT0, GL_POSITION, light0_ambient);
    glPopMatrix();

    /*1층 초록색 나무 부분*/
    glPushMatrix();
    glTranslatef(0, -1, 0);
    glRotatef(270, 1.0, 0.0, 0.0); //90도만큼 x축으로 회전
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, black);
    //glMaterialfv(GL_FRONT, GL_SHININESS, white);
    gluCylinder(qobj, 1.0, 0.0, 2.0, 12, 8);
    glPopMatrix();

    /*2층 초록색 나무 부분*/
    glPushMatrix();
    glTranslatef(0, -0.5, 0);
    glRotatef(270, 0.5, 0.0, 0.0); //90도만큼 x축으로 회전
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
    gluCylinder(qobj, 0.9, 0.0, 2.0, 11.5, 8);
    glPopMatrix();

    /*3층 초록색 나무 부분*/
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glPushMatrix();
    glRotatef(270, 0.5, 0.0, 0.0); //90도만큼 x축으로 회전
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
    gluCylinder(qobj, 0.8, 0.0, 2.0, 11, 8);
    glPopMatrix();



    /*맨 위에 밝은 Sphere*/
    glPushMatrix();
    glTranslatef(0, 2.0, 0);
    glShadeModel(GL_SMOOTH);
    glColor3f(1.0, 1.0, 0);
    glRotatef(270, 1, 0.0, 0.0); //90도만큼 x축으로 회전
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sphereColor);
    glutSolidSphere(0.2, 20, 20);
    //glEnable(GL_LIGHTING);
    glPopMatrix();

    glPopMatrix();

    /*뒷면 그리는 부분
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-2.0f, -2.0f, -1.0f);
    glVertex3f(2.0f, -2.0f, -1.0f);
    glVertex3f(2.0f, 2.0f, -1.0f);
    glVertex3f(-2.0f, 2.0f, -1.0f);
    glEnd();
    glPopMatrix();
    */

    //drawLines();

    drawSnowman();

    glutSwapBuffers();
}

void MyKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'v':
    case 'V':  //view를 3으로 나눈 나머지로 설정하여 클릭 시 3가지 시점으로 변경하도록 설정
        view = (view + 1) % 3;
        if (view == 0)viewValue = 0;
        else if (view == 1) viewValue = 30;
        else viewValue = 60;
        break;
    case 'a':
        snowPos[0] = snowPos[0] - 0.1f;
        break;
    case 'd':
        snowPos[0] = snowPos[0] + 0.1f;
        break;
    case 'w':
        snowPos[1] = snowPos[1] - 0.1f;
        break;
    case 's':
        snowPos[1] = snowPos[1] + 0.1f;
        break;
    case 'q':
        snowAngle = (snowAngle + 1) % 360;
        break;
    case 'e':
        snowAngle = (snowAngle - 1) % 360;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void goUpIdle() {
    lookY -= 0.0001;
    glutPostRedisplay();
}

void stopIdle() {
    lookY = 0;
    glutPostRedisplay();
}

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
    if (Button == GLUT_LEFT_BUTTON) {
        if (mouseClick == true) {
            mouseClick = false;
            glutIdleFunc(goUpIdle);
        }
        else if (mouseClick == false) {
            mouseClick = true;
            glutIdleFunc(stopIdle);
        }
    }
}


void InitVisibility() {
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW); // 후면 제거
    glCullFace(GL_BACK); // 후면 제거 작업 수행
    glEnable(GL_DEPTH_TEST);
}


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(300, 200);
    glutCreateWindow("X-Mas Tree");
    MyInit();
    InitVisibility(); // 후면제거
    glutDisplayFunc(MyDisplay);
    glutKeyboardFunc(MyKeyboard);
    glutMouseFunc(MyMouseClick);
    glutReshapeFunc(Reshape);
    glutMainLoop();

    return 0;
}