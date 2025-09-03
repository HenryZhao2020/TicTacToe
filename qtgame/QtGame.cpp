#include "QtGame.h"

#include <QApplication>
#include <QResizeEvent>
#include <QVBoxLayout>

#include "BoardView.h"
#include "GameBar.h"
#include "StatsView.h"

namespace {
    constexpr int GAME_FONT_PX{14};
    constexpr double GAME_SCALE_UNIT{0.25};
}

QtGame::QtGame(const int dim, const AutoSave save)
    : TicTacToe{dim, save}
    , gameBar{new GameBar{this}}
    , boardView{new BoardView{this}}
    , statsView{new StatsView{this}} {

    const auto mainWidget = new QWidget{this};  // NOLINT
    setCentralWidget(mainWidget);

    const auto gameLayout = new QVBoxLayout{mainWidget};  // NOLINT
    gameLayout->setSpacing(0);
    gameLayout->setContentsMargins(15, 15, 15, 15);
    gameLayout->addWidget(gameBar, 0, Qt::AlignTop);
    gameLayout->addWidget(boardView, 1, Qt::AlignCenter);
    gameLayout->addWidget(statsView, 0, Qt::AlignBottom);

    attachToBoard(boardView);
    setScale(1.0);
}

void QtGame::alternateTurn() {
    TicTacToe::alternateTurn();

    displayTurn();
}

void QtGame::resetRound() {
    TicTacToe::resetRound();

    displayTurn();
    gameBar->setResetEnabled(false);

    boardView->setEnabled(true);
}

void QtGame::endRound(const GameState state) {
    displayResult(state);
    gameBar->setResetEnabled(true);

    boardView->setEnabled(false);

    updateStats(state);
}

void QtGame::updateStats(const GameState state) {
    TicTacToe::updateStats(state);

    statsView->update(getStats());
}

void QtGame::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);

    const int currSide{std::min(width(), height())};
    if (currSide < baseWinSide) return;

    const double zoom{1.0 * currSide / baseWinSide};
    const double scale{std::floor(zoom / GAME_SCALE_UNIT) * GAME_SCALE_UNIT};
    setScale(scale);
}

void QtGame::runGame() {
    if (getState() != GameState::InProgress) resetRound();

    displayTurn();
    gameBar->setResetEnabled(false);

    statsView->update(getStats());

    adjustSize();
    baseWinSide = std::min(width(), height());

    show();
    raise();
}

void QtGame::onScale(const double scale) {
    // Scale app font size
    const int scaledFontPx{static_cast<int>(GAME_FONT_PX * scale)};
    for (auto *widget : QApplication::allWidgets()) {
        widget->setFont(QFont{font().families(), scaledFontPx});
    }

    gameBar->setScale(scale);
    boardView->setScale(scale);
}

void QtGame::displayTurn() const {
    const QString player{CellSymbol(getCurrentPlayer())};
    gameBar->setInfoMessage(tr("%1's Turn").arg(player));
}

void QtGame::displayResult(const GameState state) const {
    QString message;
    switch (state) {
    case GameState::XWon:
        message = tr("X won!");
        break;
    case GameState::OWon:
        message = tr("O won!");
        break;
    default:
        message = tr("Tie!");
        break;
    }
    gameBar->setInfoMessage(message);
}
