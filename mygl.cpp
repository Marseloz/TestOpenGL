#include "mygl.h"

#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QDebug>
#include <QColor>

mygl::mygl(QWidget *parent): QOpenGLWidget{parent}, sphere2(1.0f, 5, 5)
{
}

void mygl::initializeGL()
{

    qDebug() << "initializeOpenGLFunctions:" << initializeOpenGLFunctions();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    compilVertexShaderGL(vertexShader, vertexShaderSource);
    // fragment shader
    compilFragmentShaderGL(fragmentShader, fragmentShaderSource);
    // link shaders
    qDebug()<<shaderProgram << "-";
    compilShaderProgramGL(shaderProgram, vertexShader, fragmentShader);
    qDebug()<<shaderProgram << "--";
    //glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sphere2.getVertexSize(), sphere2.getVertices(), GL_DYNAMIC_DRAW);
    qDebug() << sphere2.getVertexCount() << sphere2.getTriangleCount() << sphere2.getIndexCount();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphere2.getIndexSize(), sphere2.getIndices(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(1);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);

    glUseProgram(shaderProgram);
}

void ChangeSize(GLsizei width, GLsizei height){
    int side = qMin(width, height);

    GLsizei nRange = 100.0f;

    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//#ifdef QT_OPENGL_ES_1
    //glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
//#else
//    glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
//#endif
    if (width <= height){
        glFrustum(-nRange, nRange, -nRange*height/width, nRange*height/width, nRange, nRange*3);
    }
    else{
        glFrustum(-nRange*height/width, nRange*height/width, -nRange, nRange, nRange, nRange*3);
    }
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
}

void mygl::resizeGL(int width, int height)
{
    ChangeSize(width, height);
}

void mygl::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);
    // draw our first triangle


    ChangeSize(this->width(), this->height());
    //glLoadIdentity();
    //qDebug()<<this->width()<<"|"<<this->height();
    //glPushMatrix();
    //GLdouble translate[16] = {1,0,0,0,0,1,0,0,0,0,1,0,1,0,0,1};
    //glMultMatrixd(translate);
    glTranslated(4, 4, -300);
    glRotated(30,1,0,0);
     // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    //glPopMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sphere2.getIndexCount(), GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, sphere2.getIndexCount());

    glFlush();
}

void mygl::compilVertexShaderGL(unsigned int &vertexS, const char *vertexSS)
{
    int success;
    char infoLog[512];
    vertexS = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexS, 1, &vertexSS, NULL);
    glCompileShader(vertexS);
    // check for shader compile errors

    glGetShaderiv(vertexS, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexS, 512, NULL, infoLog);
        qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog;
    }
}

void mygl::compilFragmentShaderGL(unsigned int &fragmentS, const char *fragmentSS)
{
    int success;
    char infoLog[512];
    fragmentS = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentS, 1, &fragmentSS, NULL);
    glCompileShader(fragmentS);
    // check for shader compile errors
    glGetShaderiv(fragmentS, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentS, 512, NULL, infoLog);
        qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
    }
}

void mygl::compilShaderProgramGL(unsigned int &shaderP, unsigned int &vertexS, unsigned int &fragmentS)
{
    int success;
    char infoLog[512];
    shaderP = glCreateProgram();
    glAttachShader(shaderP, vertexS);
    glAttachShader(shaderP, fragmentS);
    glLinkProgram(shaderP);
    // check for linking errors
    glGetProgramiv(shaderP, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderP, 512, NULL, infoLog);
        qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog;
    }
}


