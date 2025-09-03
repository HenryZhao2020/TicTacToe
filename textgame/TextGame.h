#ifndef TICTACTOE_TEXTGAME_H
#define TICTACTOE_TEXTGAME_H

#include <iostream>

#include "TicTacToe.h"

/// CLI frontend for TicTacToe.
class TextGame final : public TicTacToe {
public:
    /// Makes a CLI game with streams in/out (defaults are cin/cout).
    TextGame(int dim, AutoSave save,
             std::istream &in = std::cin,
             std::ostream &out = std::cout);

private:
    std::istream &in;
    std::ostream &out;

    /// Main loop hook from TicTacToe.
    void runGame() override;

    /// Displays app name, version, and author information.
    void displayAppInfo() const ;

    /// Plays one round; returns final state or Terminated.
    GameState startRound();

    /// Handles a single player's turn; may Terminate.
    GameState takeTurn(Cell player);

    /// Prints the current board.
    void printBoard() const;

    /// Prompts and reads (r,c). Returns false on cancel/EOF.
    bool askCoordinate(int &r, int &c) const;

    /// Ends the round: show result, update stats, show stats.
    void endRound(GameState result);

    /// Prints the round result (XWon/OWon/Tie).
    void displayResult(GameState result) const;

    /// Prints cumulative stats.
    void displayStats() const;

    /// Asks user to continue (y/n).
    /// @return true if input is 'y'; false otherwise.
    [[nodiscard]] bool hasNextRound() const;
};

#endif // TICTACTOE_TEXTGAME_H
