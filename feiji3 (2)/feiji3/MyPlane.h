#ifndef MYPLANE_H
#define MYPLANE_H

#include <allheader.h>
#include <Plane.h>

class MyPlane
{
public:
    int lan;
    MyPlane(){}
    MyPlane(const QGraphicsScene *scene,const string &imageFile,QPoint dir=QPoint(0,0),int life=10,int lan=10);

};

#endif // MYPLANE_H
