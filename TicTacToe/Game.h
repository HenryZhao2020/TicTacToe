#pragma once

class GameBar;
class Board;

/**
 * @brief Displays primary game elements.
 */
class Game : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Initializes a new 'Game' instance.
     */
    Game();
    ~Game();

    /**
     * @brief Provides access to the private 'GameBar' instance.
     * @return The 'GameBar' instance.
     */
    GameBar *getGameBar();

    /**
     * @brief Provides access to the private 'Board' instance.
     * @return The 'Board' instance.
     */
    Board *getBoard();

    /**
     * @brief Resets the progress, then starts a new round.
     */
    void restart();

    /**
     * @brief Restores the game state from the loaded attributes.
     */
    void load();

    /**
     * @brief Continues the current round.
     */
    void continueRound();

    /**
     * @brief Overrides the original QMainWindow::show() method.
     */
    void show();

private:
    QVBoxLayout *vboxLayout;
    GameBar *gameBar;
    Board *board;
};
