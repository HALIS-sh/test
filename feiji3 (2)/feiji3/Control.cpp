#include "Control.h"

const int movetime=50;
const int plane2newtime=500;
const int bullet2newtime=500;
const int bombtime=50;
const int bosstime=500;
const int lanuchtime=360;
const int bossappeartime=10;

Control::Control()
{
   plane=NULL;
   setSceneRect(0,0,600,500);

   //播放音乐
   playList = new QMediaPlaylist;
   playList->addMedia(QUrl("qrc:///music/starwars.mp3"));
   playList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop); //单曲循环
   player = new QMediaPlayer(this);
   player->setPlaylist(playList);
   player->play();

   //爆炸图片和音乐
   picture=new QPixmap(QString::fromStdString(strbomb3));
   music_bomb=new QMediaPlayer(this);
   music_bomb->setMedia(QUrl("qrc:///music/sound3.wav"));
   music_bossbomb=new QMediaPlayer(this);
   music_bossbomb->setMedia(QUrl("qrc:///music/sound2.wav"));

   //boss图片 血条
   bosspicture=new QPixmap(QString::fromStdString(strplane3));
   bosslifeFrameBar = new QGraphicsRectItem(99, 5, 302, 17);
   bosslifeFrameBar->setPen(QPen(Qt::white));
   addItem(bosslifeFrameBar);
   bosslifeBar = new QGraphicsRectItem(100, 6, 300, 15);
   bosslifeBar->setBrush(QBrush(Qt::red));
   addItem(bosslifeBar);

   //自己血条
   mylifeFrameBar = new QGraphicsRectItem(9, 449, 102, 12);
   mylifeFrameBar->setPen(QPen(Qt::white));
   addItem(mylifeFrameBar);
   mylifeBar = new QGraphicsRectItem(10, 450, 100, 10);
   mylifeBar->setBrush(QBrush(Qt::green));
   addItem(mylifeBar);

   //自己蓝条
   myenergyFrameBar = new QGraphicsRectItem(9, 479, 102, 12);
   myenergyFrameBar->setPen(QPen(Qt::white));
   addItem(myenergyFrameBar);
   myenergyBar = new QGraphicsRectItem(10, 480, 100, 10);
   myenergyBar->setBrush(QBrush(Qt::yellow));
   addItem(myenergyBar);

   // 得分提示
   scoreText = new QGraphicsTextItem;
   scoreText->setFont(QFont("Courier"));
   scoreText->setPos(QPointF(10,200));
   addItem(scoreText);

   // 游戏开始按钮
   QPushButton *startGameBtn = new QPushButton("Start Game");
   startGameBtn->setFont(QFont("Algerian",18));
   startGameBtn->setStyleSheet("QPushButton{background: transparent; color:white; } QPushButton:hover{color:red;}");
   connect(startGameBtn,SIGNAL(clicked()),this,SLOT(startGame()));
   startGameButton = addWidget(startGameBtn);
   startGameButton->setPos(250,200);

   // 游戏终止提示
   gameLostText = new QGraphicsTextItem;
   addItem(gameLostText);
   gameLostText->setFont(QFont("Algerian", 22));

   // 游戏帮助
   QPushButton *helpGameBtn = new QPushButton(tr("Help"));
   helpGameBtn->setFont(QFont("Algerian",18));
   helpGameBtn->setStyleSheet("QPushButton{background: transparent; color:white; }"
                                  "QPushButton:hover{color:red;}");
   connect(helpGameBtn,SIGNAL(clicked()),this,SLOT(showHelpMessage()));
   helpGameButton = addWidget(helpGameBtn);
   helpGameButton->setPos(242,250);

   // 退出游戏
   QPushButton *quitGameBtn = new QPushButton(tr("Quit Game"));
   quitGameBtn->setFont(QFont("Algerian",18));
   quitGameBtn->setStyleSheet("QPushButton{background: transparent; color:white; }"
                              "QPushButton:hover{color:red;}");
   connect(quitGameBtn,SIGNAL(clicked()),this,SLOT(quitGame()));
   quitGameButton = addWidget(quitGameBtn);
   quitGameButton->setPos(250, 300);

   sign_over=false;

   prepare();
}

