#include "mygl.h"

#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QDebug>
#include <QColor>

std::vector <float> vertexLetter_2 = {
    0.f, 0.f,
    0.f, 1.f,
    0.25f, 1.f,
    0.5f, 0.5f,
    0.75f, 1.f,
    1.f, 1.f,
    1.f, 0.f,
    0.75f, 0.f,
    0.75f, 0.5f,
    0.58f, 0.25f,
    0.41f, 0.25f,
    0.25f, 0.5f,
    0.25f, 0.f
};
std::vector <float> vertexLetter_3 = {
    0.f, 0.f,
    0.f, 1.f,
    0.25f, 1.f,
    0.25f, 0.63f,
    0.75f, 1.f,
    1.f, 1.f,
    0.5f, 0.5f,
    1.f, 0.f,
    0.75f, 0.f,
    0.25f, 0.37f,
    0.25f, 0.f
};
std::vector <std::vector <float>*> vertexLetter_1 = {new std::vector <float>{
    0.f, 0.f,
    0.f, 1.f,
    0.83f, 1.f,
    0.83f, 0.f
},
new std::vector <float>{
    0.25f, 0.25f,
    0.25f, 0.75f,
    0.58f, 0.75f,
    0.58f, 0.25f
}};

mygl::mygl(QWidget *parent): QOpenGLWidget{parent}//, sphere2(1.0f, 20, 20, false)
{
    worldScale = 1;
    world_X = 0;
    world_Y = 0;
    connect(&tmr, SIGNAL(timeout()), this, SLOT(changeZ()));
    tmr.start(20);
}

void mygl::setWorldScale(float n)
{
    worldScale = n;
}

void mygl::setWorldPositionX(float n)
{
    world_X = n;
}

void mygl::setWorldPositionY(float n)
{
    world_Y = n;
}

void mygl::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//указываем цвет фона
    glLineWidth(2);
    latter_1.importVertex(vertexLetter_1);
    latter_1.setPositionX(-1);
    latter_2.importVertex(&vertexLetter_2);
    latter_3.importVertex(&vertexLetter_3);
    latter_3.setPositionX(1.1);
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
        glOrtho(-length, length, -length*height/width, length*height/width, -zLength, zLength);
    }
    else{
        glOrtho(-length*width/height, length*width/height, -length, length, -zLength, zLength);
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
        glScalef(worldScale, worldScale, 1);
        glTranslatef(world_X,world_Y,0);
        latter_1.drawLines();
        latter_2.drawLines();
        latter_3.drawLines();
    glPopMatrix();
}

void mygl::changeZ()
{
    update();

}


