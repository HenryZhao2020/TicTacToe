#include "Square.h"
#include "Board.h"

Square::Square(Board *board, int i) : QPushButton(board) {
    setCursor(Qt::PointingHandCursor);
    connect(this, &Square::clicked, this, [board, i] {
        board->placeX(i);
    });
}

void Square::zoom() {
    iconSize = 0;

    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this, timer] {
        if (iconSize > 64) {
            timer->deleteLater();
        } else {
            setIconSize(QSize(++iconSize, iconSize));
        }
    });
    timer->start(2);
}

void Square::flash() {
    flashCount = 0;

    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this, timer] {
        if (++flashCount > 4) {
            timer->deleteLater();
        } else if (flashCount % 2) {
            setIconSize(QSize(0, 0));
        } else {
            setIconSize(QSize(64, 64));
        }
    });
    timer->start(200);
}
