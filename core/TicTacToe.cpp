#include "TicTacToe.h"

TicTacToe::TicTacToe(const int dim, const AutoSave save)
    : Serializable{"Game.txt"}
    , board{dim}
    , currPlayer{Cell::X}
    , save{save}
    , serials{this, &board, &stats} {

    attachToBoard(&checker);
}

TicTacToe::~TicTacToe() {
    if (save == AutoSave::On) saveGame();
}

void TicTacToe::play() {
    if (save == AutoSave::On) loadGame();

    runGame();
}

void TicTacToe::saveGame() const {
    for (auto *serial : serials) serial->save();
}

void TicTacToe::loadGame() const {
    for (auto *serial : serials) serial->load();
}

bool TicTacToe::placeCell(const int r, const int c, const Cell cell) {
    return board.getCell(r, c) == Cell::None &&
           board.setCell(r, c, cell);
}

void TicTacToe::alternateTurn() {
    currPlayer = (currPlayer == Cell::X) ? Cell::O : Cell::X;
}

void TicTacToe::resetRound() {
    board.clear();
    checker.resetState();
    currPlayer = (stats.getTotalPlays() % 2) ? Cell::O : Cell::X;
}

SerializableError TicTacToe::onSave(std::ostream &out) {
    out << currPlayer << '\n';
    return {};
}

SerializableError TicTacToe::onLoad(std::istream &in) {
    Cell playerRead{};
    if (!(in >> playerRead)) {
        return SerializableError{
            SerializableError::Type::InvalidDataError,
            "Cannot read current player"
        };
    }
    std::swap(currPlayer, playerRead);
    return {};
}
