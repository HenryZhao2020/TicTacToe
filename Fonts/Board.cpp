#include "Board.h"
#include "Game.h"
#include "GameBar.h"
#include "Square.h"
#include "Attr.h"

QList<QList<int>> SEQUENCES = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6},
    {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6},
};

Board::Board(Game *game) : QFrame(game) {
    this->game = game;
    gameBar = game->getGameBar();
    notPlaced = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    playerTurn = true;

    auto gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(5);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    for (int i = 0; i < 9; i++) {
        squares[i] = new Square(this, i);
        gridLayout->addWidget(squares[i], i / 3, i % 3);
    }
}

void Board::place(int i, const QIcon &icon, bool animated) {
    squares[i]->setIcon(icon);
    disconnect(squares[i], &QPushButton::clicked, nullptr, nullptr);

    if (animated) {
        squares[i]->zoom();
    } else {
        squares[i]->setIconSize(QSize(64, 64));
    }

    notPlaced.removeOne(i);
}

void Board::placeX(int i) {
    if (!playerTurn) {
        return;
    }

    place(i, getIcon("X.svg"), Attr::animated);
    Attr::xPlaced.append(i);
    playerTurn = false;
    gameBar->setHintVisible(false);

    if (isEnded()) {
        return;
    }

    QTimer::singleShot(500, this, [this] {
        gameBar->setHintVisible(Attr::hintVisible);
        gameBar->setHintText("Computer's Turn");
    });

    QTimer::singleShot(1000, this, &Board::placeO);
}

void Board::placeO() {
    int i = nextO();
    place(i, getIcon("O.svg"), Attr::animated);
    Attr::oPlaced.append(i);

    if (isEnded()) {
        return;
    }

    QTimer::singleShot(500, this, [this] {
        playerTurn = true;
        gameBar->setHintText("Your Turn");
    });
}

void Board::setPlayerTurn(bool turn) {
    playerTurn = turn;
}

int Board::lastMissingIndex(const QList<int> &placed) {
    auto isMissingOnly = [this, placed] (int a, int b, int c) {
        return placed.contains(a) && placed.contains(b) &&
               notPlaced.contains(c);
    };

    for (auto &seq : SEQUENCES) {
        if (isMissingOnly(seq[0], seq[1], seq[2])) {
            return seq[2];
        } else if (isMissingOnly(seq[0], seq[2], seq[1])) {
            return seq[1];
        } else if (isMissingOnly(seq[1], seq[2], seq[0])) {
            return seq[0];
        }
    }

    return -1;
}

int Board::nextO() {
    int i = lastMissingIndex(Attr::oPlaced);
    if (i == -1) {
        i = lastMissingIndex(Attr::xPlaced);
    }
    if (i == -1) {
        i = notPlaced[QRandomGenerator::global()->bounded(notPlaced.size())];
    }
    return i;
}

bool Board::isEnded() {
    for (auto &seq : SEQUENCES) {
        auto isThreeInRow = [seq] (const QList<int> &placed) {
            for (auto &i : seq) {
                if (!placed.contains(i)) {
                    return false;
                }
            }
            return true;
        };

        if (isThreeInRow(Attr::xPlaced)) {
            makeWinnerX(seq);
            return true;
        } else if (isThreeInRow(Attr::oPlaced)) {
            makeWinnerO(seq);
            return true;
        }
    }

    if (notPlaced.isEmpty()) {
        makeTie();
        return true;
    }

    return false;
}

void Board::makeEnded(const QIcon &icon, const QString &text) {
    for (auto &i : Attr::xPlaced) {
        squares[i]->setIcon(getIcon("X_Alpha.svg"));
    }

    for (auto &i : Attr::oPlaced) {
        squares[i]->setIcon(getIcon("O_Alpha.svg"));
    }

    for (auto &square : squares) {
        connect(square, &Square::clicked, this, [this] {
            game->restart();
        });
    }

    gameBar->setHintVisible(Attr::hintVisible);
    gameBar->setHintIcon(icon);
    gameBar->setHintText(text);
    gameBar->setRestartButtonVisible(true);

    QTimer::singleShot(2000, this, [this] {
        gameBar->setHintText("Click any square to restart...");
    });

    Attr::ended = true;
    Attr::numPlayed++;
}

void Board::makeWinnerX(const QList<int> &seq) {
    makeEnded(getIcon("Confetti.svg"), "You Won!");
    Attr::xScore++;

    for (auto &i : seq) {
        squares[i]->setIcon(getIcon("X.svg"));
        if (Attr::animated) {
            squares[i]->flash();
        }
    }
}

void Board::makeWinnerO(const QList<int> &seq) {
    makeEnded(getIcon("AI.svg"), "Computer Won!");
    Attr::oScore++;

    for (auto &i : seq) {
        squares[i]->setIcon(getIcon("O.svg"));
        if (Attr::animated) {
            squares[i]->flash();
        }
    }
}

void Board::makeTie() {
    makeEnded(getIcon("Handshake.svg"), "Tie!");
    Attr::numTied++;
}
