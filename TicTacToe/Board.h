#pragma once

// Forward declarations
class Game;
class GameBar;
class Square;

/**
 * @brief Displays squares in a 3x3 grid.
 */
class Board : public QFrame {
    Q_OBJECT

public:
    /**
     * @brief Initializes a new 'Board' instance.
     * @param game The parent 'Game' instance.
     */
    Board(Game *game);
    ~Board();

    /**
     * @brief Places an icon in a square.
     * @param i The index location of the square.
     * @param icon The icon to be displayed in the square.
     * @param animated Whether animation is enabled.
     */
    void placeIcon(int i, const QIcon &icon, bool animated);

    /**
     * @brief Automatically determines the behavior after clicking a square.
     * @param i The index location of the square.
     */
    void placeSquare(int i);

    /**
     * @brief Places an 'X' icon in a square.
     * @param i The index location of the square.
     */
    void placeX(int i);

    /**
     * @brief Places an 'O' icon in a square.
     * @param i The index location of the square.
     */
    void placeO(int i = -1);

    /**
     * @brief Sets whether the board is interactive
     * with keyboard and mouse.
     * @param interactive Whether the board is interactive
     * with keyboard and mouse.
     */
    void setInteractive(bool interactive);

    /**
     * @brief Returns whether the board is interactive
     * with keyboard and mouse.
     * @return Whether the board is interactive
     * with keyboard and mouse.
     */
    bool isInteractive();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    Game *game;
    GameBar *gameBar;

    // Board's layout
    QGridLayout *gridLayout;
    /* Store all squares in ascending order of rows and columns
     * Index    Row     Column
     * 0        0       0
     * 1        0       1
     * 2        0       2
     * 3        1       0
     * 4        1       1
     * 5        1       2
     * 6        2       0
     * 7        2       1
     * 8        2       2
     */
    Square *squares[9];
    // Store the index locations of empty squares (originally 0-8)
    QList<int> notPlaced;
    // Whether the board is interactive with keyboard and mouse
    bool interactive = true;

    // Sequences to win Tic-Tac-Toe
    static const QList<QList<int>> SEQUENCES;

    /**
     * @brief Returns O's next move calculated by AI.
     * @return The index location of the next 'O' square.
     */
    int getNextO();

    /**
     * @brief Returns the winning move for 'X' or 'O' if there is any.
     * @details
     * If only 1 index is missing to complete a row,
     * then that index will be the winning move
     *
     * @param placed The index locations of 'X' or 'O' squares.
     * @return The index location if there is a winning move; -1 otherwise.
     */
    int getWinningMove(const QList<int> &placed);

    /**
     * @brief Checks if the current round has ended.
     * @return true if the current round has ended; false otherwise.
     */
    bool isEnded();

    /**
     * @brief Ends the game and updates the UI.
     * @param icon The hint icon to be displayed on the game bar.
     * @param text The hint text to be displayed on the game bar.
     */
    void end(const QIcon &icon, const QString &text);

    /**
     * @brief Handles the end of game if 'X' wins.
     * @param seq The sequence that makes 'X' the winner.
     */
    void xWins(const QList<int> &seq);

    /**
     * @brief Handles the end of game if 'O' wins.
     * @param seq The sequence that makes 'O' the winner.
     */
    void oWins(const QList<int> &seq);

    /**
     * @brief Handles the end of game if 'X' and 'O' tie.
     */
    void tie();

    /**
     * @brief Checks if a 'QList' contains all elements of the other 'QList'.
     * @param l1 The first 'QList'.
     * @param l2 The second 'QList'.
     * @return true if l1 contains all elements of l2; false otherwise.
     */
    static bool containsAll(const QList<int> &l1, const QList<int> &l2);
};
