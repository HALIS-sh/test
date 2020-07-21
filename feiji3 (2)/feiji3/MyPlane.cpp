#include "MyPlane.h"

MyPlane::MyPlane(const QGraphicsScene *scene,const string &imageFile,QPoint dir=QPoint(0,0),int life=10,int lan=10):
    Plane(scene,imageFil,dir,life)
{
    this->lan=lan;
}
