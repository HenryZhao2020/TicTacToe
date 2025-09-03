#ifndef TICTACTOE_TICTACTOE_H
#define TICTACTOE_TICTACTOE_H

#include <iosfwd>
#include <vector>

#include "Board.h"
#include "GameChecker.h"
#include "GameStats.h"
#include "Serializable.h"

/// Save behavior for the game.
enum class AutoSave {
    On = 0,     ///< Automatically saves on quit and loads on start.
    Off         ///< Caller must invoke saveGame() and loadGame().
};

/// Game controller: runs rounds, tracks turn/state, and saves/loads.
/// Subclasses implement runGame() for a concrete UI.
class TicTacToe : public Serializable {
public:
    /// Creates a game with a dim x dim board.
    TicTacToe(int dim, AutoSave save);
    /// Saves current state if save mode is Auto.
    ~TicTacToe() override;

    TicTacToe(const TicTacToe &) = delete;
    TicTacToe(TicTacToe &&) = delete;
    TicTacToe &operator=(const TicTacToe &) = delete;
    TicTacToe &operator=(TicTacToe &&) = delete;

    /// Starts the game loop. Restores previous state if save mode is Auto.
    void play();

    /// Saves game state and owned serializable.
    void saveGame() const;

    /// Loads game state and owned serializable.
    void loadGame() const;

    /// Returns board dimension.
    [[nodiscard]] int getDimension() const { return board.getDimension(); }

    /// Returns current player (X or O).
    [[nodiscard]] Cell getCurrentPlayer() const { return currPlayer; }

    /// Returns current game state.
    [[nodiscard]] GameState getState() const { return checker.getState(); }

    /// Places cell at (r,c) if target is empty.
    /// \pre 0 <= r < board dimension, 0 <= c < board dimension.
    /// \return true if the cell is written; false otherwise.
    bool placeCell(int r, int c, Cell cell);

    /// Switches current player (X <-> O).
    virtual void alternateTurn();

    /// Clears board and resets state.
    virtual void resetRound();

protected:
    /// Reads a cell at (r,c).
    /// \pre 0 <= r < board dimension, 0 <= c < board dimension.
    [[nodiscard]] Cell getCell(const int r, const int c) const {
        return board.getCell(r, c);
    }

    /// Returns stats (wins, ties).
    [[nodiscard]] const GameStats &getStats() const { return stats; }

    /// Attaches an observer to board.
    void attachToBoard(Observer *ob) { board.attach(ob); }

    /// Updates stats based on result (XWon/OWon/Tie).
    virtual void updateStats(const GameState result) {
        stats.update(result);
    }

private:
    Board board;
    GameChecker checker;
    Cell currPlayer;
    GameStats stats;
    AutoSave save{};
    std::vector<Serializable *> serials;

    /// UI hook: runs the concrete game loop.
    virtual void runGame() = 0;

    /// Saves current player.
    SerializableError onSave(std::ostream &out) override;

    /// Loads current player.
    SerializableError onLoad(std::istream &in) override;
};

#endif // TICTACTOE_TICTACTOE_H
