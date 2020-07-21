#include "Object.h"


Object::Object(QGraphicsScene *scene,const string &imageFile,QPointF pos,QPointF dir):
    QGraphicsPixmapItem(QPixmap(QString::fromStdString(imageFile)))
{
    this->scene=scene;
    this->dir=dir;
    this->setPos(pos);
    scene->addItem(this);
    update();
    this->setZValue(4);
}

void Object::add()
{
    if(!scene->items().contains(this))
    {
        scene->addItem(this);
        update();
    }
}

void Object::out()
{
    if(scene->items().contains(this))
    {
        scene->removeItem(this);
        update();
    }
}

///判断物体位置在不在场景内
bool Object::zai()
{
    if (pos().x()<0 || pos().x()>scene->width() || pos().y()<0 || pos().y()>scene->height())return false;
    else return true;
}

QPointF Object::move()
{
    setPos(pos()+dir);
    update();
    return pos();
}
