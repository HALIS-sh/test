#ifndef BAOZHA_H
#define BAOZHA_H

#include <QtWidgets>
#include <string>
#include <QUrl>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QThread>

class Baozha:public QThread
{
protected:
    void run();
public:
    QGraphicsPixmapItem *p;
    Baozha();
    Baozha(QGraphicsPixmapItem *p);
};

#endif // BAOZHA_H
