#pragma once

#include "PCH.h"

class Game;
class GameBar;
class Square;

class Board : public QFrame {
    Q_OBJECT

public:
    Board(Game *game);

    void place(int i, const QIcon &icon, bool animated);
    void placeX(int i);
    void placeO();
    void setPlayerTurn(bool turn);

private:
    Game *game;
    GameBar *gameBar;
    Square *squares[9];
    QList<int> notPlaced;
    bool playerTurn;

    int lastMissingIndex(const QList<int> &placed);
    int nextO();
    bool isEnded();
    void makeEnded(const QIcon &icon, const QString &text);
    void makeWinnerX(const QList<int> &seq);
    void makeWinnerO(const QList<int> &seq);
    void makeTie();
};
