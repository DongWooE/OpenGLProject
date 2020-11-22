#include <gl/glut.h>
#include <gl/glu.h>
#include <gl/gl.h>

GLUquadricObj* qobj = gluNewQuadric();

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


void MyDisplay()
{
    glViewport(50, 50, 500, 500); 

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glPushMatrix();
    glTranslatef(0, -1, 0);
    glRotatef(90.0, 1.0, 0.0, 0.0); //90도만큼 x축으로 회전
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    gluCylinder(qobj, 0.5, 0.5, 0.8, 3, 3);//네 번째 parameter가 height
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -1, 0);
    glRotatef(270, 1.0, 0.0, 0.0); //90도만큼 x축으로 회전
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    gluCylinder(qobj, 1.0, 0.0, 2.0, 20, 8);
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
    
    /*다른 면 그리는 것 추가해야 함(왜 안되는지..)
    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex3f(-0.1f, -0.1f, -0.1f);
    glVertex3f(-0.1f, -0.1f, 0.1f);
    glVertex3f(0.1f, -0.1f, 0.1f);
    glVertex3f(0.1f, -0.1f, -0.1f);
    glEnd();
    glPopMatrix();
    */

    glutSwapBuffers();

    glFlush();
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
    glutReshapeFunc(Reshape);
    glutMainLoop();
    return 0;
}