#include "carinfo.h"
#include "ui_carinfo.h"

CarInfo::CarInfo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CarInfo)
{
    ui->setupUi(this);

    m_engine = new CarInfoEngine(this);
    m_engine->setGear(ui->gearBox->value());
    m_engine->setRpm(ui->rpmBox->value());

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

    connect(ui->gearBox, &QSpinBox::valueChanged,
            m_engine, &CarInfoEngine::setGear);
    connect(ui->rpmBox, &QSpinBox::valueChanged,
            m_engine, &CarInfoEngine::setRpm);
    connect(m_engine, &CarInfoEngine::gearChanged,
            ui->gearBox, &QSpinBox::setValue);
    connect(m_engine, &CarInfoEngine::rpmChanged,
            ui->rpmBox, &QSpinBox::setValue);

    connect(ui->gearSlider, &QSlider::valueChanged,
            m_engine, &CarInfoEngine::setGear);
    connect(ui->rpmSlider, &QSlider::valueChanged,
            m_engine, &CarInfoEngine::setRpm);
    connect(m_engine, &CarInfoEngine::gearChanged,
            ui->gearSlider, &QSlider::setValue);
    connect(m_engine, &CarInfoEngine::rpmChanged,
            ui->rpmSlider, &QSlider::setValue);
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

CarInfoEngine *CarInfo::engine() const {
    return m_engine;
}
