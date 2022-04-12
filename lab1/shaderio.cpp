#include "shaderio.h"
#include <QDebug>
#include <QString>


ShaderIO::ShaderIO()
{
    initializeOpenGLFunctions();
}

ShaderIO::ShaderIO(const char *vertexPath, const char *fragmentPath)
{
    initializeOpenGLFunctions();
    if (vertexPath != nullptr){
        setVertexPath(vertexPath);
        //qDebug()<<vertexCode;
    }
    if (fragmentPath != nullptr){
        setFragmentPath(fragmentPath);
        //qDebug()<<fragmentCode;
    }
    compileSProgram();
}

void ShaderIO::setVertexPath(const char *vertexPath)
{
    int success;
    char infoLog[512];

    vertexCode = readCodeFile(vertexPath);

    //qDebug()<<QString(vertexCode);

    vertexID = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexID, 1, &vertexCode, NULL);
    glCompileShader(vertexID);

    glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexID, 512, NULL, infoLog);
        qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog;
    }
}

void ShaderIO::setFragmentPath(const char *fragmentPath)
{
    int success;
    char infoLog[512];

    fragmentCode = readCodeFile(fragmentPath);

    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentID, 1, &fragmentCode, NULL);
    glCompileShader(fragmentID);

    glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentID, 512, NULL, infoLog);
        qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
    }
}

void ShaderIO::compileSProgram()
{
    int success;
    char infoLog[512];

    ID = glCreateProgram();
    if (vertexCode != nullptr){ glAttachShader(ID, vertexID);}
    if (fragmentCode != nullptr){ glAttachShader(ID, fragmentID);}
    glLinkProgram(ID);



    glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(ID, 512, NULL, infoLog);
        qDebug() << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog;
    }

    if (vertexCode != nullptr){ glDeleteShader(vertexID);}
    if (fragmentCode != nullptr){ glDeleteShader(fragmentID);}
}

const char* ShaderIO::readCodeFile(const char *filePath)
{
    QFile file(":/"+QString(filePath)); // создаем объект класса QFile
    if (!file.open(QIODevice::ReadOnly)){ // Проверяем, возможно ли открыть наш файл для чтения
        qDebug()<<"ERROR: File no open!!!";
        return nullptr;
    }
    dataBuff = file.readAll(); //считываем все данные с файла в объект data
    return dataBuff.constData();
}

void ShaderIO::use()
{
    glUseProgram(ID);
}

void ShaderIO::noUse()
{
    glUseProgram(0);
}
