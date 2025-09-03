#ifndef TICTACTOE_CELLVIEW_H
#define TICTACTOE_CELLVIEW_H

#include <QPushButton>

#include "Cell.h"
#include "Scalable.h"

class BoardView;

/// Single clickable cell on the board, shows X/O mark.
class CellView final : public QPushButton, public Scalable {
    Q_OBJECT

public:
    /// Creates a cell at (r,c), bound to a BoardView.
    CellView(int r, int c, BoardView *boardView);

    /// Updates cell text if value changed.
    void place(Cell cell);

private:
    Cell currCell{};

    /// Scales the cell size and content.
    void onScale(double scale) override;
};

#endif
