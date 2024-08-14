#pragma once

#include <QList>

enum class SquareIcon;

class GameAI {
public:
    static SquareIcon getWinner();
    static QList<int> getWinSeq();
    static bool isDraw();
    static int getBestMove();

private:
    static const QList<QList<int>> WIN_SEQS;
    static QList<SquareIcon> &board;

    static int minimax(int depth, bool isMaximizing);
};
