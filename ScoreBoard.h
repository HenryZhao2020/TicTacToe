#pragma once

#include <QFrame>
#include <QLabel>

class Game;

class ScoreBoard : public QFrame {
    Q_OBJECT

public:
    ScoreBoard(Game *game);
    ~ScoreBoard();

    void updateHeaders();
    void updateValues();

private:
    QLabel *xHead;
    QLabel *tieHead;
    QLabel *oHead;

    QLabel *xVal;
    QLabel *tieVal;
    QLabel *oVal;
};
