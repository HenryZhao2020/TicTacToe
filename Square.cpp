#include "Square.h"
#include "Board.h"
#include "Attr.h"

Square::Square(Board *board, int i) : QPushButton(board) {
    setCursor(Qt::PointingHandCursor);
    connect(this, &Square::clicked, this, [board, i] {
        if (board->isFrozen()) {
            return;
        }

        if (Attr::get().xTurn) {
            board->placeX(i);
        } else if (Attr::get().twoPlayer) {
            board->placeO(i);
        }
    });
}

Square::~Square() {
    if (zoomTimer != nullptr) {
        zoomTimer->deleteLater();
    }

    if (flashTimer != nullptr) {
        flashTimer->deleteLater();
    }
}

void Square::zoomIn(int maxSize) {
    if (zoomTimer != nullptr) {
        zoomTimer->deleteLater();
    }
    currSize = maxSize % 10;
    setIconSize(QSize(currSize, currSize));

    zoomTimer = new QTimer(this);
    connect(zoomTimer, &QTimer::timeout, this, [this, maxSize] {
        if (currSize >= maxSize) {
            zoomTimer->deleteLater();
            zoomTimer = nullptr;
            return;
        }

        currSize += maxSize / 10;
        setIconSize(QSize(currSize, currSize));
    });
    zoomTimer->start(10);
}

void Square::flash(int maxFlash) {
    if (flashTimer != nullptr) {
        flashTimer->deleteLater();
    }
    currFlash = 0;

    const QIcon &oldIcon = icon();
    static QIcon blankIcon;

    flashTimer = new QTimer(this);
    connect(flashTimer, &QTimer::timeout, this, [this, maxFlash, oldIcon] {
        if (currFlash >= maxFlash) {
            flashTimer->deleteLater();
            flashTimer = nullptr;
            return;
        }

        setIcon(++currFlash % 2 ? blankIcon : oldIcon);
    });
    flashTimer->start(250);
}
