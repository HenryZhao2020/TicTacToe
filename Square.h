#ifndef SQUARE_H
#define SQUARE_H

#include "PCH.h"

class Board;

class Square : public QPushButton {
    Q_OBJECT

public:
    Square(Board *board, int i);

    void zoom(int size = 0);
    void flash(int count = 0);
};

#endif
