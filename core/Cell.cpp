#include "Cell.h"

#include <istream>
#include <ostream>

namespace {
    // Cell symbols.
    constexpr char X_SYMBOL{'X'};
    constexpr char O_SYMBOL{'O'};
    constexpr char NONE_SYMBOL{'.'};
}

char CellSymbol(const Cell cell) {
    switch (cell) {
    case Cell::X:   return X_SYMBOL;
    case Cell::O:   return O_SYMBOL;
    default:        return NONE_SYMBOL;
    }
}

std::istream &operator>>(std::istream &in, Cell &cell) {
    char symbol;
    if (!(in >> symbol)) return in;

    // Safe cast for non-ASCII
    switch (std::toupper(static_cast<unsigned char>(symbol))) {
    case X_SYMBOL:
        cell = Cell::X;
        break;
    case O_SYMBOL:
        cell = Cell::O;
        break;
    case NONE_SYMBOL:
        cell = Cell::None;
        break;
    default:
        in.setstate(std::ios::failbit);
        break;
    }
    return in;
}

std::ostream &operator<<(std::ostream &out, const Cell cell) {
    return out << CellSymbol(cell);
}
