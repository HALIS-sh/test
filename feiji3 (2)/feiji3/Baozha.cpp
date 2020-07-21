#include "Baozha.h"

Baozha::Baozha()
{

}

Baozha::Baozha(QGraphicsPixmapItem *p)
{
    this->p=p;
}

void Baozha::run()
{
    QPixmap *tu=new QPixmap(QString::fromStdString(":/images/explosion.BMP"));

    for(int i=1;i<=8;i++)
    {
        QPixmap tu2=tu->copy(tu->width()/8*(i-1),0,tu->width()/8,tu->height());
        tu2=tu2.scaled(QSize(tu2.width()/2,tu2.height()/2), Qt::KeepAspectRatio);
        p->setPixmap(tu2);
        p->update();
        if(i!=8)Sleep(1000);
    }
}
