#ifndef TICTACTOE_GAMECHECKER_H
#define TICTACTOE_GAMECHECKER_H

#include "Observer.h"

/// Overall game state as seen by the checker.
enum class GameState { InProgress = 0, XWon, OWon, Tie, Terminated };

/// Observer that detects wins/ties as the board changes.
class GameChecker final : public Observer {
public:
    /// Creates a checker with state = InProgress.
    GameChecker();

    /// Resets state to InProgress.
    void resetState() { state = GameState::InProgress; }

    /// Returns the last computed state.
    [[nodiscard]] GameState getState() const { return state; }

private:
    GameState state{};

    /// Handles board updates and recomputes state.
    void notify(const Subject &sub) override;
};

#endif // TICTACTOE_GAMECHECKER_H
