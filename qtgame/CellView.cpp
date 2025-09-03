#include "CellView.h"

#include "BoardView.h"

namespace {
    constexpr int CELL_SIDE{120};
    constexpr int CELL_FONT_PX{44};
}

CellView::CellView(const int r, const int c, BoardView *boardView)
    : QPushButton{boardView}
    , currCell{Cell::None} {

    setCursor(Qt::PointingHandCursor);
    setFocusPolicy(Qt::StrongFocus);
    connect(this, &CellView::clicked, this, [=] {
        boardView->takeTurn(r, c);
    });
}

void CellView::place(const Cell cell) {
    if (cell == currCell) return;

    currCell = cell;
    setText((cell != Cell::None) ? QString{CellSymbol(cell)} : "");
}

void CellView::onScale(const double scale) {
    const int scaledSide{static_cast<int>(CELL_SIDE * scale)};
    setMinimumSize(scaledSide, scaledSide);

    const int scaledFontPx{static_cast<int>(CELL_FONT_PX * scale)};
    setStyleSheet(QString{"font-size: %1px"}.arg(scaledFontPx));
}
