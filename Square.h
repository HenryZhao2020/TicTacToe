#pragma once

#include "PCH.h"

class Board;

class Square : public QPushButton {
    Q_OBJECT

public:
    Square(Board *board, int i);

    void zoom();
    void flash();

private:
    int iconSize;
    int flashCount;
};
