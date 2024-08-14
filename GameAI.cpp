#include "GameAI.h"
#include "Attr.h"

const QList<QList<int>> GameAI::WIN_SEQS = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8},  // Rows
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8},  // Columns
    {0, 4, 8}, {2, 4, 6}              // Diagonals
};

QList<SquareIcon> &GameAI::board = Attr::get().board;

// Function to check if a player has won
SquareIcon GameAI::getWinner() {
    for (const auto &seq : WIN_SEQS) {
        if (board[seq[0]] == board[seq[1]] &&
            board[seq[1]] == board[seq[2]] &&
            board[seq[0]] != SquareIcon::EMPTY) {
            return board[seq[0]];
        }
    }
    return SquareIcon::EMPTY;
}

QList<int> GameAI::getWinSeq() {
    for (const auto &seq : WIN_SEQS) {
        if (board[seq[0]] == board[seq[1]] &&
            board[seq[1]] == board[seq[2]] &&
            board[seq[0]] != SquareIcon::EMPTY) {
            return seq;
        }
    }
    return {};
}

// Function to check for a draw
bool GameAI::isDraw() {
    for (SquareIcon icon : board) {
        if (icon == SquareIcon::EMPTY) {
            return false;
        }
    }
    return true;
}

// Function to find the best move
int GameAI::getBestMove() {
    int bestMove = -1;
    int bestScore = INT_MIN;
    for (int i = 0; i < 9; ++i) {
        if (board[i] == SquareIcon::EMPTY) {
            board[i] = SquareIcon::O;
            int score = minimax(0, false);
            board[i] = SquareIcon::EMPTY;
            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }
    return bestMove;
}

// Minimax function
int GameAI::minimax(int depth, bool isMaximizing) {
    SquareIcon winner = getWinner();
    if (winner == SquareIcon::O) {
        return 1;
    } else if (winner == SquareIcon::X) {
        return -1;
    } else if (isDraw()) {
        return 0;
    }

    if (isMaximizing) {
        int bestScore = INT_MIN;
        for (int i = 0; i < 9; ++i) {
            if (board[i] == SquareIcon::EMPTY) {
                board[i] = SquareIcon::O;
                int score = minimax(depth + 1, false);
                board[i] = SquareIcon::EMPTY;
                bestScore = qMax(score, bestScore);
            }
        }
        return bestScore;
    } else {
        int bestScore = INT_MAX;
        for (int i = 0; i < 9; ++i) {
            if (board[i] == SquareIcon::EMPTY) {
                board[i] = SquareIcon::X;
                int score = minimax(depth + 1, true);
                board[i] = SquareIcon::EMPTY;
                bestScore = qMin(score, bestScore);
            }
        }
        return bestScore;
    }
}
