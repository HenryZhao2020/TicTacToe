#include "BoardView.h"

#include <QGridLayout>

#include "CellView.h"
#include "QtGame.h"

namespace {
    constexpr int GRIDLINE_THICKNESS{6};
}

BoardView::BoardView(QtGame *game)
    : QFrame{game}
    , game{game}
    , dim{game->getDimension()} {

    const auto gridLayout = new QGridLayout{this};  // NOLINT
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    for (int r = 0; r < dim; ++r) {
        for (int c = 0; c < dim; ++c) {
            // Place each cell in their respective row and column.
            const auto view = new CellView{r, c, this};
            cellViews.append(view);
            gridLayout->addWidget(view, r * 2, c * 2);

            // Vertical line between every two horizontally adjacent cells.
            if (c != dim - 1) {
                const auto vLine = new GridLine{Qt::Vertical, this};
                gridLines.append(vLine);
                gridLayout->addWidget(vLine, r * 2, c * 2 + 1);
            }
        }

        // Horizontal line between every two adjacent rows.
        if (r != dim - 1) {
            const auto hLine = new GridLine{Qt::Horizontal, this};
            gridLines.append(hLine);
            gridLayout->addWidget(hLine, r * 2 + 1, 0, 1, dim * 2);
        }
    }
}

void BoardView::notify(const Subject &sub) {
    const auto &board{dynamic_cast<const Board &>(sub)};
    for (int r = 0; r < dim; ++r) {
        for (int c = 0; c < dim; ++c) {
            cellViews[r * dim + c]->place(board.getCell(r, c));
        }
    }
}

void BoardView::takeTurn(const int r, const int c) const {
    if (const Cell player{game->getCurrentPlayer()};
        !game->placeCell(r, c, player)) return;

    if (const GameState state{game->getState()};
        state == GameState::InProgress) {
        game->alternateTurn();
    } else {
        game->endRound(state);
    }
}

void BoardView::onScale(const double scale) {
    for (auto *view : cellViews) view->setScale(scale);
    for (auto *line : gridLines) line->setScale(scale);
}

GridLine::GridLine(const Qt::Orientation orient, BoardView *boardView)
    : QFrame{boardView}, orient{orient} {
    setThickness(GRIDLINE_THICKNESS);
}

void GridLine::onScale(const double scale) {
    const int scaledThickness{static_cast<int>(GRIDLINE_THICKNESS * scale)};
    setThickness(scaledThickness);
}

void GridLine::setThickness(const int thickness) {
    if (orient == Qt::Horizontal) setFixedHeight(thickness);
    else setFixedWidth(thickness);
}
