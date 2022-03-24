#ifndef MYGL_H
#define MYGL_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QObject>

#include <vector>
#include "Sphere.h"
#include <QMatrix4x4>
    //Sphere sphere2(1.0f, 36, 18);

class mygl : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    Sphere sphere2;
    mygl(QWidget *parent = nullptr);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
private:

    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;
    unsigned int VBO, VAO, EBO;
    //std::vector <float> vertices;
    //std::vector <unsigned int> indices;
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

    void compilVertexShaderGL(unsigned int &vertexS, const char *vertexSS);
    void compilFragmentShaderGL(unsigned int &fragmentS, const char *fragmentSS);
    void compilShaderProgramGL(unsigned int &shaderP, unsigned int &vertexS, unsigned int &fragmentS);
    GLint viewport[4];
    GLfloat faceColor[4];
    QMatrix4x4 mat;
    //------------------------


};

#endif // MYGL_H
