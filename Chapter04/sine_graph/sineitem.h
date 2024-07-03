#ifndef SINEITEM_H
#define SINEITEM_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

class SineItem : public QGraphicsItem
{
public:
    SineItem();

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    float maxX();
    void setMaxX(float value);

    // QGraphicsItem interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    float m_maxX = 50;
};

#endif // SINEITEM_H
