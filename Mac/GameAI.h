#pragma once

#include <QList>

enum class Role;

class GameAI {
public:
    static Role getWinner();
    static QList<int> getWinSeq();
    static bool isDraw();
    static int getBestMove();

private:
    static const QList<QList<int>> WIN_SEQS;
    static QList<Role> &board;

    static int minimax(int depth, bool isMaximizing);
};
