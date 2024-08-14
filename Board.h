#pragma once

#include <QFrame>

class Game;
class GameBar;
class Square;

enum class SquareIcon;

/**
 * @brief Displays a 3x3 Tic-Tac-Toe board.
 */
class Board : public QFrame {
    Q_OBJECT

public:
    Board(Game *game);
    ~Board();

    static const QIcon &getSquareIcon(SquareIcon icon, bool gray = false);

    void place(int i, const QIcon &icon, bool animated);
    void placeX(int i);
    void placeO(int i = -1);
    void setFrozen(bool frozen);
    bool isFrozen();

private:
    Game *game;
    GameBar *gameBar;
    Square *squares[9];
    SquareIcon winner;
    bool frozen;

    bool isRoundEnded();
    void endRound();
};