void Control::timerEvent(QTimerEvent *event)
{
    if(plane==NULL)return;
    if(event->timerId()==movetimeid)
    {
        planemove1();
        planemove2();
        bulletmove1();
        bulletmove2();
        propmove();
        if(boss!=NULL)bossmove();
        if(mybulletsign>0)mybulletsign--;
    }
    else if(event->timerId()==plane2newtimeid)
    {
        if(bossappearnum==0&&boss==NULL)addplane2();
        if(plane->energy<100)
        {
            plane->energy=min(100,plane->energy+2);
             myenergystrand();
        }

    }
    else if(event->timerId()==bullet2newtimeid)
    {
        if(boss!=NULL)bossshoot1();
        if(bossappearnum>0)bossappeargo();
        shoot2();
    }
    else if(event->timerId()==bombtimeid)
    {
        myhaemalstrand();
        bombgo();
    }
    else if(event->timerId()==bosstimeid)
    {
        if(boss!=NULL)bossshoot2();
        if(boss==NULL&&score>=10)
        {
            score=0;
            bossappear();
        }
    }
    else if(event->timerId()==launchtimeid)
    {
        if(sign_j)prelaunch();
    }
}

void Control::keyPressEvent(QKeyEvent *event)
{
    if(plane==NULL)
    {
        if(event->key()==16777220&&!event->isAutoRepeat())
        {
            startGame();
        }
        return;
    }
    if(event->key()==Qt::Key_W&&!event->isAutoRepeat())
    {
        if(!sign_w)plane->dir+=QPointF(0, -15),sign_w=true;
    }
    else if(event->key()==Qt::Key_S&&!event->isAutoRepeat())
    {
        if(!sign_s)plane->dir+=QPointF(0, 15),sign_s=true;
    }
    else if(event->key()==Qt::Key_A&&!event->isAutoRepeat())
    {
        if(!sign_a)plane->dir+=QPointF(-15, 0),sign_a=true;
    }
    else if(event->key()==Qt::Key_D&&!event->isAutoRepeat())
    {
       if(!sign_d) plane->dir+=QPointF(15, 0),sign_d=true;
    }
    else if(event->key()==Qt::Key_J&&!event->isAutoRepeat())
    {
        if(!sign_j) sign_j=true;
        prelaunch();
    }
    else if(event->key()==Qt::Key_K&&!event->isAutoRepeat())
    {
       if(plane->energy>=50)
       {
           plane->energy-=50;
          myenergystrand();
           uniqueskill();
       }

    }
}

void Control::keyReleaseEvent(QKeyEvent *event)
{
    if(plane==NULL)return;
    if(event->key()==Qt::Key_W&&!event->isAutoRepeat())
    {
        if(sign_w)plane->dir-=QPointF(0, -15),sign_w=false;
    }
    else if(event->key()==Qt::Key_S&&!event->isAutoRepeat())
    {
        if(sign_s)plane->dir-=QPointF(0, 15),sign_s=false;
    }
    else if(event->key()==Qt::Key_A&&!event->isAutoRepeat())
    {
        if(sign_a)plane->dir-=QPointF(-15, 0),sign_a=false;
    }
    else if(event->key()==Qt::Key_D&&!event->isAutoRepeat())
    {
        if(sign_d)plane->dir-=QPointF(15, 0),sign_d=false;
    }
    else if(event->key()==Qt::Key_J&&!event->isAutoRepeat())
    {
        if(sign_j) sign_j=false;
    }
}

//自己准备发射一个子弹
void Control::prelaunch()
{
    QTime time=QTime::currentTime();
    int num=time.hour()*60*60*1000+time.minute()*60*1000+time.second()*1000+time.msec();
    if(num-prelaunchtime<lanuchtime)return;
    shoot1();
    prelaunchtime=num;
}

//产生boss画面向前推进一个
void Control::bossappeargo()
{
    bossappearnum--;
    if(bossappearnum<=0)
    {
        boss2->out();
        delete boss2;
        addboss();
    }
    else boss2->setOpacity(1-bossappearnum*1.0/bossappeartime);
}

//产生boss画面
void Control::bossappear()
{
    bossappearnum=bossappeartime;
    boss2=new Plane(this,strplane3,QPointF(150,15),QPointF(0,0),20,0,2);
    boss2->add();
    boss2->setOpacity(1-bossappearnum*1.0/bossappeartime);
}

