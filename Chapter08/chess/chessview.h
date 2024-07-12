#ifndef CHESSVIEW_H
#define CHESSVIEW_H

#include "chessboard.h"

#include <QIcon>
#include <QList>
#include <QMap>
#include <QMouseEvent>
#include <QPainter>
#include <QPointer>
#include <QWidget>

class ChessView : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QSize fieldSize READ fieldSize WRITE setFieldSize NOTIFY fieldSizeChanged)
public:
    explicit ChessView(QWidget *parent = nullptr);

    void setBoard(ChessBoard* board);
    ChessBoard* board() const;
    const QSize &fieldSize() const;
    void setFieldSize(const QSize &newFieldSize);
    QSize sizeHint() const;
    QRect fieldRect(int rank, int column) const;
    void setPiece(char type, const QIcon &icon);
    QIcon piece(char type) const;
    QPoint fieldAt(const QPoint& pt) const;

    class Highlight {
    public:
        Highlight() = default;
        virtual ~Highlight() = default;
        virtual int type() const { return 0; }
    };

    class FieldHighlight : public Highlight {
        public:
            enum { Type = 1 };
            FieldHighlight(int rank, int column, QColor color)
                : m_field(rank, column), m_color(color) {}
            inline int column() const { return m_field.x(); }
            inline int rank() const { return m_field.y(); }
            inline QColor color() const { return m_color; }
            int type() const { return Type; }
        private:
            QPoint m_field;
            QColor m_color;
    };

    void addHighlight(Highlight *hl);
    void removeHighlight(Highlight *hl);
    inline Highlight *highlight(int index) const { return m_highlights.at(index); }
    inline int highlightCount() const { return m_highlights.size(); }
    void drawHighlights(QPainter *painter);
signals:
    void fieldSizeChanged();
    void clicked(const QPoint&);
private:    
    QPointer<ChessBoard> m_board;
    QSize m_fieldSize;
    QMap<char, QIcon> m_pieces;
    QList<Highlight*> m_highlights;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
    virtual void drawRank(QPainter* painter, int rank);
    virtual void drawColumn(QPainter* painter, int column);
    virtual void drawField(QPainter* painter, int rank, int column);
    virtual void drawPiece(QPainter* painter, int rank, int column);

    // QWidget interface
protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // CHESSVIEW_H
