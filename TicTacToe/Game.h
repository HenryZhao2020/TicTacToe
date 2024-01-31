#pragma once

// Forward declarations
class GameBar;
class Board;

/**
 * @brief Displays primary game elements, including a game bar on the top
 * and a board in the center.
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
     * @brief Provides access to the 'GameBar' instance.
     * @return The 'GameBar' instance.
     */
    GameBar *getGameBar();

    /**
     * @brief Provides access to the 'Board' instance.
     * @return The 'Board' instance.
     */
    Board *getBoard();

    /**
     * @brief Resets the progress, then starts a new round.
     */
    void restart();

    /**
     * @brief Restores the game state.
     * @note Call this function AFTER loading the attributes.
     */
    void load();

    /**
     * @brief Continues the current round.
     */
    void continueRound();

    /**
     * @brief Make this window non-resizable upon opening.
     */
    void show();

private:
    QVBoxLayout *mainLayout;
    GameBar *gameBar;
    Board *board;
};
