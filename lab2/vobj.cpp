#include "vobj.h"
#include <GL/gl.h>
#include <QDebug>
#include <math.h>
#include <QRandomGenerator>
#include <QTime>




vObj::vObj()
{
    QRandomGenerator(QTime(0,0,0).secsTo(QTime::currentTime()));
    vScale = 1;
    vWH[0] = 0;
    vWH[1] = 0;
    vCenterPoint[0] = 0;
    vCenterPoint[1] = 0;
    vPosition[0] = 0;
    vPosition[1] = 0;
    _trigg = 0;
}

void vObj::importVertex(std::vector <std::vector <float>*> n)
{
    vertexBuff = n;
}

void vObj::importVertex(std::vector <float> *n){
    vertexBuff.push_back(n);
}

void calcuateCenterPoint(std::vector <std::vector <float>*> points, float* centrPoint){
    float minX = 0, maxX = 0, minY = 0, maxY = 0;
    bool triggMinX = 0, triggMaxX = 0, triggMinY = 0, triggMaxY = 0;
      for(size_t k = 0; k < points.size(); k++){
        for(size_t i = 0; i < points[k]->size(); i++){
            if(!((i+1)%2)){ //если чётное (Y)
                if(((*points[k])[i] < minY)||!triggMinY) {
                    minY = (*points[k])[i];
                    triggMinY = true;
                }
                if(((*points[k])[i] > maxY)||!triggMaxY) {
                    maxY = (*points[k])[i];
                    triggMaxY = true;
                }
            }
            else{ //если нет (X)
                if(((*points[k])[i] < minX)||!triggMinX) {
                    minX = (*points[k])[i];
                    triggMinX = true;
                }
                if(((*points[k])[i] > maxX)||!triggMaxX) {
                    maxX = (*points[k])[i];
                    triggMaxX = true;
                }
            }
        }
    }
    centrPoint[0] = (abs(maxX-minX)/2)+minX;
    centrPoint[1] = (abs(maxY-minY)/2)+minY;
}

void vObj::drawLines()
{
    if(!vertexBuff.empty()){
        if(vertexRezult.size()!=vertexBuff.size()){
            vertexRezult.clear();
            for(size_t i = 0; i < vertexBuff.size(); i++) {
                vertexRezult.push_back(*vertexBuff[i]);
            }
        } else {
            for(size_t i = 0; i < vertexBuff.size(); i++) {
                vertexRezult[i] = *vertexBuff[i];
            }
        }
        calcuateCenterPoint(vertexBuff, vCenterPoint);
        for(size_t k = 0; k < vertexBuff.size(); k++){
            for(size_t i = 0; i < vertexBuff[k]->size(); i++){
                if(!((i+1)%2)){ //если чётное (Y)
                    vertexRezult[k][i] = ((*vertexBuff[k])[i]-vCenterPoint[1])*(vScale+vWH[1])+vCenterPoint[1]
                    +vPosition[1];
                }
                else{ //если нет (X)
                    vertexRezult[k][i] = ((*vertexBuff[k])[i]-vCenterPoint[0])*(vScale+vWH[0])+vCenterPoint[0]
                    +vPosition[0];
                }
                //qDebug()<<vertexRezult[i]<<" | "<<(*vertexBuff)[i];

            }
        }

            glPushMatrix();
                glEnableClientState(GL_VERTEX_ARRAY);
                    glColor3f((float)(qrand()%100)/100, (float)(qrand()%100)/100, (float)(qrand()%100)/100);
                    glTranslatef(-vCenterPoint[0],-vCenterPoint[1],0);
                    for(size_t i = 0; i < vertexRezult.size(); i++){
                        glVertexPointer(2, GL_FLOAT, 0, vertexRezult[i].data());
                        if(!_trigg){
                            glDrawArrays(GL_LINE_LOOP, 0, vertexRezult[i].size()/2);
                        }
                        else{
                            glDrawArrays(GL_LINE_STRIP, 0, vertexRezult[i].size()/2);
                        }
                    }
                glDisableClientState(GL_VERTEX_ARRAY);
            glPopMatrix();

    }
}

void vObj::setScale(float n)
{
    vScale = n;
}

void vObj::setWidth(float n)
{
    vWH[0] = n;
}

void vObj::setHeight(float n)
{
    vWH[1] = n;
}

void vObj::setPositionX(float n)
{
    vPosition[0] = n;
}

void vObj::setPositionY(float n)
{
    vPosition[1] = n;
}

void vObj::setTrigg(bool n)
{
    _trigg = n;
}
