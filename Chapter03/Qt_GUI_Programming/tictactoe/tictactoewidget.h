#ifndef TICTACTOEWIDGET_H
#define TICTACTOEWIDGET_H

#include <QPushButton>
#include <QWidget>

class TicTacToeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TicTacToeWidget(QWidget *parent = nullptr);

    enum class Player {
        Invalid, Player1, Player2, Draw
    };
    Q_ENUM(Player);

    Player currentPlayer() const {
        return m_currentPlayer;
    }
    void setCurrentPlayer(Player p) {
        if(m_currentPlayer == p) {
            return;
        }
        m_currentPlayer = p;
        emit currentPlayerChanged(p);
    }
    void initNewGame();

private:
    QVector<QPushButton*> m_board;
    Player m_currentPlayer = Player::Invalid;

    Player checkWinCondition();
signals:
    void currentPlayerChanged(Player);
    void gameOver(Player);
private slots:
    void handleButtonClick(int index);
};

#endif // TICTACTOEWIDGET_H
