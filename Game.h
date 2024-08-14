#pragma once

#include <QMainWindow>
#include <QVBoxLayout>

class GameBar;
class Board;
class ScoreBoard;

class Game : public QMainWindow {
    Q_OBJECT

public:
    Game();
    ~Game();

    GameBar *getGameBar();
    Board *getBoard();
    ScoreBoard *getScoreBoard();

    void restart();
    void loadSave();
    void resumeRound();

private:
    QVBoxLayout *mainLayout;
    GameBar *gameBar;
    Board *board;
    ScoreBoard *scoreBoard;
};
