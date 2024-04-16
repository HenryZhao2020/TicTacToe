#include "Square.h"
#include "Board.h"

Square::Square(Board *board, int i) : QPushButton(board), board(board) {
    setCursor(Qt::PointingHandCursor);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(this, &Square::clicked, this, [board, i] {
        board->placeSquare(i);
    });
}

Square::~Square() {
    // Ensure all pointers are deleted
    if (zoomTimer != nullptr) {
        zoomTimer->deleteLater();
    }

    if (flashTimer != nullptr) {
        flashTimer->deleteLater();
    }
}

void Square::zoomIn() {
    animating = true;

    // Stop the animation if it is currently running
    if (zoomTimer != nullptr) {
        zoomTimer->deleteLater();
    }

    // Adjust the icon size of squares based on the new board size
    int boardSize = board->width();
    int spacing = board->layout()->spacing();
    int iconSize = boardSize / 4 - spacing / 2 - 20;

    /* The animation progresses over 10 intervals to reach the final icon size.
     * During each interval, the square's current icon size
     * increases by the quotient of the final icon size divided by 10.
     *
     * If the final size is not divisible by 10, the initial size is set to
     * the remainder of the final size divided by 10.
     *
     * Note that the final size is determined before the animation begins.
     * In case that the size changes if the window resizes
     * during the animation, the optimal icon size will be
     * recalculated once the animation is complete.
     */
    currentSize = iconSize % 10;
    setIconSize(QSize(currentSize, currentSize));

    // Set up the animation
    zoomTimer = new QTimer(this);
    connect(zoomTimer, &QTimer::timeout, this, [this, iconSize] {
        // Stop the animation after the icon width reaches 64px
        if (currentSize >= iconSize) {
            animating = false;
            zoomTimer->deleteLater();
            zoomTimer = nullptr;

            // Adjust the icon size of squares based on the new board size
            int boardSize = board->width();
            int spacing = board->layout()->spacing();
            int iconSize = boardSize / 4 - spacing / 2 - 20;
            setIconSize(QSize(iconSize, iconSize));

            return;
        }

        // Increase the icon size after each interval
        currentSize += (iconSize / 10);
        setIconSize(QSize(currentSize, currentSize));
    });

    // Start the animation
    zoomTimer->start(10);
}

void Square::flash() {
    animating = true;

    // Stop the animation if it is currently running
    if (flashTimer != nullptr) {
        flashTimer->deleteLater();
    }

    // Reset the flash count to 0
    flashes = 0;
    const QIcon &initIcon = icon();

    // Set up the animation
    flashTimer = new QTimer(this);
    connect(flashTimer, &QTimer::timeout, this, [this, initIcon] {
        // Stop the animation after the flash count reaches 4
        if (flashes >= 4) {
            animating = false;
            flashTimer->deleteLater();
            flashTimer = nullptr;
            return;
        }

        // Adjust the icon size of squares based on the new board size
        int boardSize = board->width();
        int spacing = board->layout()->spacing();
        int iconSize = boardSize / 4 - spacing / 2 - 20;

        // Increase the flash count by 1 after each interval
        // If the flash count is even, show the icon
        // If the flash count is odd, hide the icon
        setIcon((++flashes % 2) ? QIcon() : initIcon);
        setIconSize(QSize(iconSize, iconSize));
    });

    // Start the animation
    flashTimer->start(200);
}

bool Square::isAnimating() {
    return animating;
}
