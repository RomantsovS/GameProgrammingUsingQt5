#include "configurationdialog.h"
#include "ui_configurationdialog.h"

#include <qpushbutton.h>

ConfigurationDialog::ConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationDialog)
{
    ui->setupUi(this);
    connect(ui->Player1Name, &QLineEdit::textChanged, this, &ConfigurationDialog::updateOKButtonState);
    connect(ui->Player2Name, &QLineEdit::textChanged, this, &ConfigurationDialog::updateOKButtonState);
    updateOKButtonState();
}

ConfigurationDialog::~ConfigurationDialog()
{
    delete ui;
}

void ConfigurationDialog::setPlayer1Name(QString &p1name)
{
    ui->Player1Name->setText(p1name);
}

void ConfigurationDialog::setPlayer2Name(QString &p2name)
{
    ui->Player2Name->setText(p2name);
}

QString ConfigurationDialog::player1Name() const
{
    return ui->Player1Name->text();
}

QString ConfigurationDialog::player2Name() const
{
    return ui->Player2Name->text();
}

void ConfigurationDialog::updateOKButtonState()
{
    QPushButton* okbutton = ui->buttonBox->button(QDialogButtonBox::Ok);
    okbutton->setEnabled(!ui->Player1Name->text().isEmpty() && !ui->Player2Name->text().isEmpty());
}
