#include "Square.h"
#include "Board.h"

Square::Square(Board *board, int i) : QPushButton(board) {
    setCursor(Qt::PointingHandCursor);
    connect(this, &clicked, this, [board, i] {
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
    // Stop the animation if it is currently running
    if (zoomTimer != nullptr) {
        zoomTimer->deleteLater();
    }

    // Reset the icon width (px) to 0
    iconWidth = 0;

    // Set up the animation
    zoomTimer = new QTimer(this);
    connect(zoomTimer, &QTimer::timeout, this, [this] {
        // Stop the animation after the icon width reaches 64px
        if (iconWidth >= 64) {
            zoomTimer->deleteLater();
            zoomTimer = nullptr;
            return;
        }

        // Increase the icon width by 1px after each interval
        iconWidth += 2;
        setIconSize(QSize(iconWidth, iconWidth));
    });

    // Start the animation
    zoomTimer->start(3);
}

void Square::flash() {
    // Stop the animation if it is currently running
    if (flashTimer != nullptr) {
        flashTimer->deleteLater();
    }

    // Reset the flash count to 0
    flashes = 0;

    // Set up the animation
    flashTimer = new QTimer(this);
    connect(flashTimer, &QTimer::timeout, this, [this] {
        // Stop the animation after the flash count reaches 4
        if (flashes >= 4) {
            flashTimer->deleteLater();
            flashTimer = nullptr;
            return;
        }

        // Increase the flash count by 1 after each interval
        // If the flash count is even, show the icon
        // If the flash count is odd, hide the icon
        setIconSize((++flashes % 2 == 0) ? QSize(64, 64) : QSize(0, 0));
    });

    // Start the animation
    flashTimer->start(200);
}
