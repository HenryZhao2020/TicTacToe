#ifndef TICTACTOE_QTGAME_H
#define TICTACTOE_QTGAME_H

#include <QMainWindow>

#include "Scalable.h"
#include "TicTacToe.h"

class QResizeEvent;

class BoardView;
class GameBar;
class StatsView;

/// QWidget-based frontend for TicTacToe.
class QtGame final : public QMainWindow, public TicTacToe, public Scalable {
    Q_OBJECT

public:
    /// Creates a Qt game with dim x dim board and save mode.
    QtGame(int dim, AutoSave save);

    /// Switches player and updates UI.
    void alternateTurn() override;

    /// Clears board, resets state, updates UI.
    void resetRound() override;

    /// Ends round: show result, disable board, update stats.
    void endRound(GameState state);

protected:
    /// Updates stats view after controller updates stats.
    void updateStats(GameState state) override;

    /// Calculates scale factor as the window grows or shrinks.
    void resizeEvent(QResizeEvent *event) override;

private:
    GameBar *gameBar{};
    BoardView *boardView{};
    StatsView *statsView{};
    int baseWinSide{};

    /// UI entry point for the game loop.
    void runGame() override;

    /// Scales app font size and game elements.
    void onScale(double scale) override;

    /// Shows current player's turn in the toolbar.
    void displayTurn() const;

    /// Shows final result in the toolbar.
    void displayResult(GameState state) const;
};

#endif // TICTACTOE_QTGAME_H
