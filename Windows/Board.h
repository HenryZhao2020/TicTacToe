#pragma once

#include <QFrame>

class Game;
class GameBar;
class Square;

enum class Role;

class Board : public QFrame {
    Q_OBJECT

public:
    Board(Game *game);
    ~Board();

    static const QIcon &getRoleIcon(const Role &role, bool gray = false);

    void place(int i, const QIcon &icon, bool animated);
    void placeX(int i);
    void placeO(int i = -1);
    void setFrozen(bool frozen);
    bool isFrozen();

private:
    Game *game;
    GameBar *gameBar;
    Square *squares[9];
    Role winner;
    bool frozen;

    bool isRoundEnded();
    void endRound();
};
