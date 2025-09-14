#include "carinfo.h"
#include "ui_carinfo.h"

CarInfo::CarInfo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CarInfo)
{
    ui->setupUi(this);

    connect(ui->speedBox, &QSpinBox::valueChanged,
            this, &CarInfo::speedChanged);
    connect(ui->distanceBox, &QSpinBox::valueChanged,
            this, &CarInfo::distanceChanged);

    connect(ui->distanceSlider, &QSlider::valueChanged,
            ui->distanceBox, &QSpinBox::setValue);
    connect(this, &CarInfo::distanceChanged,
            ui->distanceSlider, &QSlider::setValue);

    connect(ui->speedSlider, &QSlider::valueChanged,
            ui->speedBox, &QSpinBox::setValue);
    connect(this, &CarInfo::speedChanged,
            ui->speedSlider, &QSlider::setValue);

    // connect(ui->gearBox, SIGNAL(valueChanged(int)),
    //         m_engine, SLOT(setGear(int)));
    // connect(ui->rpmBox, SIGNAL(valueChanged(int)),
    //         m_engine, SLOT(setRpm(int)));
    // connect(m_engine, SIGNAL(gearChanged(int)),
    //         ui->gearBox, SLOT(setValue(int)));
    // connect(m_engine, SIGNAL(rpmChanged(int)),
    //         ui->rpmBox, SLOT(setValue(int)));
}

CarInfo::~CarInfo()
{
    delete ui;
}

int CarInfo::speed() const {
    return ui->speedBox->value();
}
void CarInfo::setSpeed(int s) {
    ui->speedBox->setValue(s);
}
double CarInfo::distance() const {
    return ui->distanceBox->value();
}
void CarInfo::setDistance(double d) {
    ui->distanceBox->setValue(d);
}
