#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QWidget>

class View : public QGraphicsView
{
    Q_OBJECT

public:
    View(QWidget *parent = nullptr);
    ~View();

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *event);

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
};
#endif // VIEW_H
