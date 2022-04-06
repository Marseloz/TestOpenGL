#ifndef MYGL_H
#define MYGL_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QObject>
#include <QTimer>
//#include "shaderio.h"

#include <vector>
#include "Sphere.h"

    //Sphere sphere2(1.0f, 36, 18);

class mygl : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    Sphere sphere2;
    mygl(QWidget *parent = nullptr);
    void drawAxis();
    void setX(float n);
    void setY(float n);
    void setZ(float n);
    void setSpeedRotation(float n);
    void setColorLine(float r, float g, float b);
    void setColorPolygons(float r, float g, float b);
    void setView(int n);
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
private:
    std::vector <float> lineColor, polyColor;
    float buffR, vectR, X0, Y0, Z0;
    int viewTrigger;
    float *colorView;
    QTimer tmr;
public slots:
    void changeZ();

};

#endif // MYGL_H
