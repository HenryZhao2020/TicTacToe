#pragma once

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
     * @brief Places an icon on a square.
     * @param i The index location of the square.
     * @param icon The displayed icon.
     * @param animated Whether animation is enabled.
     */
    void placeIcon(int i, const QIcon &icon, bool animated);

    /**
     * @brief Automatically determines the behavior after clicking a square.
     * @param i The index location of the square.
     */
    void placeSquare(int i);

    /**
     * @brief Places an 'X' icon on a square.
     * @param i The index location of the square.
     */
    void placeX(int i);

    /**
     * @brief Places an 'O' icon on a square.
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

private:
    Game *game;
    GameBar *gameBar;
    // Store all squares
    Square *squares[9];
    // Store all index locations of empty squares
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
     * @param placed The placed 'X' or 'O' indexes.
     * @return The index location if there is a winning move; -1 otherwise.
     */
    int getWinningMove(const QList<int> &placed);

    /**
     * @brief Checks if the round has ended.
     * @return 'true' if the round has ended; 'false' otherwise.
     */
    bool isEnded();

    /**
     * @brief Ends the game.
     * @param icon The displayed icon on the game bar.
     * @param text The displayed text on the game bar.
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
     * @return 'true' if l1 contains all elements of l2; 'false' otherwise.
     */
    static bool containsAll(const QList<int> &l1, const QList<int> &l2);
};
