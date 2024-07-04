#include "sineitem.h"
#include "view.h"

#include <QPainter>

View::View(QWidget *parent)
    : QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing);
    setScene(new QGraphicsScene);

    SineItem* item = new SineItem;
    item->setFlag(QGraphicsItem::ItemIsSelectable);
    scene()->addItem(item);
}

View::~View()
{
    delete scene();
}

void View::wheelEvent(QWheelEvent *event)
{
    QGraphicsView::wheelEvent(event);
    if(event->isAccepted()) {
        return;
    }
    const qreal factor = 1.1;
    if(event->angleDelta().y() > 0) {
        scale(factor, factor);
    } else {
        scale(1 / factor, 1 / factor);
    }
}

void View::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    if(event->isAccepted()) {
            return;
    }
    switch(event->button()) {
    case Qt::LeftButton: {
        SineItem* item = new SineItem;
        item->setPos(mapToScene(event->pos()));
        scene()->addItem(item);
        event->accept();
        break;
    }
    case Qt::RightButton: {
        QGraphicsItem* item = itemAt(event->pos());
        if(item) {
            delete item;
        }
        event->accept();
        break;
    }
    default:
        break;
    }
}

