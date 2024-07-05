#ifndef BACKGROUNDITEM_H
#define BACKGROUNDITEM_H

#include <QGraphicsPixmapItem>

class BackgroundItem : public QGraphicsPixmapItem
{
public:
    BackgroundItem(const QPixmap &pixmap, QGraphicsItem *parent = nullptr);

    // QGraphicsItem interface
public:
    QPainterPath shape() const override;
};

#endif // BACKGROUNDITEM_H
