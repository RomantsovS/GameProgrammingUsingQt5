#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>

#include "tictactoewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startNewGame();
    void UpdateNameLabels();
    void handleGameOver(TicTacToeWidget::Player winner);

private:
    Ui::MainWindow *ui;

    void setLabelBold(QLabel* label, bool isBold);
};
#endif // MAINWINDOW_H
