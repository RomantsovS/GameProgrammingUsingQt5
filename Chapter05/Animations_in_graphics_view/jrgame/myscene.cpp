#include "coin.h"
#include "myscene.h"

#include <QApplication>
#include <QEasingCurve>

MyScene::MyScene() : m_jumpAnimation(new QPropertyAnimation(this))
{
    initPlayField();
    m_timer.setInterval(30);
    connect(&m_timer, &QTimer::timeout, this, &MyScene::movePlayer);

    m_jumpAnimation = new QPropertyAnimation(this);
    m_jumpAnimation->setTargetObject(this);
    m_jumpAnimation->setPropertyName("jumpFactor");
    m_jumpAnimation->setStartValue(0);
    m_jumpAnimation->setKeyValueAt(0.5, 1);
    m_jumpAnimation->setEndValue(0);
    m_jumpAnimation->setDuration(800);
    m_jumpAnimation->setEasingCurve(QEasingCurve::OutInQuad);
}

qreal MyScene::jumpFactor() const
{
    return m_jumpFactor;
}

void MyScene::setJumpFactor(const qreal &jumpFactor)
{
    if(m_jumpFactor == jumpFactor) {
        return;
    }
    m_jumpFactor = jumpFactor;
    emit jumpFactorChanged(m_jumpFactor);

    qreal groundY = (m_groundLevel - m_player->boundingRect().height() / 2);
    qreal y = groundY - m_jumpAnimation->currentValue().toReal() * m_jumpHeight;
    m_player->setY(y);

    checkColliding();
}

void MyScene::applyParalax(qreal ratio, QGraphicsItem* item)
{
    item->setX(-ratio * (item->boundingRect().width() - width()));
}

void MyScene::jump()
{
    if(m_jumpAnimation->state() == QAbstractAnimation::Stopped) {
        m_jumpAnimation->start();
    }
}

void MyScene::checkColliding()
{
    for(QGraphicsItem* item : collidingItems(m_player)) {
        if(Coin* c = qgraphicsitem_cast<Coin*>(item)) {
            c->explode();
        }
    }
}

void MyScene::initPlayField()
{
    setSceneRect(0, 0, 500, 340);
    m_sky = new BackgroundItem(QPixmap(":/sky.png"));
    addItem(m_sky);

    BackgroundItem *ground = new BackgroundItem(QPixmap(":/ground.png"));
    addItem(ground);
    ground->setPos(0, m_groundLevel);

    m_trees = new BackgroundItem(QPixmap(":/trees.png"));
    m_trees->setPos(0, m_groundLevel - m_trees->boundingRect().height());
    addItem(m_trees);

    m_grass = new BackgroundItem(QPixmap(":/grass.png"));
    m_grass->setPos(0, m_groundLevel - m_grass->boundingRect().height());
    addItem(m_grass);

    m_player = new Player;
    m_minX = m_player->boundingRect().width() * 0.5;
    m_maxX = m_fieldWidth - m_player->boundingRect().width() * 0.5;
    m_player->setPos(m_minX, m_groundLevel - m_player->boundingRect().height() / 2);
    m_currentX = m_minX;
    addItem(m_player);

    m_coins = new QGraphicsRectItem(0, 0, m_fieldWidth, m_jumpHeight);
    m_coins->setPen(Qt::NoPen);
    m_coins->setPos(0, m_groundLevel - m_jumpHeight);
    const int xRange = (m_maxX - m_minX) * 0.94;
    for(int i = 0; i < 10; ++i) {
        Coin *c = new Coin(m_coins);
        c->setPos(m_minX + qrand() % xRange, qrand() % m_jumpHeight);
//        c->setPos(50, 50);
    }
    addItem(m_coins);
}

void MyScene::movePlayer()
{
    const int direction = m_player->direction();
    if(direction == 0) {
        return;
    }
    const int dx = direction * m_velocity;
    qreal newX = qBound(m_minX, m_currentX + dx, m_maxX);
    if(newX == m_currentX) {
        return;
    }
    m_currentX = newX;

    const int shiftBorder = 150;
    const int rightShiftBorder = width() - shiftBorder;

    const int visiblePlayerPos = m_currentX - m_worldShift;
    const int newWorldShifRight = visiblePlayerPos - rightShiftBorder;
    if(newWorldShifRight > 0) {
        m_worldShift += newWorldShifRight;
    }
    const int newWorldShifLeft = shiftBorder - visiblePlayerPos;
    if(newWorldShifLeft > 0) {
        m_worldShift -= newWorldShifLeft;
    }
    const int maxWorldShift = m_fieldWidth - qRound(width());
    m_worldShift = qBound(0, m_worldShift, maxWorldShift);
    m_player->setX(m_currentX - m_worldShift);

    qreal ratio = qreal(m_worldShift) / maxWorldShift;
    applyParalax(ratio, m_sky);
    applyParalax(ratio, m_grass);
    applyParalax(ratio, m_trees);
    applyParalax(ratio, m_coins);

    checkColliding();
}

void MyScene::addHorizontalInput(int input)
{
    m_horizontalInput += input;
    m_horizontalInput = qBound(-1, m_horizontalInput, 1);
    m_player->setDirection(m_horizontalInput);
    checkTimer();
}

void MyScene::checkTimer()
{
    if(m_player->direction() == 0) {
        m_timer.stop();
    } else if(!m_timer.isActive()) {
        m_timer.start();
    }
}

void MyScene::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()) {
        return;
    }
    switch(event->key()) {
    case Qt::Key_Right :
        addHorizontalInput(1);
        break;
    case Qt::Key_Left:
        addHorizontalInput(-1);
        break;
    case Qt::Key_Space:
        jump();
        break;
    case Qt::Key_Escape:
        QApplication::quit();
        break;
    }
}
