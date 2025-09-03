#ifndef TICTACTOE_CELL_H
#define TICTACTOE_CELL_H

#include <iosfwd>

/// Represents a single Tic-Tac-Toe cell.
enum class Cell { None = 0, X, O };

/// Returns the display symbol for a cell.
char CellSymbol(Cell cell);

/// Parses a symbol from the stream and assigns it to cell.
/// Accepts 'X', 'O', or '.' (case-insensitive for X and O).
/// Sets std::ios::failbit on invalid input.
std::istream &operator>>(std::istream &in, Cell &cell);

/// Writes the cell as a single character to the stream.
std::ostream &operator<<(std::ostream &out, Cell cell);

#endif // TICTACTOE_CELL_H
