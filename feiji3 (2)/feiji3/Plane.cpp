#include "Plane.h"

Plane::Plane(QGraphicsScene *scene,const string &imageFile,QPointF pos,QPointF dir,int life,int energy,int might):
    Object(scene,imageFile,pos,dir)
{
    this->life=life;
    this->energy=energy;
    this->might=might;
}

///飞机被造成伤害值为shang  飞机死亡返回true
bool Plane::hit(int shang)
{
    life-=shang;
    if(life<=0)return true;
    else return false;
}
