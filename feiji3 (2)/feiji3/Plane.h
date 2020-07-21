#ifndef PLANE_H
#define PLANE_H

#include "Object.h"
#include <QtWidgets>
#include <cstring>
#include <vector>
using namespace std;

class Plane: public Object
{
public:
    int life,energy,might;
    Plane(){}
    Plane(QGraphicsScene *scene,const string &imageFile,QPointF pos,QPointF dir,int life,int energy,int might);
    bool hit(int shang);
};

#endif // PLANE_H
