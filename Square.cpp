#include "Square.h"
#include "Board.h"

Square::Square(Board *board, int i) : QPushButton(board) {
    setCursor(Qt::PointingHandCursor);
    connect(this, &Square::clicked, this, [board, i] {
        board->placeX(i);
    });
}

void Square::zoom(int size) {
    if (size > 64) {
        return;
    }

    setIconSize(QSize(size, size));
    QTimer::singleShot(3, this, [this, size] {
        zoom(size + 2);
    });
}

void Square::flash(int count) {
    if (count > 4) {
        return;
    }

    if (count % 2) {
        setIconSize(QSize(0, 0));
    } else {
        setIconSize(QSize(64, 64));
    }

    QTimer::singleShot(200, this, [this, count] {
        flash(count + 1);
    });
}
