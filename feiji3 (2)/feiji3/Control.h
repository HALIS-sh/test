#ifndef CONTROL_H
#define CONTROL_H

#include <ctime>
#include <vector>
#include <cmath>
#include <cassert>
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <windows.h>

#include <QUrl>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDateTime>

#include "Plane.h"
#include "Bullet.h"
using namespace std;

class Node
{
public:
    QGraphicsPixmapItem *p;
    int id;
    Node(QGraphicsPixmapItem *p=NULL,int id=0):p(p),id(id){}
};

class Control: public QGraphicsScene
{
    Q_OBJECT
protected:
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

public:
    
    const string strplane1=":/images/myplane.png";
    const string strplane2=":/images/enemyplane.png";
    const string strplane3=":/images/boss.png";
    const string strbullet1=":/images/mybullet.png";
    const string strbullet2=":/images/enemybullet.png";
    const string strbullet3=":/images/bossbullet.png";
    const string strbomb1=":/images/explosion.BMP";
    const string strbomb2=":/images/explosion2.BMP";
    const string strbomb3=":/images/explosion.png";
    const string strprop=":/images/lifesupply.png";
    const string strmusic="sqc:///music/starwars.mp3";
    
    vector<Bullet*>vec_bullet1;
    vector<Bullet*>vec_bullet2;
    vector<Bullet*>::iterator pbullet;
    Plane *plane;
    Plane *boss;
    Plane *boss2;
    vector<Plane*>vec_plane2;
    vector<Plane*>::iterator pplane;
    vector<Node>vec_bomb;
    vector<Object *>vec_prop;

    QPixmap *picture;
    QPixmap *bosspicture;
    QMediaPlayer *music_bomb;
    QMediaPlayer *music_bossbomb;
    QMediaPlayer *player;
    QMediaPlaylist *playList;

    QGraphicsRectItem *bosslifeFrameBar;
    QGraphicsRectItem *bosslifeBar;
    QGraphicsRectItem *mylifeFrameBar;
    QGraphicsRectItem *mylifeBar;
    QGraphicsRectItem *myenergyFrameBar;
    QGraphicsRectItem *myenergyBar;
    QGraphicsRectItem *sceneFrameBar;

    QGraphicsWidget *helpGameButton;
    QGraphicsWidget *startGameButton;
    QGraphicsWidget *retryGameButton;
    QGraphicsWidget *quitGameButton;

    QGraphicsTextItem *gameLostText;
    QGraphicsTextItem *scoreText;
    
    int plane2newtimeid;
    int movetimeid;
    int bullet2newtimeid;
    int bombtimeid;
    int bosstimeid;
    int launchtimeid;
    int prelaunchtime;
    int bossmovenum;
    int bossappearnum;
    
    int mybulletsign;
    int score;
    int addscore;
    bool sign_over,sign_w,sign_s,sign_a,sign_d,sign_j;

    Control();
    void prelaunch();
    void bossappeargo();
    void bossappear();
    void removeprop();
    QPointF xiang(QPointF wei);
    bool panduan3(Object *p);
    void propmove();
    void prop(QPointF wei);
    void uniqueskill();
    void myenergystrand();
    void myhaemalstrand();
    void haemalstrand();
    void bossshoot1();
    void bossshoot2();
    void bossmove();
    void remove();
    void addboss();
    void bombgo();
    void bomb(QPointF wei);
    void planemove1();
    bool panduan1(Bullet *p);
    void bulletmove1();
    void shoot1();
    void planemove2();
    bool panduan2(Bullet *p);
    void bulletmove2();
    void shoot2();
    bool addplane2();
    void allhit();
    void prepare();
    void gameover();

protected slots:
    void startGame(); //开始游戏
    void showHelpMessage(); //显示帮助信息
    void quitGame(); //结束游戏
};

#endif // CONTROL_H
