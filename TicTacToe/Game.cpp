#include "Game.h"
#include "GameBar.h"
#include "Board.h"
#include "Attr.h"

Game::Game() {
    // Set up the layout
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(30);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    // Place the game bar on the top
    gameBar = new GameBar(this);
    gameBar->setHintIcon(Icon::load("Hint.svg"));
    gameBar->setHintText(tr("Click a square to begin..."));
    gameBar->setRestartVisible(false);
    mainLayout->addWidget(gameBar);

    // Place the board in the center
    board = new Board(this);
    mainLayout->addWidget(board);
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
    mainLayout->removeWidget(board);
    board->deleteLater();

    // Place a new board
    board = new Board(this);
    mainLayout->addWidget(board);

    // Continue the round
    continueRound();
}

void Game::load() {
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
        gameBar->setHintText(tr("X's turn"));
    } else {
        if (Attr::get().playAI) {
            QTimer::singleShot(500, this, [this] {
                board->placeO();
            });
        }

        gameBar->setHintText(tr("O's turn"));
    }
}
