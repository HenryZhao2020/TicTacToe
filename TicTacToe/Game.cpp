#include "Game.h"
#include "GameBar.h"
#include "Board.h"
#include "Attr.h"

Game::Game() {
    // Create a central widget
    auto widget = new QWidget(this);
    setCentralWidget(widget);

    // Set up the layout
    vboxLayout = new QVBoxLayout(widget);
    vboxLayout->setSpacing(30);
    vboxLayout->setContentsMargins(30, 30, 30, 30);

    // Place the game bar on the top
    gameBar = new GameBar(this);
    gameBar->setHintIcon(Icon::load("Hint.svg"));
    gameBar->setRestartVisible(false);
    vboxLayout->addWidget(gameBar);

    // Place the board in the center
    board = new Board(this);
    vboxLayout->addWidget(board, 0, Qt::AlignCenter);
}

Game::~Game() {

}

GameBar *Game::getGameBar() {
    return gameBar;
}

Board *Game::getBoard() {
    return board;
}

void Game::restart() {
    // Reset the game progress
    Attr::get().resetProgress();

    // Reset the game bar
    gameBar->setHintIcon(Icon::load("Hint.svg"));
    gameBar->setRestartVisible(false);

    // Remove and delete the old board
    vboxLayout->removeWidget(board);
    board->deleteLater();

    // Place a new board
    board = new Board(this);
    vboxLayout->addWidget(board, 0, Qt::AlignCenter);

    // Continue the round
    continueRound();
}

void Game::load() {
    // Load saved attributes if possible
    if (!Attr::get().load()) {
        gameBar->setHintText("Click a square to begin...");
        return;
    }

    // If the round has ended previously, start a new round
    if (Attr::get().ended) {
        restart();
        return;
    }

    // Place all 'X's on their original locations
    for (const auto &i : Attr::get().xPlaced) {
        board->placeIcon(i, Icon::load("X.svg"), false);
    }

    // Place all 'O's on their original locations
    for (const auto &i : Attr::get().oPlaced) {
        board->placeIcon(i, Icon::load("O.svg"), false);
    }

    // Continue the round
    continueRound();
}

void Game::continueRound() {
    // If the round has ended, exit the function
    if (Attr::get().ended) {
        return;
    }

    if (Attr::get().xTurn) {
        gameBar->setHintText("X's turn");
    } else {
        if (Attr::get().playAI) {
            QTimer::singleShot(500, this, [this] {
                board->placeO();
            });
        }

        gameBar->setHintText("O's turn");
    }
}

void Game::show() {
    // Make this window not resizable
    setFixedSize(sizeHint());
    QMainWindow::show();
}
