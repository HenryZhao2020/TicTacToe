#ifndef GAME_H
#define GAME_H

#include "PCH.h"

class GameBar;
class Board;

class Game : public QMainWindow {
    Q_OBJECT

public:
    Game();

    GameBar *getGameBar();
    Board *getBoard();
    void restart();
    void restore();

private:
    QVBoxLayout *vboxLayout;
    GameBar *bar;
    Board *board;

    void startRound();
};

#endif
