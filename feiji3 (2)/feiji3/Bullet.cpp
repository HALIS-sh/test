#include "Bullet.h"
Bullet::Bullet(QGraphicsScene *scene,const string &imageFile,QPointF pos,QPointF dir,int might):
    Object(scene,imageFile,pos,dir)
{
    this->might=might;
}

bool Bullet::zai()
{
    if (pos().x()<0 || pos().x()>scene->width()+80 || pos().y()<0 || pos().y()>scene->height()+80)return false;
    else return true;
}
