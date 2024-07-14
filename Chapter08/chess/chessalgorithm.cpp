#include "chessalgorithm.h"

ChessAlgorithm::ChessAlgorithm(QObject *parent)
    : QObject{parent}
{

}

ChessBoard *ChessAlgorithm::board() const
{
    return m_board;
}

void ChessAlgorithm::newGame()
{
    setupBoard();
    board()->setFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

bool ChessAlgorithm::move(int rankFrom, int colFrom, int rankTo, int colTo)
{
    Q_UNUSED(rankFrom);
    Q_UNUSED(colFrom);
    Q_UNUSED(rankTo);
    Q_UNUSED(colTo);
    return false;
}

bool ChessAlgorithm::move(const QPoint &from, const QPoint &to)
{
    return move(from.y(), from.x(), to.y(), to.x());
}

void ChessAlgorithm::setupBoard()
{
    setBoard(new ChessBoard(8, 8, this));
}

void ChessAlgorithm::setBoard(ChessBoard *board)
{
    if(board == m_board) {
        return;
    }
    delete m_board;
    m_board = board;
    emit boardChanged(m_board);
}

void ChessAlgorithm::setResult(Result value)
{
    if(result() == value) {
        return;
    }
    if(result() == NoResult) {
        m_result = value;
        emit gameOver(m_result);
    } else {
        m_result = value;
    }
}

void ChessAlgorithm::setCurrentPlayer(Player player)
{
    if(m_currentPlayer == player) {
        return;
    }
    m_currentPlayer = player;
    emit currentPlayerChangedChanged(m_currentPlayer);
}

const ChessAlgorithm::Player &ChessAlgorithm::currentPlayer() const
{
    return m_currentPlayer;
}

ChessAlgorithm::Result ChessAlgorithm::result() const
{
    return m_result;
}
