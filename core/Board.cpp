#include "Board.h"

#include <cassert>

namespace {
    constexpr int MIN_DIM{2};
}

Board::Board(const int dim)
    : Serializable{"Board.txt"}
    , dim{dim}
    , cells(dim * dim)
    , empty{dim * dim} {

    assert(dim >= MIN_DIM && "Dimension too small");
}

Cell Board::getCell(const int r, const int c) const {
    return cells[index(r, c)];
}

bool Board::setCell(const int r, const int c, const Cell newCell) {
    const Cell oldCell{cells[index(r, c)]};
    if (newCell == oldCell) return false;

    cells[index(r, c)] = newCell;
    notifyObservers();

    // At this point, oldCell != newCell.
    // If new cell is None, then old cell is not None, thus ++empty.
    // If new cell is not None, then old cell is None, thus --empty.
    if (newCell == Cell::None) ++empty;
    else if (oldCell == Cell::None) --empty;

    return true;
}

void Board::clear() {
    if (empty == dim * dim) return;

    std::ranges::fill(cells, Cell::None);
    empty = dim * dim;
    notifyObservers();
}

SerializableError Board::onSave(std::ostream &out) {
    out << dim << '\n';
    for (const Cell cell : cells) {
        out << cell << '\n';
    }
    return {};
}

SerializableError Board::onLoad(std::istream &in) {
    int dimRead{};
    if (!(in >> dimRead)) {
        return SerializableError{
            SerializableError::Type::InvalidDataError,
            "Cannot read dimension"
        };
    }
    if (dimRead < MIN_DIM) {
        return SerializableError{
            SerializableError::Type::InvalidDataError,
            "Dimension too small"
        };
    }

    std::vector<Cell> cellsRead(dimRead * dimRead);
    int emptyRead{};
    for (Cell &cell : cellsRead) {
        if (!(in >> cell)) {
            return SerializableError{
                SerializableError::Type::InvalidDataError,
                "Cannot read cell"
            };
        }
        if (cell == Cell::None) ++emptyRead;
    }

    std::swap(dim,   dimRead);
    std::swap(cells, cellsRead);
    std::swap(empty, emptyRead);
    
    notifyObservers();
    return {};
}

std::size_t Board::index(const int r, const int c) const {
    assert(0 <= r && r < dim && "Row out of bounds");
    assert(0 <= c && c < dim && "Column out of bounds");
    return r * dim + c;
}
