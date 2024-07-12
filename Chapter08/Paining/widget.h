#ifndef WIDGET_H
#define WIDGET_H

#include <QPaintEvent>
#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int selectionStart READ selectionStart NOTIFY selectionChanged)
    Q_PROPERTY(int selectionEnd READ selectionEnd NOTIFY selectionChanged)

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    int selectionStart() const {
        return m_selectionStart;
    }
    int selectionEnd() const {
        return m_selectionEnd;
    }
public slots:
    void addPoint(unsigned yVal) {
        m_points << qMax(0u, yVal);
        update();
    }
    void clear() {
        m_points.clear();
        update();
    }
signals:
    void selectionChanged();
protected:
    void paintEvent(QPaintEvent*);
    void drawChart(QPainter* painter, const QRect& rect);
    void drawSelection(QPainter* painter, const QRect& rect);

    QVector<quint16> m_points;
private:
    int m_selectionStart = -1;
    int m_selectionEnd = -1;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};
#endif // WIDGET_H