//使用大招
void Control::uniqueskill()
{
    music_bossbomb->play();
    int xx=0;
    for(pplane=vec_plane2.begin();pplane!=vec_plane2.end();)
    {
        bomb((*pplane)->pos());
        (*pplane)->out();
        delete (*pplane);
        pplane=vec_plane2.erase(pplane);
        xx++;
    }
    if(boss!=NULL)
    {
        xx+=min(3,boss->life);
        bomb(boss->pos());
        music_bomb->play();
        if(boss->hit(3))
        {
            music_bossbomb->play();
            prop(boss->pos());
            bomb(boss->pos());
            boss->out();
            delete boss;
            boss=NULL;
        }
        haemalstrand();
    }

    if(boss==NULL&&bossappearnum==0)score+=xx;
    addscore+=xx;
    scoreText->setHtml(tr("<font color='yellow' size=4>分数: %1</font>").arg(addscore));
    scoreText->update();
}

//将爆炸向前推进一次
void Control::bombgo()
{
    for(vector<Node>::iterator it=vec_bomb.begin();it!=vec_bomb.end();)
    {
        it->id++;
        if(it->id>8)
        {
            removeItem(it->p);
            delete(it->p);
            it=vec_bomb.erase(it);
        }
        else
        {
            QPixmap tu2=picture->copy(picture->width()/8*(it->id-1),3,picture->width()/8,picture->height()-5);
            tu2=tu2.scaled(QSize(tu2.width()/2,tu2.height()/2), Qt::KeepAspectRatio);
            it->p->setPixmap(tu2);
            it->p->update();
            it++;
        }
    }
}

//判断道具是否应该被销毁
bool Control::panduan3(Object *p)
{
    if(!p->zai())return true;
    if(p->collidesWithItem(plane))
    {
        mybulletsign=60;
        return true;
    }
    return false;
}

//子弹包移动一步
void Control::propmove()
{
    vector<Object*>::iterator it;
    for(it=vec_prop.begin();it!=vec_prop.end();)
    {
        (*it)->move();
        if(panduan3(*it))
        {
            (*it)->out();
            delete(*it);
            it=vec_prop.erase(it);
        }
        else it++;
    }
}

//产生一个道具
void Control::prop(QPointF wei)
{
    Object *p = new Object(this,strprop,wei,QPoint(0,5));
    vec_prop.push_back(p);
    p->add();
}

//产生一个爆炸
void Control::bomb(QPointF wei)
{
    QGraphicsPixmapItem *p=new QGraphicsPixmapItem();
    p->setPos(wei);
    p->setZValue(3);
    addItem(p);
    vec_bomb.push_back(Node(p,0));
    music_bomb->play();
}

//清空道具
void Control::removeprop()
{
    for(vector<Object*>::iterator it=vec_prop.begin();it!=vec_prop.end();it++)
    {
        (*it)->out();
        delete(*it);
    }
    vec_prop.clear();
}

//清空场上所有图形
void Control::remove()
{

    for(pbullet=vec_bullet1.begin();pbullet!=vec_bullet1.end();pbullet++)
    {
        (*pbullet)->out();
        delete(*pbullet);
    }
    for(pbullet=vec_bullet2.begin();pbullet!=vec_bullet2.end();pbullet++)
    {
        (*pbullet)->out();
        delete(*pbullet);
    }
    for(pplane=vec_plane2.begin();pplane!=vec_plane2.end();pplane++)
    {
        (*pplane)->out();
        delete(*pplane);
    }
    vec_bullet1.clear();
    vec_bullet2.clear();
    vec_plane2.clear();

    for(vector<Node>::iterator it=vec_bomb.begin();it!=vec_bomb.end();)
    {
        removeItem(it->p);
        delete(it->p);
        it=vec_bomb.erase(it);
    }
    if(boss!=NULL)
    {
        boss->out();
        delete boss;
        boss=NULL;
    }
}

