#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chessalgorithm.h"
#include "chessview.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void viewClicked(const QPoint&field);
private:
    Ui::MainWindow *ui;
    ChessView *m_view;
    ChessAlgorithm *m_algorithm;
    QPoint m_clickPoint;
    ChessView::FieldHighlight*  m_selectedField;
};
#endif // MAINWINDOW_H
