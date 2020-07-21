#include "Control.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap welcome(":/images/welcome_new.png");
    QSplashScreen splash(welcome);
    splash.resize(welcome.size());
    splash.show();
    a.processEvents();
    Sleep(1000);

    Control *scene=new Control();
    QGraphicsView *view = new QGraphicsView;
    splash.finish(view);
    view->setWindowTitle(QObject::tr("WAR OF PLANES"));
    view->setScene(scene);
    view->setBackgroundBrush(QBrush(QPixmap(":/images/background.png")));
    view->setStyleSheet("padding:0px; border:0px;");
    view->show();
    return a.exec();
}
