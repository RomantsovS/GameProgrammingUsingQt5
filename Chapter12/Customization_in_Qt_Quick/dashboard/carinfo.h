#ifndef CARINFO_H
#define CARINFO_H

#include <QWidget>
#include "carinfoengine.h"

namespace Ui {
class CarInfo;
}

class CarInfo : public QWidget {
    Q_OBJECT
    Q_PROPERTY(int speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(double distance READ distance NOTIFY distanceChanged)
    Q_PROPERTY(CarInfoEngine *engine READ engine NOTIFY engineChanged)
public:
    explicit CarInfo(QWidget *parent = nullptr);
    ~CarInfo();

    int speed() const;
    void setSpeed(int s);
    double distance() const;
    void setDistance(double d);
    CarInfoEngine *engine() const;

signals:
    void speedChanged(int);
    void distanceChanged(double);
    void engineChanged();

private:
    CarInfoEngine *m_engine;
    Ui::CarInfo *ui;
};

#endif // CARINFO_H
