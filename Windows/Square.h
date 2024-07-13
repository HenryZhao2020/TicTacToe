#pragma once

#include <QPushButton>
#include <QTimer>

class Board;

class Square : public QPushButton {
    Q_OBJECT

public:
    Square(Board *board, int i);
    ~Square();

    void zoomIn(int maxSize);
    void flash(int maxFlash = 3);

private:
    QTimer *zoomTimer = nullptr;
    int currSize;

    QTimer *flashTimer = nullptr;
    int currFlash;
};
