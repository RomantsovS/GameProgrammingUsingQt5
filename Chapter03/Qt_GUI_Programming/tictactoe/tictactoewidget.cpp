#include "tictactoewidget.h"

#include <QGridLayout>
#include <QSignalMapper>

TicTacToeWidget::TicTacToeWidget(QWidget *parent)
    : QWidget{parent}
{
    QGridLayout* gridLayout = new QGridLayout(this);
    QSignalMapper *mapper = new QSignalMapper(this);
    for(int row = 0; row < 3; ++row) {
        for(int col = 0; col < 3; ++col) {
            QPushButton* button = new QPushButton(" ");
            button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
            gridLayout->addWidget(button, row, col);
            m_board.append(button);
            mapper->setMapping(button, m_board.count() - 1);
            connect(button, SIGNAL(clicked()), mapper, SLOT(map()));
        }
    }
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(handleButtonClick(int)));
}

void TicTacToeWidget::initNewGame()
{
    for(QPushButton *button : m_board) {
        button->setText(" ");
    }
    setCurrentPlayer(Player::Player1);
}

TicTacToeWidget::Player TicTacToeWidget::checkWinCondition()
{
    for(int i = 0; i < 3; ++i) {
        auto start_text = m_board[i * 3]->text();
        if(start_text == " ") {
            break;
        }
        int j = 1;
        for(; j < 3; ++j) {
            const auto& cur_text = m_board[i * 3 + j % 3]->text();
            if(cur_text != start_text) {
                break;
            }
        }
        if(j == 3) {
            return start_text == "X" ? Player::Player1 : Player::Player2;
        }
    }
    for(int j = 0; j < 3; ++j) {
        auto start_text = m_board[j % 3]->text();
        if(start_text == " ") {
            break;
        }
        int i = 1;
        for(; i < 3; ++i) {
            const auto& cur_text = m_board[i * 3 + j % 3]->text();
            if(cur_text != start_text) {
                break;
            }
        }
        if(i == 3) {
            return start_text == "X" ? Player::Player1 : Player::Player2;
        }
    }
    int i = 0;
    auto start_text = m_board[i * 3 + i % 3]->text();
    for(; i < 3; ++i) {
        if(start_text == " ") {
            break;
        }
        const auto& cur_text = m_board[i * 3 + i % 3]->text();
        if(cur_text != start_text) {
            break;
        }
    }
    if(i == 3) {
        return start_text == "X" ? Player::Player1 : Player::Player2;
    }
    i = 0;
    start_text = m_board[i * 3 + (2 - i) % 3]->text();
    for(; i < 3; ++i) {
        if(start_text == " ") {
            break;
        }
        const auto& cur_text = m_board[i * 3 + (2 - i) % 3]->text();
        if(cur_text != start_text) {
            break;
        }
    }
    if(i == 3) {
        return start_text == "X" ? Player::Player1 : Player::Player2;
    }
    for(int i = 0; i < 9; ++i) {
        if(m_board[i]->text() == " ")
        return Player::Invalid;
    }
    return Player::Draw;
}

void TicTacToeWidget::handleButtonClick(int index)
{
    if(m_currentPlayer == Player::Invalid) {
        return;
    }
    if(index < 0 || index >= m_board.size()) {
        return;
    }
    QPushButton *button = m_board[index];
    if(button->text() != " ") {
        return;
    }
    button->setText(currentPlayer() == Player::Player1 ? "X" : "O");
    Player winner = checkWinCondition();
    if(winner == Player::Invalid) {
        setCurrentPlayer(currentPlayer() == Player::Player1 ? Player::Player2 : Player::Player1);
        return;
    } else {
        emit gameOver(winner);
    }
}
