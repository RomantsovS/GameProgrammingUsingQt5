#include "myscene.h"

#include <QApplication>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyScene scene;
    QGraphicsView view;
    view.setRenderHint(QPainter::Antialiasing);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    view.setScene(&scene);
    view.setFixedSize(scene.sceneRect().size().toSize());
    view.show();
    return a.exec();
}
