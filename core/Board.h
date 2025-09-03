#ifndef TICTACTOE_BOARD_H
#define TICTACTOE_BOARD_H

#include <iosfwd>
#include <vector>

#include "Cell.h"
#include "Observer.h"
#include "Serializable.h"

/// A square Tic-Tac-Toe board that holds cells and notifies observers.
class Board final : public Subject, public Serializable {
public:
    /// Creates a dim x dim board with empty cells.
    /// \pre dim >= 2
    explicit Board(int dim);

    /// Returns the number of rows/columns.
    [[nodiscard]] int getDimension() const { return dim; }

    /// Returns true if no empty cells remain; false otherwise.
    [[nodiscard]] bool isFull() const { return (empty == 0); }

    /// Returns the cell at (r,c).
    /// \pre 0 <= r < dim, 0 <= c < dim
    [[nodiscard]] Cell getCell(int r, int c) const;

    /// Sets the cell at (r,c) and notifies observers if the cell is changed.
    /// \pre 0 <= r < dim, 0 <= c < dim
    /// \return true if the cell is changed, false otherwise.
    bool setCell(int r, int c, Cell newCell);

    /// Resets all cells to None and notifies observers.
    void clear();

private:
    int dim{};                  // Board dimension
    std::vector<Cell> cells;    // dim*dim cells
    int empty{};                // Number of empty cells

    /// Saves dimension and all cells (one per line).
    SerializableError onSave(std::ostream &out) override;

    /// Loads dimension and cells, then notifies observers.
    SerializableError onLoad(std::istream &in) override;

    /// Returns linear index for (r,c) in row-major order.
    /// \pre 0 <= r < dim, 0 <= c < dim
    [[nodiscard]] std::size_t index(int r, int c) const;
};

#endif // TICTACTOE_BOARD_H
