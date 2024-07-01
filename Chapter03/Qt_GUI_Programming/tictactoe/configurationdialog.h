#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include <QDialog>

namespace Ui {
class ConfigurationDialog;
}

class ConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigurationDialog(QWidget *parent = nullptr);
    ~ConfigurationDialog();

    void setPlayer1Name(QString& p1name);
    void setPlayer2Name(QString& p2name);

    QString player1Name() const;
    QString player2Name() const;
private slots:
    void updateOKButtonState();
private:
    Ui::ConfigurationDialog *ui;
};

#endif // CONFIGURATIONDIALOG_H
