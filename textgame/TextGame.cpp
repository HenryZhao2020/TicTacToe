#include "TextGame.h"

#include "AppInfo.h"
#include "TextInput.h"

namespace {
    constexpr int CELL_WIDTH{3};
}

TextGame::TextGame(const int dim, const AutoSave save,
                   std::istream &in, std::ostream &out)
    : TicTacToe{dim, save}, in{in}, out{out} {}

void TextGame::runGame() {
    displayAppInfo();

    do {
        if (const GameState result{startRound()};
            result == GameState::Terminated) {
            out << "\nGame terminated.\n";
            return;
        }
        resetRound();
    }
    while (hasNextRound());
}

void TextGame::displayAppInfo() const {
    out << appinfo::name << '\n';
    out << "Version " << appinfo::version << '\n';
    out << "By " << appinfo::author << '\n';
}

GameState TextGame::startRound() {
    GameState state{};
    while (true) {
        state = takeTurn(getCurrentPlayer());
        if (state == GameState::Terminated) return state;
        if (state != GameState::InProgress) break;
        alternateTurn();
    }

    endRound(state);
    return state;
}

GameState TextGame::takeTurn(const Cell player) {
    printBoard();
    out << player << "'s turn\n";

    while (true) {
        int r{}, c{};
        if (!askCoordinate(r, c)) return GameState::Terminated;

        if (!placeCell(r, c, player)) {
            out << "This cell is already occupied!\n";
            continue;
        }
        return getState();
    }
}

void TextGame::printBoard() const {
    out << '\n';
    const int dim{getDimension()};
    for (int r = 0; r < dim; ++r) {
        for (int c = 0; c < dim; ++c) {
            out << ' ' << getCell(r, c) << ' ';
            if (c != dim - 1) out << '|';
        }
        out << '\n';

        if (r != dim - 1) {
            for (int c = 1; c < dim * (CELL_WIDTH + 1); ++c) {
                if (c % (CELL_WIDTH + 1) == 0) out << '+';
                else out << '-';
            }
        }
        out << '\n';
    }
    out << '\n';
}

bool TextGame::askCoordinate(int &r, int &c) const {
    const int dim{getDimension()};

    for (;;) {
        out << "Enter row (0-" << (dim - 1) << "): ";
        if (textinput::ReadIntBound(in, r, 0, dim - 1)) break;

        if (in.eof()) return false;
        out << "Invalid row!\n";
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    for (;;) {
        out << "Enter column (0-" << (dim - 1) << "): ";
        if (textinput::ReadIntBound(in, c, 0, dim - 1)) break;

        if (in.eof()) return false;
        out << "Invalid column!\n";
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return true;
}

void TextGame::endRound(const GameState result) {
    printBoard();
    displayResult(result);
    updateStats(result);
    displayStats();
}

void TextGame::displayResult(const GameState result) const {
    switch (result) {
    case GameState::XWon:
        out << "X won!\n";
        break;
    case GameState::OWon:
        out << "O won!\n";
        break;
    case GameState::Tie:
        out << "Tie!\n";
        break;
    default:
        break;
    }
}

void TextGame::displayStats() const {
    out << "\nGame Stats\n";
    out << "==========\n";
    out << "X: "   << getStats().getXWins() << '\n';
    out << "O: "   << getStats().getOWins() << '\n';
    out << "Tie: " << getStats().getTies()  << '\n';
}

bool TextGame::hasNextRound() const {
    bool yn{};
    out << "\nNext round (Y/n)? ";
    if (!textinput::ReadYesOrNo(in, yn)) return false;
    return yn;
}
