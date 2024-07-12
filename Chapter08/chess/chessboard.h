#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QObject>

class ChessBoard : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int ranks READ ranks NOTIFY ranksChanged)
    Q_PROPERTY(int columns READ columns NOTIFY columnsChanged)
public:
    explicit ChessBoard(int ranks, int columns, QObject *parent = nullptr);

    int ranks() const;
    int columns() const;
    char data(int rank, int column) const;
    void setData(int rank, int column, char value);
    void movePiece(int fromRank, int fromColumn, int toRank, int toColumn);
    void setFen(const QString &fen);
signals:
    void ranksChanged();
    void columnsChanged();
    void dataChanged(int r, int c);
    void boardReset();
protected:
    void setRanks(int newRanks);
    void setColumns(int newColumns);
    void initBoard();
    bool setDataInternal(int rank, int column, char value);
private:
    int m_ranks;
    int m_columns;
    QVector<char> m_boardData;
};

#endif // CHESSBOARD_H
