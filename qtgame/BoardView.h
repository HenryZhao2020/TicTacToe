#ifndef TICTACTOE_BOARDVIEW_H
#define TICTACTOE_BOARDVIEW_H

#include <QFrame>
#include <QList>

#include "Observer.h"
#include "Scalable.h"

class CellView;
class GridLine;
class QtGame;

/// Draws grid, renders cells, and handles clicks.
class BoardView final : public QFrame, public Observer, public Scalable {
    Q_OBJECT

public:
    /// Creates a board view tied to a QtGame.
    explicit BoardView(QtGame *game);

    /// Observer callback: refresh cells from the board.
    void notify(const Subject &sub) override;

    /// Handles a user click at (r,c): place or finish round.
    void takeTurn(int r, int c) const;

private:
    QtGame *game{};
    const int dim{};
    QList<CellView *> cellViews;
    QList<GridLine *> gridLines;

    /// Scales the CellViews and the grid lines.
    void onScale(double scale) override;
};

/// Grid lines drawn in BoardView.
class GridLine final : public QFrame, public Scalable {
    Q_OBJECT

public:
    /// Creates a horizontal/vertical grid line.
    GridLine(Qt::Orientation orient, BoardView *boardView);

private:
    Qt::Orientation orient{};

    /// Updates line thickness when the scale changes.
    void onScale(double scale) override;

    /// Applies a thickness value.
    void setThickness(int thickness);
};

#endif // TICTACTOE_BOARDVIEW_H
