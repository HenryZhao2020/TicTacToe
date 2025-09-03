#ifndef TICTACTOE_GAMESTATS_H
#define TICTACTOE_GAMESTATS_H

#include <iosfwd>

#include "GameChecker.h"
#include "Serializable.h"

/// Tracks wins and ties, with save/load support.
class GameStats final : public Serializable {
public:
    /// Creates empty stats, all = 0.
    GameStats();

    /// Returns number of X wins.
    [[nodiscard]] int getXWins() const { return xWins; }

    /// Returns number of O wins.
    [[nodiscard]] int getOWins() const { return oWins; }

    /// Returns number of ties.
    [[nodiscard]] int getTies() const { return ties; }

    /// Returns total games played.
    [[nodiscard]] int getTotalPlays() const {
        return xWins + oWins + ties;
    }

    /// Updates stats based on game result.
    void update(GameState result);

private:
    int xWins{};
    int oWins{};
    int ties{};

    /// Saves X, O, and tie counts.
    SerializableError onSave(std::ostream &out) override;

    /// Loads counts from stream.
    SerializableError onLoad(std::istream &in) override;
};

#endif // TICTACTOE_GAMESTATS_H
