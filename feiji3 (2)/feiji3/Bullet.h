#ifndef BULLET_H
#define BULLET_H

#include <QtWidgets>

#include "Object.h"
#include <utility>
#include <fstream>
#include <iostream>
using namespace std;

class Bullet : public Object
{
public:
    int might;//威力
    Bullet(){}
    Bullet(QGraphicsScene *scene,const string &imageFile,QPointF pos,QPointF dir,int might);
    bool zai();
};
#endif // BULLET_H
