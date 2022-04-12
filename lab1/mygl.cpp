#include "mygl.h"

#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QDebug>
#include "glm/mat4x4.hpp"
#include <QColor>
#include "shaderio.h"


float vertices[] = {
     0.f,  0.f, 0.f,
     0.5f, 0.f, 0.f,
     0.f,  0.f, 0.f,
     0.f, 0.5f, 0.f,
     0.f,  0.f, 0.f,
     0.f,  0.f, 0.5f
};
unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};
//unsigned int VBO, VAO, EBO;
//float z;
mygl::mygl(QWidget *parent): QOpenGLWidget{parent}, sphere2(1.0f, 20, 20, false)
{
    buffR=vectR=X0=Y0=Z0=0;
    viewTrigger = 0;
    lineColor = {1, 1, 1, 0};
    polyColor = {1, 0, 1};
    connect(&tmr, SIGNAL(timeout()), this, SLOT(changeZ()));
    tmr.start(20);
}

void mygl::drawAxis()
{
    glDisable(GL_LIGHTING);
    glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, &vertices);
        glColor3d(1,0,0);
        glDrawArrays(GL_LINES, 0, 2);
        glColor3d(0,1,0);
        glDrawArrays(GL_LINES, 2, 2);
        glColor3d(0,0,1);
        glDrawArrays(GL_LINES, 4, 2);
    glDisableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_LIGHTING);
}

void mygl::setX(float n)
{
    X0=n;
}

void mygl::setY(float n)
{
    Y0=n;
}

void mygl::setZ(float n)
{
    Z0=n;
}

void mygl::setSpeedRotation(float n)
{
    vectR = n;
}

void mygl::setColorLine(float r, float g, float b)
{
    lineColor.clear();
    lineColor = {r,g,b};
}

void mygl::setColorPolygons(float r, float g, float b)
{
    polyColor.clear();
    polyColor = {r,g,b};
}

void mygl::setView(int n)
{
    viewTrigger = n;
}

void mygl::initializeGL()
{
    initializeOpenGLFunctions();

    //shader = new ShaderIO("vert1.vsh", "fragm1.frag");
    //shader = new ShaderIO();
    //shader->setFragmentPath("fragm1.frag");
    //shader->compileSProgram();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//указываем цвет фона

    glEnable(GL_LIGHTING); //включаем для сцены возможность использовать источники света
    glEnable(GL_LIGHT0); //включаем источник света 1
    glEnable(GL_LIGHT1); //включаем источник света 2
    GLfloat	light1_Intensity[4] = {0.3f, 0.3f, 0.3f, 0.3f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_Intensity);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_Intensity);
    glEnable(GL_COLOR_MATERIAL);//включаем отображение изначального цвета объектов

    float v[] = {1., 1., 1., 1.};
    glMaterialfv(GL_FRONT, GL_SPECULAR, v);//включение блика
    glMateriali(GL_FRONT, GL_SHININESS, 16);//настройка блика

    glEnable(GL_NORMALIZE);//выравнивание нормалей
}

void ChangeSize(GLsizei width, GLsizei height){
    int side = qMin(width, height);

    float length = 1;
    float zLength = 500;


    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST); //включение перекрытия полигонов в зависимости от расстояния до камеры

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    if (width <= height){
        glFrustum(-length, length, -length*height/width, length*height/width, 1, length+zLength);
    }
    else{
        glFrustum(-length*width/height, length*width/height, -length, length, 1, length+zLength);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mygl::resizeGL(int width, int height)
{
    ChangeSize(width, height);
    qDebug()<<"START";
}

void mygl::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        float light0Pos[] = {-2, 2, 1}; //позиция первого источника
        float light1Pos[] = {-2, 2, -1.5}; //позиция первого источника
        glTranslatef(0, 0, -2);
        glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
        glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);

        glPushMatrix();
            glColor3d(polyColor[0], polyColor[1], polyColor[2]);
            glRotatef(buffR, X0, Y0, Z0);
            if(viewTrigger == 0) sphere2.drawLines(lineColor.data());
            else if(viewTrigger == 1) sphere2.drawWithLines(lineColor.data());
            else sphere2.draw();
            drawAxis();
        glPopMatrix();
    glPopMatrix();
}

void mygl::changeZ()
{
    buffR += vectR;
    update();

}


