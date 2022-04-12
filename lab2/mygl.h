#ifndef MYGL_H
#define MYGL_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QObject>
#include <QTimer>
//#include "shaderio.h"

#include <vector>
//#include "Sphere.h"
#include "vobj.h"

    //Sphere sphere2(1.0f, 36, 18);

class mygl : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    //Sphere sphere2;
    vObj latter_1;
    vObj latter_2;
    vObj latter_3;
    mygl(QWidget *parent = nullptr);
    void setWorldScale(float n);
    void setWorldPositionX(float n);
    void setWorldPositionY(float n);
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
private:
    std::vector <float> lineColor, polyColor;
    float worldScale, world_X, world_Y;
    //int viewTrigger;
    //float *colorView;
    QTimer tmr;
public slots:
    void changeZ();

};

#endif // MYGL_H