//boss发射5个子弹
void Control::bossshoot2()
{
    do
    {
        if(rand()%20!=0)return;
        QPointF wei=boss->pos()+QPointF(80,50);
        Bullet *p;

        p = new Bullet(this,strbullet2,wei,QPointF(14,14),1);
        p->setRotation(-45);
        vec_bullet2.push_back(p);
        p->add();

        p = new Bullet(this,strbullet2,wei,QPointF(-14,14),1);
        p->setRotation(45);
        vec_bullet2.push_back(p);
        p->add();

        p = new Bullet(this,strbullet2,wei,QPointF(10,17.3),1);
        p->setRotation(-30);
        vec_bullet2.push_back(p);
        p->add();

        p = new Bullet(this,strbullet2,wei,QPointF(-10,17.3),1);
        p->setRotation(30);
        vec_bullet2.push_back(p);
        p->add();

        p = new Bullet(this,strbullet2,wei,QPointF(0,20),1);
        vec_bullet2.push_back(p);
        p->add();
    }
    while(addscore==10);
    do
    {
        if(rand()%1!=0)return;
        QPointF wei=boss->pos()+QPointF(80,50);
        Bullet *p;

        p = new Bullet(this,strbullet2,wei,QPointF(14,14),1);
        p->setRotation(-45);
        vec_bullet2.push_back(p);
        p->add();

        p = new Bullet(this,strbullet2,wei,QPointF(-14,14),1);
        p->setRotation(45);
        vec_bullet2.push_back(p);
        p->add();

        p = new Bullet(this,strbullet2,wei,QPointF(10,17.3),1);
        p->setRotation(-30);
        vec_bullet2.push_back(p);
        p->add();

        p = new Bullet(this,strbullet2,wei,QPointF(-10,17.3),1);
        p->setRotation(30);
        vec_bullet2.push_back(p);
        p->add();

        p = new Bullet(this,strbullet2,wei,QPointF(0,20),1);
        vec_bullet2.push_back(p);
        p->add();
    }
    while(addscore==50);
}

//返回打向自己飞机的发射方向（追踪）
QPointF Control::xiang(QPointF wei)
{
    qreal xx=plane->x()-wei.x();
    qreal yy=plane->y()-wei.y();
    qreal len=sqrt(xx*xx+yy*yy);
    return QPoint(31*xx/len,31*yy/len);
}

//boss发设一个子弹
void Control::bossshoot1()
{
    if(rand()%2!=0)return;
    QPointF wei=boss->pos()+QPointF(80,50);
    Bullet *p = new Bullet(this,strbullet3,wei,xiang(wei),1);
    vec_bullet2.push_back(p);
    p->add();
}

//boss移动一步
void Control::bossmove()
{
    if(bossmovenum<=0)
    {
        bossmovenum=rand()%10+5;
        if(rand()%2==0)boss->dir=QPointF(rand()%10+5,0);
        else boss->dir=QPointF(-(rand()%10+5),0);
    }
    QPointF p=boss->pos();
    boss->move();
    if(boss->pos().x()<10||boss->pos().x()>480)boss->setPos(p);
    bossmovenum--;
}

//更新我的血条
void Control::myhaemalstrand()
{
        mylifeBar->setRect(10, 450, plane->life*10, 10);
        mylifeBar->setBrush(QBrush(Qt::green));
        mylifeBar->update();

}

//更新我的蓝条
void Control::myenergystrand()
{
    myenergyBar->setRect(10, 480, plane->energy, 10);
    myenergyBar->setBrush(QBrush(Qt::yellow));
    myenergyBar->update();
}

//更新boss血条
void Control::haemalstrand()
{
    if(boss==NULL)
    {
        bosslifeBar->hide();
        bosslifeFrameBar->hide();
    }
    else
    {
        bosslifeBar->setRect(100,6,(boss->life*10),15);
        bosslifeBar->setBrush(QBrush(Qt::red));
        bosslifeBar->update();
        bosslifeBar->show();
        bosslifeFrameBar->show();
    }

}

//产生一个boss
void Control::addboss()
{
    boss=new Plane(this,strplane3,QPointF(200,15),QPointF(0,0),30,0,2);
    boss->setZValue(2);
    boss->add();
    bossmovenum=0;
    haemalstrand();
}

//自己飞机移动一步
void Control::planemove1()
{
    QPointF p=plane->pos();
    plane->move();
    if(!plane->zai()||plane->pos().y()<120)plane->setPos(p);
}

