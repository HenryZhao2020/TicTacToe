#include "GameAI.h"
#include "Attr.h"

const QList<QList<int>> GameAI::WIN_SEQS = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8},  // Rows
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8},  // Columns
    {0, 4, 8}, {2, 4, 6}              // Diagonals
};

QList<Role> &GameAI::board = Attr::getProgress().board;

// Function to check if a player has won
Role GameAI::getWinner() {
    for (const auto &seq : WIN_SEQS) {
        if (board[seq[0]] == board[seq[1]] &&
            board[seq[1]] == board[seq[2]] &&
            board[seq[0]] != Role::EMPTY) {
            return board[seq[0]];
        }
    }
    return Role::EMPTY;
}

QList<int> GameAI::getWinSeq() {
    for (const auto &seq : WIN_SEQS) {
        if (board[seq[0]] == board[seq[1]] &&
            board[seq[1]] == board[seq[2]] &&
            board[seq[0]] != Role::EMPTY) {
            return seq;
        }
    }
    return {};
}

// Function to check for a draw
bool GameAI::isDraw() {
    for (Role role : board) {
        if (role == Role::EMPTY) {
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
        if (board[i] == Role::EMPTY) {
            board[i] = Role::O;
            int score = minimax(0, false);
            board[i] = Role::EMPTY;
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
    Role winner = getWinner();
    if (winner == Role::O) {
        return 1;
    } else if (winner == Role::X) {
        return -1;
    } else if (isDraw()) {
        return 0;
    }

    if (isMaximizing) {
        int bestScore = INT_MIN;
        for (int i = 0; i < 9; ++i) {
            if (board[i] == Role::EMPTY) {
                board[i] = Role::O;
                int score = minimax(depth + 1, false);
                board[i] = Role::EMPTY;
                bestScore = qMax(score, bestScore);
            }
        }
        return bestScore;
    } else {
        int bestScore = INT_MAX;
        for (int i = 0; i < 9; ++i) {
            if (board[i] == Role::EMPTY) {
                board[i] = Role::X;
                int score = minimax(depth + 1, true);
                board[i] = Role::EMPTY;
                bestScore = qMin(score, bestScore);
            }
        }
        return bestScore;
    }
}
