#ifndef MYSCENE_H
#define MYSCENE_H

#include "player.h"
#include "backgrounditem.h"

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QTimer>

class MyScene : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(qreal jumpFactor
               READ jumpFactor
               WRITE setJumpFactor
               NOTIFY jumpFactorChanged)
public:
    MyScene();

    qreal jumpFactor() const;
    void setJumpFactor(const qreal& jumpFactor);

private slots:
    void movePlayer();

signals:
    void jumpFactorChanged(qreal);
private:
    void addHorizontalInput(int input);
    void checkTimer();
    void applyParalax(qreal ratio, QGraphicsItem* item);
    void jump();
    void checkColliding();
    void initPlayField();

 int m_fieldWidth = 1500;
 QTimer m_timer;
 Player *m_player;
 int m_horizontalInput;
 qreal m_minX = 0, m_maxX = 0, m_currentX = 0;
 int m_velocity = 4;
 int m_worldShift = 0;
 qreal m_jumpFactor;
 QPropertyAnimation *m_jumpAnimation;
 qreal m_groundLevel = 300;
 int m_jumpHeight = 180;

 BackgroundItem* m_sky = nullptr;
 BackgroundItem* m_trees = nullptr;
 BackgroundItem* m_grass = nullptr;
 QGraphicsRectItem *m_coins = nullptr;

protected:
 void keyPressEvent(QKeyEvent *event) override;
};

#endif // MYSCENE_H