//判断自己的子弹是否应该被销毁
bool Control::panduan1(Bullet *p)
{
    if(!p->zai())return true;
    for(pplane=vec_plane2.begin();pplane!=vec_plane2.end();pplane++)
    {
        if(!p->collidesWithItem(*pplane))continue;
        if(plane->energy<10)
        {
            plane->energy++;
            myenergystrand();
        }
        if((*pplane)->hit(p->might))
        {
            (*pplane)->out();
            if(rand()%10==0)prop((*pplane)->pos());
            bomb((*pplane)->pos());
            delete(*pplane);
            if(boss==NULL&&bossappearnum==0)score++;
            addscore++;
            scoreText->setHtml(tr("<font color='yellow' size=4>分数: %1</font>").arg(addscore));
            //scoreText->update();
            pplane=vec_plane2.erase(pplane);
        }
        return true;
    }
    if(boss!=NULL&&p->collidesWithItem(boss))
    {
        addscore++;
        scoreText->setHtml(tr("<font color='yellow' size=4>分数: %1</font>").arg(addscore));
        bomb(p->pos());
        if(plane->energy<10)
        {
            plane->energy++;
            myenergystrand();
        }
        music_bomb->play();
        if(boss->hit(p->might))
        {
            music_bossbomb->play();
            prop(boss->pos());
            bomb(boss->pos());
            boss->out();
            delete boss;
            boss=NULL;
        }
        haemalstrand();
        return true;
    }
    return false;
}

//自己的子弹走一步
void Control::bulletmove1()
{
    for(pbullet=vec_bullet1.begin();pbullet!=vec_bullet1.end();)
    {
        (*pbullet)->move();
        if(panduan1(*pbullet))
        {
            (*pbullet)->out();
            delete(*pbullet);
            pbullet=vec_bullet1.erase(pbullet);
        }
        else pbullet++;
    }
}

//自己发射一个子弹
void Control::shoot1()
{
    Bullet *p;
    if(mybulletsign<=0)
    {
        p = new Bullet(this,strbullet1,plane->pos()+QPointF(40,-38),QPointF(0,-25),1);
        vec_bullet1.push_back(p);
        p->add();
    }
    else
    {


        p = new Bullet(this,strbullet1,plane->pos()+QPointF(10,-38),QPointF(-12.5,-21.63),1);
        p->setRotation(-30);
        vec_bullet1.push_back(p);
        p->add();

        p = new Bullet(this,strbullet1,plane->pos()+QPointF(70,-38),QPointF(12.5,-21.63),1);
        p->setRotation(30);
        vec_bullet1.push_back(p);
        p->add();

        p = new Bullet(this,strbullet1,plane->pos()+QPointF(25,-38),QPointF(0,-25),1);
        vec_bullet1.push_back(p);
        p->add();

        p = new Bullet(this,strbullet1,plane->pos()+QPointF(55,-38),QPointF(0,-25),1);
        vec_bullet1.push_back(p);
        p->add();
    }
}

//敌方飞机移动一步
void Control::planemove2()
{
    for(pplane=vec_plane2.begin();pplane!=vec_plane2.end();)
    {
        (*pplane)->move();
        if(!(*pplane)->zai())
        {
            (*pplane)->out();
            delete *pplane;
            pplane=vec_plane2.erase(pplane);
        }
        else if((*pplane)->collidesWithItem(plane))
        {
            bomb((*pplane)->pos());
            if(plane->hit((*pplane)->might))
            {
                gameover();
                return;
            }
            (*pplane)->out();
            delete *pplane;
            pplane=vec_plane2.erase(pplane);
        }
        else pplane++;
    }
}

//判断敌机的子弹是否应该被销毁
bool Control::panduan2(Bullet *p)
{
    if(!p->zai())return true;
    if(p->collidesWithItem(plane))
    {
        if(plane->hit(p->might))
        {
            gameover();
        }
        return true;
    }
    return false;
}

//敌机的子弹走一步
void Control::bulletmove2()
{
    for(pbullet=vec_bullet2.begin();pbullet!=vec_bullet2.end();)
    {
        (*pbullet)->move();
        if(panduan2(*pbullet))
        {
            if(plane==NULL)return;
            (*pbullet)->out();
            delete(*pbullet);
            pbullet=vec_bullet2.erase(pbullet);
        }
        else pbullet++;
    }
}

//敌机发射一个子弹
void Control::shoot2()
{
    for(pplane=vec_plane2.begin();pplane!=vec_plane2.end();pplane++)
    {
        if(rand()%2!=0||(*pplane)->energy!=0)continue;
        Bullet *p = new Bullet(this,strbullet2,
              (*pplane)->pos() + QPointF((*pplane)->pixmap().width()/2-5,(*pplane)->pixmap().height()/2),QPoint(0,18),1);
        vec_bullet2.push_back(p);
        p->add();
    }
    
}

