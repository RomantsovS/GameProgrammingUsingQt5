#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>

class Player : public QGraphicsPixmapItem
{
public:
    Player(QGraphicsItem *parent = nullptr);
    int direction() const;
    void setDirection(int direction);
private:
    int m_direction = 0;
};

#endif // PLAYER_H
