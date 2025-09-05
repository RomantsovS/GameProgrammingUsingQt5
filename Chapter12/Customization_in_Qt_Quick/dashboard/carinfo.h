#ifndef CARINFO_H
#define CARINFO_H

#include <QWidget>

namespace Ui {
class CarInfo;
}

class CarInfo : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(double distance READ distance NOTIFY distanceChanged)
public:
    explicit CarInfo(QWidget *parent = nullptr);
    ~CarInfo();

    int speed() const;
    void setSpeed(int s);
    double distance() const;
    void setDistance(double d);

signals:
    void speedChanged(int);
    void distanceChanged(double);

private:
    Ui::CarInfo *ui;
};

#endif // CARINFO_H
