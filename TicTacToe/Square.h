#pragma once

class Board;

/**
 * @brief Displays an 'X' or 'O' icon.
 */
class Square : public QPushButton {
    Q_OBJECT

public:
    /**
     * @brief Initializes a new 'Square' instance.
     * @param board The parent 'Board' instance.
     * @param i The assigned index location.
     */
    Square(Board *board, int i);
    ~Square();

    /**
     * @brief Gradually increases the width of the displayed icon to 64px.
     */
    void zoomIn();

    /**
     * @brief Shows then hides the icon after each interval.
     */
    void flash();

    /**
     * @brief Returns whether the square is animating.
     * @return Whether the square is animating.
     */
    bool isAnimating();

private:
    Board *board;
    // Used for zoom-in effect
    QTimer *zoomTimer = nullptr;
    // Store the current icon width
    int currentSize;
    // Whether the icon is animating
    bool animating = false;

    // Used for flash effect
    QTimer *flashTimer = nullptr;
    // Store the number of flashes
    int flashes;
};
