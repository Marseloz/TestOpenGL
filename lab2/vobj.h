#ifndef VOBJ_H
#define VOBJ_H
#include <vector>

class vObj
{
public:
    vObj();
    void importVertex(std::vector <std::vector <float>*> n);
    void importVertex(std::vector <float> *n);
    void drawLines();
    void setScale(float n); //масштаб
    void setWidth(float n); //ширина
    void setHeight(float n); //высота
    void setPositionX(float n);
    void setPositionY(float n);
    void setTrigg(bool n); // переключение отображения контура

private:
    std::vector <std::vector <float>*> vertexBuff;
    std::vector <std::vector <float>> vertexRezult;
    float vScale;
    float vWH[2];
    float vCenterPoint[2];
    float vPosition[2];
    bool _trigg;
};

#endif // VOBJ_H