//在场景中添加一个敌机
bool Control::addplane2()
{
    QPixmap tu(QString::fromStdString(strplane2));
    int randx=rand()%(int)width();
    int i=0;
    for(int i=0;i<10;i++)
    {
        bool sign=true;
        for(Plane *p: vec_plane2)
        {
            if(p->sceneBoundingRect().intersects(QRectF(randx, 0, tu.width(), tu.height())))
            {
                sign=false;
                break;
            }
        }
        if(sign)break;
        else randx=rand()%(int)width();
    }
    
    if(i>=10)return false;
    Plane *p=new Plane(this,strplane2,QPointF(randx,0),QPointF(0,rand()%10+5),1,0,1);
    if(rand()%3==0)
    {
        p->energy=1;
        int xx=rand()%4;
        if(xx==0)p->setRotation(15),p->dir=QPointF(-1.95,14.8);
        else if(xx==1)p->setRotation(30),p->dir=QPointF(-7.48,13);
        else if(xx==3)p->setRotation(-30),p->dir=QPointF(7.45,13);
        else p->setRotation(-15),p->dir=QPointF(1.95,14.8);
    }
    vec_plane2.push_back(p);
    p->add();
    return true;
}

//显示帮助信息
void Control::showHelpMessage()
{
    QString helpText;
    helpText += tr("欢迎来到飞机大战\n");
    helpText += tr("\n进度条：\n");
    helpText += tr("绿色进度条：你的生命值\n");
    helpText += tr("黄色进度条：你的技能值\n");
    helpText += tr("\n操作：\n");
    helpText += tr("W：上； S：下； A：左； D：右\n");
    helpText += tr("J：发射一枚子弹\n");
    helpText += tr("K：消耗一半能量值，破坏全部小兵，并对boss造成10%的伤害，\n");
    helpText += tr("\n子弹包补给：\n");
    helpText += tr("强化子弹3秒，击毁boss 100%的几率爆出，击毁小兵10%的几率爆出   ");
    QMessageBox::information(NULL,tr("游戏帮助"),helpText);
}

//结束游戏
void Control::quitGame()
{
    exit(0);
}

//自己战机被击毁
void Control::gameover()
{
    killTimer(movetimeid);
    killTimer(plane2newtimeid);
    killTimer(bullet2newtimeid);
    killTimer(bombtimeid);
    killTimer(bosstimeid);
    killTimer(launchtimeid);
    remove();
    removeprop();
    sign_over=true;
    plane->out();
    delete plane;
    plane=NULL;

    prepare();
}

//开始游戏
void Control::startGame()
{
    srand(time(NULL));
    allhit();
    
    plane=new Plane(this,strplane1,QPointF(width()/2,height()*3/4),QPointF(0,0),10,0,1);
    plane->add();

    boss=NULL;
    score=0;
    addscore=0;
    mybulletsign=0;
    prelaunchtime=-10000;
    sign_w=sign_s=sign_a=sign_d=sign_j=false;

    scoreText->setHtml(tr("<font color='yellow' size=4>分数: %1</font>").arg(addscore));
    mylifeFrameBar->show();
    mylifeBar->show();
    myenergyFrameBar->show();
    myenergyBar->show();
    scoreText->show();
    myhaemalstrand();
    myenergystrand();

    movetimeid = startTimer(movetime);
    plane2newtimeid = startTimer(plane2newtime);
    bullet2newtimeid = startTimer(bullet2newtime);
    bombtimeid = startTimer(bombtime);
    bosstimeid = startTimer(bosstime);
    launchtimeid = startTimer(lanuchtime);
}

//主界面
void Control::prepare()
{
    plane=NULL;
    allhit();
    helpGameButton->show();
    startGameButton->show();
    quitGameButton->show();
    gameLostText->show();
    
    if(sign_over)
    {
        gameLostText->setHtml(tr("<font color=white>Game Over,得分: %1</font>").arg(addscore));
        gameLostText->setPos(180, 100);
    }
    else
    {
        gameLostText->setHtml(tr("<font color=white>飞机大战</font>"));
        gameLostText->setPos(250, 100);
    }
}

//将所有界面隐藏
void Control::allhit()
{
    bosslifeFrameBar->hide();
    bosslifeBar->hide();
    mylifeFrameBar->hide();
    mylifeBar->hide();
    myenergyFrameBar->hide();
    myenergyBar->hide();
    helpGameButton->hide();
    startGameButton->hide();
    quitGameButton->hide();
    gameLostText->hide();
    scoreText->hide();
}
