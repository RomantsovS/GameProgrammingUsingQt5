#include "chessboard.h"

ChessBoard::ChessBoard(int ranks, int columns, QObject *parent) : QObject(parent), m_ranks(ranks), m_columns(columns)
{
    initBoard();
}

int ChessBoard::ranks() const
{
    return m_ranks;
}

int ChessBoard::columns() const
{
    return m_columns;
}

char ChessBoard::data(int rank, int column) const
{
    return m_boardData.at((rank - 1) * columns() + (column - 1));
}

void ChessBoard::setData(int rank, int column, char value)
{
    if(setDataInternal(rank, column, value)) {
        emit dataChanged(rank, column);
    }
}

void ChessBoard::movePiece(int fromRank, int fromColumn, int toRank, int toColumn)
{
    setData(toRank, toColumn, data(fromRank, fromColumn));
    setData(fromRank, fromColumn, ' ');
}

void ChessBoard::setFen(const QString &fen)
{
    int index = 0;
    int skip = 0;
    const int column_count = columns();
    QChar ch;
    for(int rank = ranks(); rank > 0; --rank){
        for(int column = 1; column <= column_count; ++column) {
            if(skip > 0) {
                ch = ' ';
                skip--;
            } else {
                ch = fen.at(index++);
                if(ch.isDigit()) {
                    skip = ch.toLatin1() - '0';
                    ch = ' ';
                    skip--;
                }
            }
            setDataInternal(rank, column, ch.toLatin1());
        }
        QChar next = fen.at(index++);
        if(next != '/' && next != ' ') {
            initBoard();
            return;
        }
    }
    emit boardReset();
}

void ChessBoard::setRanks(int newRanks)
{
    if(ranks() == newRanks) {
        return;
    }
    m_ranks = newRanks;
    initBoard();
    emit ranksChanged();
}

void ChessBoard::setColumns(int newColumns)
{
    if(columns() == newColumns) {
        return;
    }
    m_columns = newColumns;
    initBoard();
    emit columnsChanged();
}

void ChessBoard::initBoard()
{
    m_boardData.fill(' ', ranks() * columns());
    emit boardReset();
}

bool ChessBoard::setDataInternal(int rank, int column, char value)
{
    int index = (rank - 1) * columns() + (column - 1);
    if(m_boardData.at(index) == value) {
        return false;
    }
    m_boardData[index] = value;
    return true;
}
