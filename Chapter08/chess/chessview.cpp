#include "chessview.h"

#include <QPainter>

ChessView::ChessView(QWidget *parent)
    : QWidget{parent}
{

}

void ChessView::setBoard(ChessBoard *board)
{
    if(m_board == board) {
        return;
    }
    if(m_board) {
        m_board->disconnect(this);
    }
    m_board = board;
    if(board) {
        connect(board, SIGNAL(dataChanged(int, int)), this, SLOT(update()));
        connect(board, SIGNAL(boardReset()), this, SLOT(update()));
    }
    updateGeometry();
}

ChessBoard *ChessView::board() const
{
    return m_board;
}

const QSize &ChessView::fieldSize() const
{
    return m_fieldSize;
}

void ChessView::setFieldSize(const QSize &newFieldSize)
{
    if (m_fieldSize == newFieldSize)
        return;
    m_fieldSize = newFieldSize;
    emit fieldSizeChanged();
    updateGeometry();
}

QSize ChessView::sizeHint() const
{
    if(!m_board) {
        return QSize(100, 100);
    }
    QSize boardSize = QSize(fieldSize().width() * m_board->columns() + 1,
                            m_fieldSize.height() * m_board->ranks() + 1);
    int rankSize = fontMetrics().width('M') + 4;
    int columnSize = fontMetrics().height() + 4;
    return boardSize + QSize(rankSize, columnSize);
}

QRect ChessView::fieldRect(int rank, int column) const
{
    if(!m_board) {
        return QRect();
    }
    const QSize fs = fieldSize();
    QPoint topLeft((column - 1) * fs.width(), (m_board->ranks() - rank) * fs.height());
    QRect fRect = QRect(topLeft, fs);
    int offset = fontMetrics().width('M');
    return fRect.translated(offset + 4, 0);
}

void ChessView::setPiece(char type, const QIcon &icon)
{
    m_pieces.insert(type, icon);
    update();
}

QIcon ChessView::piece(char type) const
{
    return m_pieces.value(type, QIcon());;
}

void ChessView::drawHighlights(QPainter *painter)
{
    for(int idx=0; idx < highlightCount(); ++idx) {
        Highlight *hl = highlight(idx);
        if(hl->type() == FieldHighlight::Type) {
            FieldHighlight *fhl = static_cast<FieldHighlight*>(hl);
            QRect rect = fieldRect(fhl->column(), fhl->rank());
            painter->fillRect(rect, fhl->color());
        }
    }
}

QPoint ChessView::fieldAt(const QPoint &pt) const
{
    if(!m_board) {
        return QPoint();
    }
    const QSize fs = fieldSize();
    int offset = fontMetrics().width('M') + 4;
    if(pt.x() < offset) {
        return QPoint();
    }
    int c = (pt.x() - offset) / fs.width();
    int r = pt.y() / fs.height();
    if(c < 0 || c > m_board->columns() || r < 0 || r > m_board->ranks()) {
        return QPoint();
    }
    return QPoint(c + 1, m_board->ranks() - r);
}

void ChessView::addHighlight(ChessView::Highlight *hl) {
    m_highlights.append(hl);
    update();
}

void ChessView::removeHighlight(ChessView::Highlight *hl) {
    m_highlights.removeOne(hl);
    update();
}

void ChessView::drawRank(QPainter *painter, int rank)
{
    QRect r = fieldRect(rank, 1);
    QRect rankRect = QRect(0, r.top(), r.left(), r.height()).adjusted(2, 0, -2, 0);
    QString rankText = QString::number(rank);
    painter->drawText(rankRect, Qt::AlignVCenter | Qt::AlignRight, rankText);
}

void ChessView::drawColumn(QPainter *painter, int column)
{
    QRect r = fieldRect(1, column);
    QRect columnRect = QRect(r.left(), r.bottom(), r.width(), height() - r.bottom()).adjusted(0, 2, 0, -2);
    painter->drawText(columnRect, Qt::AlignHCenter | Qt::AlignTop, QChar('a' + column - 1));
}

void ChessView::drawField(QPainter *painter, int rank, int column)
{
    QRect rect = fieldRect(rank, column);
    QColor fillColor = (column + rank) % 2 ? palette().color(QPalette::Light) : palette().color(QPalette::Mid);
    painter->setPen(palette().color(QPalette::Dark));
    painter->setBrush(fillColor);
    painter->drawRect(rect);
}

void ChessView::drawPiece(QPainter *painter, int rank, int column)
{
    QRect rect = fieldRect(rank, column);
    char value = m_board->data(rank, column);
    if(value != ' ') {
        QIcon icon = piece(value);
        if(!icon.isNull()) {
            icon.paint(painter, rect, Qt::AlignCenter);
        }
    }
}

void ChessView::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint pt = fieldAt(event->pos());
    if(pt.isNull()) {
        return;
    }
    emit clicked(pt);
}

void ChessView::paintEvent(QPaintEvent *event)
{
    if(!m_board) {
        return;
    }
    QPainter painter(this);
    for(int r = m_board->ranks(); r > 0; --r) {
        painter.save();
        drawRank(&painter, r);
        painter.restore();
    }
    for(int c = 1; c <= m_board->columns(); ++c) {
        painter.save();
        drawColumn(&painter, c);
        painter.restore();
    }
    for(int r = 1; r <= m_board->ranks(); ++r) {
        for(int c = 1; c <= m_board->columns(); ++c) {
            painter.save();
            drawField(&painter, r, c);
            painter.restore();
        }
    }

    drawHighlights(&painter);

    for(int r = m_board->ranks(); r > 0; --r) {
        for(int c = 1; c <= m_board->columns(); ++c) {
            drawPiece(&painter, r, c);
        }
    }
}
