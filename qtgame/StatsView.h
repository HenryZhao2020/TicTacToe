#ifndef TICTACTOE_STATSVIEW_H
#define TICTACTOE_STATSVIEW_H

#include <QFrame>

class QLabel;

class GameStats;
class QtGame;

/// Bottom bar that shows running X/O/Tie counts.
class StatsView final : public QFrame {
    Q_OBJECT

public:
    /// Creates a stats bar bound to a QtGame.
    explicit StatsView(QtGame *game);

    /// Refreshes labels from stats object.
    void update(const GameStats &stats) const;

private:
    QLabel *xLabel{};
    QLabel *tieLabel{};
    QLabel *oLabel{};
};

#endif // TICTACTOE_STATSVIEW_H
