#include "mygl.h"

#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QDebug>

#include <QColor>

void qMultMatrix(const QMatrix4x4 &mat)
{
    if (sizeof(qreal) == sizeof(GLfloat))
        glMultMatrixf((GLfloat*)mat.constData());
#ifndef QT_OPENGL_ES
    else if (sizeof(qreal) == sizeof(GLdouble))
        glMultMatrixd((GLdouble*)mat.constData());
#endif
    else
    {
        GLfloat fmat[16];
        GLfloat const *r = mat.constData();
        for (int i = 0; i < 16; ++i)
            fmat[i] = r[i];
        glMultMatrixf(fmat);
    }
}

mygl::mygl(QWidget *parent): QOpenGLWidget{parent}, sphere2(1.0f, 3, 40)
{
}

void mygl::initializeGL()
{

    initializeOpenGLFunctions();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_MULTISAMPLE);

    compilVertexShaderGL(vertexShader, vertexShaderSource);
    // fragment shader
    compilFragmentShaderGL(fragmentShader, fragmentShaderSource);
    // link shaders
    compilShaderProgramGL(shaderProgram, vertexShader, fragmentShader);

    glUseProgram(shaderProgram);
    glGetUniformLocation(shaderProgram, "pMatrix");
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

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ChangeSize(GLsizei width, GLsizei height){
    int side = qMin(width, height);

    GLsizei nRange = 100.0f;

    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//#ifdef QT_OPENGL_ES_1
//    glOrthof(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
//#else
//    glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
//#endif
    if (width <= height){
        glFrustum(-nRange, nRange, -nRange*height/width, nRange*height/width, -nRange, nRange);}
    else{
        glFrustum(-nRange*height/width, nRange*height/width, -nRange, nRange, -nRange, nRange);}
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mygl::resizeGL(int width, int height)
{
    ChangeSize(width, height);
}

void mygl::paintGL()
{
    //qDebug()<<this->width()<<"|"<<this->height();
    ChangeSize(this->width(), this->height());
    // draw our first triangle
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, faceColor);
    glPopMatrix();
    glDrawElements(GL_TRIANGLES, sphere2.getIndexCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
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


