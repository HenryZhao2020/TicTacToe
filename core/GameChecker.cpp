#include "GameChecker.h"

#include "Board.h"

namespace {
    /// Returns true if a line is all X or all O in board.
    template <typename Func>
    bool isAllXO(const Board &board, Func &&getCell) {
        const Cell first{getCell(0)};
        if (first == Cell::None) return false;

        const int dim{board.getDimension()};
        for (int i = 1; i < dim; ++i) {
            if (getCell(i) != first) return false;
        }
        return true;
    }

    /// Returns true if row r is all X or all O.
    bool isRowAllXO(const int r, const Board &board) {
        return isAllXO(board, [&](const int c) {
            return board.getCell(r, c);
        });
    }

    /// Returns true if column c is all X or all O.
    bool isColumnAllXO(const int c, const Board &board) {
        return isAllXO(board, [&](const int r) {
            return board.getCell(r, c);
        });
    }

    /// Returns true if main diagonal is all X or all O.
    bool isMainDiagAllXO(const Board &board) {
        return isAllXO(board, [&](const int i) {
            return board.getCell(i, i);
        });
    }

    /// Returns true if anti-diagonal is all X or all O.
    bool isAntiDiagAllXO(const Board &board) {
        const int dim{board.getDimension()};
        return isAllXO(board, [&](const int i) {
            return board.getCell(i, dim - i - 1);
        });
    }

    /// Returns X/O if anyone won, else None.
    Cell getWinner(const Board &board) {
        const int dim{board.getDimension()};
        for (int i = 0; i < dim; ++i) {
            if (isRowAllXO(i, board))    return board.getCell(i, 0);
            if (isColumnAllXO(i, board)) return board.getCell(0, i);
        }

        if (isMainDiagAllXO(board)) return board.getCell(0, 0);
        if (isAntiDiagAllXO(board)) return board.getCell(0, dim - 1);

        return Cell::None;
    }
}

GameChecker::GameChecker() : state{GameState::InProgress} {}

void GameChecker::notify(const Subject &sub) {
    switch (const auto &board{dynamic_cast<const Board &>(sub)};
            getWinner(board)) {
    case Cell::X:
        state = GameState::XWon;
        break;
    case Cell::O:
        state = GameState::OWon;
        break;
    default:
        state = board.isFull() ? GameState::Tie : GameState::InProgress;
        break;
    }
}
