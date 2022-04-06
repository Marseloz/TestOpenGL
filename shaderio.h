#ifndef SHADERIO_H
#define SHADERIO_H
#include <QFile>
#include <QOpenGLFunctions_3_3_Core>

class ShaderIO: public QOpenGLFunctions_3_3_Core
{
public:
    ShaderIO();
    ShaderIO(const char* vertexPath, const char* fragmentPath);
    void setVertexPath(const char* vertexPath);
    void setFragmentPath(const char* fragmentPath);
    void compileSProgram();
    const char* readCodeFile(const char* filePath);
    unsigned int getID() { return ID; };
    void use();
    void noUse();
private:
    unsigned int ID, vertexID, fragmentID;
    const char* vertexCode = nullptr;
    const char* fragmentCode = nullptr;
    QByteArray dataBuff;
};

#endif // SHADERIO_H
