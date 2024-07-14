#ifndef FOXANDHOUNDS_H
#define FOXANDHOUNDS_H

#include "chessalgorithm.h"

class FoxAndHounds : public ChessAlgorithm
{
public:
    explicit FoxAndHounds(QObject *parent = nullptr);

    // ChessAlgorithm interface
public slots:
    void newGame() override;
    bool move(int rankFrom, int colFrom, int rankTo, int colTo) override;
protected:
    bool foxCanMove() const;
    bool emptyByOffset(int x, int y) const;
private:
    QPoint m_fox;
};

#endif // FOXANDHOUNDS_H
