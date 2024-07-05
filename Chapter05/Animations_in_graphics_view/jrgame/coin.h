#ifndef COIN_H
#define COIN_H

#include <QGraphicsEllipseItem>
#include <QObject>

class Coin : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
    Q_PROPERTY(QRectF rect READ rect WRITE setRect)
public:
    explicit Coin(QGraphicsItem *parent = nullptr);
    void explode();
    enum {Type = UserType + 1};
    int type() const override;

signals:

private:
    bool m_explosion = false;
};

#endif // COIN_H
