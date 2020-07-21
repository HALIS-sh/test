#ifndef OBJECT_H
#define OBJECT_H

#include <QtWidgets>
#include <string>
#include <QUrl>
#include <QMediaPlayer>
#include <QMediaPlaylist>

using namespace std;

///setPos(pos().x() + dx, pos().y() + dy);
class Object : public QGraphicsPixmapItem
{
public:
    QGraphicsScene *scene;
    QPointF dir;
    Object(){}
    Object(QGraphicsScene *scene,const string &imageFile,QPointF pos,QPointF dir);
    void add();
    void out();
    virtual bool zai();
    QPointF move();
};

#endif // WIDGET_H
