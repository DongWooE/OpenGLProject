#include <gl/glut.h>
#include <gl/glu.h>
#include <gl/gl.h>
#include<math.h>
#define Pi 3.1415

GLUquadricObj* qobj = gluNewQuadric();
static int view = 0, viewValue = 0;  //3가지 시점으로 볼 수 있게 해주는 변수
GLfloat snowPos[2] = { 0, };
GLint snowAngle = 0;

void Reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.5, 2.5, -2.5 * (GLfloat)h / (GLfloat)w, 2.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void MyInit(void) {
    GLfloat mat_ambient[] = { 0.0, 0.0, 0.0, 1.0 }; //주변광
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 }; //반사광
    GLfloat mat_shininess[] = { 50.0 }; //선명도
    GLfloat light_position[] = { 0.3, 0.3, 0.5, 0.0 }; //조명 위치
    GLfloat model_ambient[] = { 0.6, 0.4, 0.2, 1.0 };
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

void drawLines() {
    
    //트리 주위를 감는 선 그리기
    GLfloat Size[2], Angle;
    glColor3f(1.0, 0.0, 0.0);
    glGetFloatv(GL_POINT_SIZE_RANGE, Size);
    glPointSize(Size[0] * 10);
    glBegin(GL_POINTS);
    for (Angle = 0.0; Angle <= 2.0 * Pi; Angle += Pi / 20.0) {
        glVertex3f(0.5 * cos(Angle), 1.0-Angle, 0.5 * sin(Angle));
        
    }
    glEnd();



}

void drawSnowman() {

    glTranslatef(snowPos[0], -2.5, snowPos[1]);
    glRotatef(snowAngle, 0, 1, 0);
    glPushMatrix();

    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glutWireSphere(0.2, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0.19, 0);
    glRotatef(90, 1, 0, 0);
    glutWireSphere(0.18, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1/sqrt(20), 1/sqrt(20), 0);
    glRotatef(-45, 0, 0, 1);
    glScalef(1, 3, 1);
    glutWireCube(0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1 / sqrt(20), 1 / sqrt(20), 0);
    glRotatef(45, 0, 0, 1);
    glScalef(1, 3, 1);
    glutWireCube(0.1);
    glPopMatrix();

    glPopMatrix();
}
void MyDisplay()
{
    glViewport(50, 50, 500, 500);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    gluQuadricDrawStyle(qobj, GLU_LINE);

    glRotatef(viewValue, 1, 1, 0);
    glPushMatrix();
    glTranslatef(0, -1, 0);
    glRotatef(90.0, 1.0, 0.0, 0.0); //90도만큼 x축으로 회전
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    gluCylinder(qobj, 0.3, 0.3, 0.8, 10, 8);//네 번째 parameter가 height
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -1, 0);
    glRotatef(270, 1.0, 0.0, 0.0); //90도만큼 x축으로 회전
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    gluCylinder(qobj, 1.0, 0.0, 2.0, 12, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -0.5, 0);
    glRotatef(270, 0.5, 0.0, 0.0); //90도만큼 x축으로 회전
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    gluCylinder(qobj, 0.9, 0.0, 2.0, 11.5, 8);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, 0, 0);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    
    glPushMatrix();
    glRotatef(270, 0.5, 0.0, 0.0); //90도만큼 x축으로 회전
    gluCylinder(qobj, 0.8, 0.0, 2.0, 11, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 2.0, 0);
    glRotatef(270, 1, 0.0, 0.0); //90도만큼 x축으로 회전
    glutWireSphere(0.2, 20, 20);
    glPopMatrix();
    
    glPopMatrix();

    /*뒷면 그리는 부분*/
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-2.0f, -2.0f, -1.0f);
    glVertex3f(2.0f, -2.0f, -1.0f);
    glVertex3f(2.0f, 2.0f, -1.0f);
    glVertex3f(-2.0f, 2.0f, -1.0f);
    glEnd();
    glPopMatrix();

    //다른 면 그리는 것 추가해야 함(왜 안되는지..)
    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex3f(-0.1f, -0.1f, -0.1f);
    glVertex3f(-0.1f, -0.1f, 0.1f);
    glVertex3f(0.1f, -0.1f, 0.1f);
    glVertex3f(0.1f, -0.1f, -0.1f);
    glEnd();
    glPopMatrix();
    

    drawLines();
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
    case 'a' :
        snowPos[0] = snowPos[0] - 0.1f;
        break;
    case 'd' :
        snowPos[0] = snowPos[0] + 0.1f;
        break;
    case 'w':
        snowPos[1] = snowPos[1] - 0.1f;
        break;
    case 's':
        snowPos[1] = snowPos[1] + 0.1f;
        break;
    case 'q':
        snowAngle =(snowAngle + 1)%360;
        break;
    case 'e':
        snowAngle = (snowAngle - 1) % 360;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(300, 200);
    glutCreateWindow("Brown Cylinder");
    MyInit();
    glutDisplayFunc(MyDisplay);
    glutKeyboardFunc(MyKeyboard);
    glutReshapeFunc(Reshape);
    glutMainLoop();
    return 0;
}