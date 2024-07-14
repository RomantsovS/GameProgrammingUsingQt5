#ifndef CHESSALGORITHM_H
#define CHESSALGORITHM_H

#include "chessboard.h"

#include <QObject>
#include <QPoint>

class ChessAlgorithm : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Result result READ result)
    Q_PROPERTY(Player currentPlayer READ currentPlayer NOTIFY currentPlayerChangedChanged)
public:
    explicit ChessAlgorithm(QObject *parent = nullptr);

    enum Result { NoResult, Player1Wins, Draw, Player2Wins };
    Q_ENUM(Result)
    enum Player {NoPlayer, Player1, Player2 };
    Q_ENUM(Player)

    ChessBoard* board() const;
    const Player &currentPlayer() const;

    Result result() const;

public slots:
    virtual void newGame();
    virtual bool move(int rankFrom, int colFrom, int rankTo, int colTo);
    virtual bool move(const QPoint& from, const QPoint& to);
signals:
    void boardChanged(ChessBoard*);
    void currentPlayerChangedChanged(Player);
    void gameOver(Result);
protected:
    virtual void setupBoard();
    void setBoard(ChessBoard* board);
    void setResult(Result value);
    void setCurrentPlayer(Player player);
private:
    ChessBoard* m_board = nullptr;
    Player m_currentPlayer = Player::NoPlayer;
    Result m_result = Result::NoResult;
};

#endif // CHESSALGORITHM_H
